#include "OrderQueue.cpp"
#include "../WarehouseTree.h"
#include "../Header/RobotList.hpp"
#include "../Header/RobotQueue.hpp"
#include "../Header/RobotQueue.hpp"
#include <iostream>
#include <limits>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Function to assign tasks to robot
void assignTask(OrderNode *order, Robot &robot, RobotQueue &queue)
{
    cout << "Order ID: " << order->orderId << " is assigned to " << robot.ID << endl;
    robot.currOrder = order;
    robot.status = BUSY;
    robot.workLoad++;

    //======================= TASK 3 CODE INSERT HERE =======================

    //========================== END OF CODE ==================================

    // After completion, enqueue back the robot
    robot.status = AVAILABLE;
    queue.enqueue(&robot);
}

// Function to validate input
void checkInput(int *option)
{
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input!" << endl;
        cout << "Your Option: ";
        cin >> *option;
    }
}

void robotSubMenu(RobotList &robotList);
int selectStatusMenu();

int main()
{

    OrderManagement orderManagement;

    // Insert 100 dummy orders
    for (int i = 0; i < 10; i++)
    {
        orderManagement.addPendingOrder("test", "test", i + 1);
    }
    cout << endl
         << endl;

    // Declare RobotList and RobotQueue objects
    RobotList *robotList = new RobotList(2);
    RobotQueue *queue = new RobotQueue();

    // Initialise 10 robots in the RobotList
    for (int i = 0; i < 10; i++)
    {
        string ID = "R" + to_string(i + 1);
        robotList->insertAtEnd(ID);
    }

    // Insert all robots in the array into queue
    for (int i = 0; i < robotList->getSize(); i++)
    {
        // Insert pointer to array element
        queue->enqueue(&robotList->arr[i]);
    }

    // Declare difference parameter to identify acceptable difference range in workload
    int diffParameter = 5;

    while (!orderManagement.pendingQueue.isEmpty())
    {

        // Dequeue first robot
        Robot *currRobot = queue->dequeue();

        // Check the status
        // If available, assign task
        if (currRobot->status == AVAILABLE)
        {
            // If the current robot's workload is least, that means it's the slowest
            if (currRobot->workLoad < queue->minLoad)
            {
                // Set the new workload as the new minLoad
                queue->minLoad = currRobot->workLoad;

                // Identify slowest robot
                queue->slowestRobot = currRobot->ID;
            }

            // If the difference in workload with the next in line is between difference parameter,
            // Assume the workload is balanced, so reset slowest robot
            int diff = currRobot->workLoad - queue->peek()->workLoad;
            bool isSame = currRobot->workLoad == queue->peek()->workLoad;

            if ((currRobot->ID == queue->slowestRobot && diff >= diffParameter) || isSame)
            {
                queue->minLoad = INT_MAX;
                queue->slowestRobot = "";
            }

            // Get first pending order
            OrderNode *currOrder = orderManagement.assignToRobot();
            assignTask(currOrder, *currRobot, *queue);
        }
        else
        {
            // Else, enqueue the robot back to "skip" its turn
            queue->enqueue(currRobot);
        }
    }

    robotSubMenu(*robotList);
    return 0;
}

void robotSubMenu(RobotList &robotList)
{
    int choice;
    int selection;
    bool isExit = false;
    while (!isExit)
    {
        cout << "\n----------------- Order Management System -----------------" << endl;
        cout << "1. Add New Robot" << endl;
        cout << "2. Modify Robot Status" << endl;
        cout << "3. View Robot Details" << endl;
        cout << "4. Back" << endl;

        cin >> choice;
        checkInput(&choice);

        switch (choice)
        {
        case 1:
        {
            // Get last auto incremented value
            int lastID = robotList.getSize() + 1;

            // Create new robot and insert at the end
            string newID = "R" + to_string(lastID);

            robotList.insertAtEnd(newID);

            // Print successful message
            cout << "Robot with the ID: " << newID << " has been created successfully!";
        }
        break;
        case 2:
            // Display short lists of available robots
            cout << "\n----------------- List of Available Robots -----------------" << endl;
            robotList.displayShortList();
            cout << "Please select a robot: ";
            cin >> selection; // Prompt user to select a robot
            checkInput(&selection);

            // Display error message for invalid ID
            if (selection > robotList.getSize() || selection <= 0)
            {
                cout << "Invalid robot selection.";
            }
            else // Else, prompt for status selection
            {
                // Store selected ID as string
                int selectedID = selection;
                string ID = "R" + to_string(selectedID);

                // Get status selection and make it into 0-indexed
                int option = selectStatusMenu() - 1;

                Status chosenStatus;

                switch (option)
                {
                case 0:
                    chosenStatus = AVAILABLE;
                    break;

                case 1:
                    chosenStatus = MAINTENANCE;
                    break;

                case 2:
                    chosenStatus = BUSY;
                default:
                    cout << "Error!";
                }

                // Set status by ID
                robotList.setStatusByID(ID, chosenStatus);
            }

            break;
        case 3:
            cout << "\n----------------- List of Available Robots -----------------" << endl;
            robotList.displayList(); // Display the entire robot list
            break;
        case 4:
            cout << "Returning..." << endl;
            isExit = true;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }
}

int selectStatusMenu()
{
    int option;

    cout << "1. Available" << endl
         << "2. Maintenance" << endl
         << "3. Busy" << endl;
    cout << "Please select a status to modify" << endl;
    cin >> option;
    checkInput(&option);

    return option;
}
