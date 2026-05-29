#include "OrderQueue.cpp"
#include "../WarehouseTree.h"
#include "../Header/RobotList.hpp"
#include "../Header/RobotQueue.hpp"
#include "../Header/RobotQueueList.hpp"
#include <iostream>
#include <limits>
#include <chrono>
using namespace std;
using namespace std::chrono;

void assignTask(OrderNode *order, Robot &robot, RobotQueue &queue)
{
    cout << "Order ID: " << order->orderId << " is assigned to " << robot.ID << endl;
    robot.currOrder = order;
    robot.status = BUSY;
    robot.workLoad++;

    // After completion, enqueue back the robot
    robot.status = AVAILABLE;
    queue.enqueue(robot);
}

// Method Overloading for Linked List Implementation
void assignTask(OrderNode *order, Robot &robot, RobotQueueList &queue)
{
    cout << "Order ID: " << order->orderId << " is assigned to " << robot.ID << endl;
    robot.currOrder = order;
    robot.status = BUSY;
    robot.workLoad++;

    // After completion, enqueue back the robot
    robot.status = AVAILABLE;
    queue.enqueue(&robot);
}

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

// Array implementation : 3155 ms
// int main()
// {

//     OrderManagement orderManagement;

//     // Insert 100 dummy orders
//     for (int i = 0; i < 100; i++)
//     {
//         orderManagement.addPendingOrder("test", "test", i + 1);
//     }
//     cout << endl
//          << endl;

//     // Initialise 5 robots
//     RobotQueue *queue = new RobotQueue(10);

//     // Initialise Robots into Queue
//     for (int i = 0; i < 5; i++)
//     {
//         string ID = "R" + to_string(i + 1);
//         Robot newRobot = queue->createNewNode(ID);
//         queue->enqueue(newRobot);
//     }

//     int diffParameter = 5;

//     string id1 = queue->queue[1].ID;
//     string id2 = queue->queue[2].ID;

//     queue->setStatusByID(id1, MAINTENANCE);
//     queue->setStatusByID(id2, MAINTENANCE);

//     int counter = 0;

//     // Start timer
//     auto start = steady_clock::now();

//     while (!orderManagement.pendingQueue.isEmpty())
//     {

//         if (counter == 1000)
//         {
//             queue->setStatusByID(id1, AVAILABLE);
//         }
//         else if (counter == 6000)
//         {
//             queue->setStatusByID(id2, AVAILABLE);
//         }

//         // Dequeue first robot
//         Robot currRobot = queue->dequeue();

//         // Check the status
//         // If available, assign task
//         if (currRobot.status == AVAILABLE)
//         {
//             // If the current robot's workload is least, that means it's the slowest
//             if (currRobot.workLoad < queue->minLoad)
//             {
//                 // Set the new workload as the new minLoad
//                 queue->minLoad = currRobot.workLoad;

//                 // Identify slowest robot
//                 queue->slowestRobot = currRobot.ID;
//             }

//             // If the difference in workload with the next in line is between difference parameter,
//             // Assume the workload is balanced, so reset slowest robot
//             int diff = currRobot.workLoad - queue->peek().workLoad;
//             bool isSame = currRobot.workLoad == queue->peek().workLoad;

//             if ((currRobot.ID == queue->slowestRobot && diff >= diffParameter) || isSame)
//             {
//                 queue->minLoad = INT_MAX;
//                 queue->slowestRobot = "";
//             }

//             // Get first pending order
//             OrderNode *currOrder = orderManagement.assignToRobot();
//             assignTask(currOrder, currRobot, *queue);
//         }
//         else
//         {
//             // Else, enqueue the robot back to "skip" its turn
//             queue->enqueue(currRobot);
//         }
//         counter++;
//     }

//     // End Timer
//     auto end = steady_clock::now();

//     // Get Duration
//     auto duration = duration_cast<milliseconds>(end - start);
//     cout << "\n Time Taken for Array: " << duration.count() << " ms";

//     // robotSubMenu(*queue);

//     return 0;
// }

// LINKED LIST IMPLEMENTATION: 2509ms
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

    // Declare RobotList and RobotQueueList objects
    RobotList *robotList = new RobotList(2);
    RobotQueueList *queue = new RobotQueueList();

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

    // Test Case: Set status into maintenance
    robotList->setStatusByID(robotList->arr[1].ID, MAINTENANCE);
    robotList->setStatusByID(robotList->arr[2].ID, MAINTENANCE);

    int counter = 0;

    // Start Timer
    auto start = steady_clock::now();

    while (!orderManagement.pendingQueue.isEmpty())
    {

        if (counter == 1000)
        {
            queue->setStatusByID(robotList->arr[1].ID, AVAILABLE);
        }
        else if (counter == 6000)
        {
            queue->setStatusByID(robotList->arr[2].ID, AVAILABLE);
        }

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
        counter++;
    }

    // End Timer
    auto end = steady_clock::now();

    // Get duration
    auto duration = duration_cast<milliseconds>(end - start);

    cout << "\nTime Taken for Linked List: " << duration.count() << " ms";

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
            // Prompt for ID
            // Modify the status

            cout << "\n----------------- List of Available Robots -----------------" << endl;
            robotList.displayShortList();
            cout << "Please select a robot: ";
            cin >> selection;
            checkInput(&selection);

            if (selection > robotList.getSize() || selection <= 0)
            {
                cout << "Invalid robot selection.";
            }
            else
            {
                int selectedID = selection;
                string ID = "R" + to_string(selectedID);

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
            robotList.displayList();
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
