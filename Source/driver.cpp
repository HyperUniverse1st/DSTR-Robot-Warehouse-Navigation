#include "OrderQueue.cpp"
#include "../WarehouseTree.h"
#include "../Header/RobotList.hpp"
#include "../Header/RobotQueue.hpp"
#include <iostream>
#include <limits>
using namespace std;

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

// DOES NOT WORK, need more testing
// int main()
// {

//     OrderManagement orderManagement;

//     // Insert 100 dummy orders
//     for (int i = 0; i < 1000; i++)
//     {
//         orderManagement.addPendingOrder("test", "test", i + 1);
//     }

//     // Initialise 5 robots in master list
//     RobotList *robots = new RobotList(5);
//     for (int i = 0; i < robots->getSize(); i++)
//     {
//         string ID = "R" + to_string(i + 1);
//         robots->insertAtTail(ID);
//     }

//     int capacity = 5;
//     RobotQueue *queue = new RobotQueue(capacity);

//     // For each value in robots, insert into queue

//     for (int i = 0; i < robots->getSize(); i++)
//     {
//         queue->enqueue(robots->arr[i]);
//     }

//     // Loop while there are still orders
//     int diffParameter = 5;

//     queue->queue[2].status = MAINTENANCE;
//     queue->queue[3].status = MAINTENANCE;

//     int counter = 0;
//     while (!orderManagement.pendingQueue.isEmpty())
//     {

//         if (counter == 200)
//         {
//             queue->queue[2].status = AVAILABLE;
//         }
//         else if (counter == 5000)
//         {
//             queue->queue[3].status = AVAILABLE;
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
//             if (currRobot.ID == queue->slowestRobot && (currRobot.workLoad - queue->peek().workLoad) >= diffParameter)
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

//     cout << endl
//          << endl;
//     robots->displayList();
//     return 0;
// }

void robotSubMenu(RobotQueue &queue);
int main()
{

    OrderManagement orderManagement;

    // Insert 100 dummy orders
    for (int i = 0; i < 10000; i++)
    {
        orderManagement.addPendingOrder("test", "test", i + 1);
    }
    cout << endl
         << endl;

    // Initialise 5 robots
    RobotQueue *queue = new RobotQueue(10);

    // Initialise Robots into Queue
    for (int i = 0; i < 5; i++)
    {
        string ID = "R" + to_string(i + 1);
        Robot newRobot = queue->createNewNode(ID);
        queue->enqueue(newRobot);
    }

    int diffParameter = 5;

    string id1 = queue->queue[1].ID;
    string id2 = queue->queue[2].ID;

    queue->setStatusByID(id1, MAINTENANCE);
    queue->setStatusByID(id2, MAINTENANCE);

    int counter = 0;
    while (!orderManagement.pendingQueue.isEmpty())
    {

        if (counter == 1000)
        {
            queue->setStatusByID(id1, AVAILABLE);
        }
        else if (counter == 6000)
        {
            queue->setStatusByID(id2, AVAILABLE);
        }

        // Dequeue first robot
        Robot currRobot = queue->dequeue();

        // Check the status
        // If available, assign task
        if (currRobot.status == AVAILABLE)
        {
            // If the current robot's workload is least, that means it's the slowest
            if (currRobot.workLoad < queue->minLoad)
            {
                // Set the new workload as the new minLoad
                queue->minLoad = currRobot.workLoad;

                // Identify slowest robot
                queue->slowestRobot = currRobot.ID;
            }

            // If the difference in workload with the next in line is between difference parameter,
            // Assume the workload is balanced, so reset slowest robot
            int diff = currRobot.workLoad - queue->peek().workLoad;
            bool isSame = currRobot.workLoad == queue->peek().workLoad;

            if ((currRobot.ID == queue->slowestRobot && diff >= diffParameter) || isSame)
            {
                queue->minLoad = INT_MAX;
                queue->slowestRobot = "";
            }

            // Get first pending order
            OrderNode *currOrder = orderManagement.assignToRobot();
            assignTask(currOrder, currRobot, *queue);
        }
        else
        {
            // Else, enqueue the robot back to "skip" its turn
            queue->enqueue(currRobot);
        }
        counter++;
    }

    // robotSubMenu(*queue);
    return 0;
}

void robotSubMenu(RobotQueue &queue)
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

            break;
        case 2:
            cout << "\n----------------- List of Available Robots -----------------" << endl;
            queue.displayQueue();
            cin >> selection;
            checkInput(&selection);

            break;
        case 3:

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
