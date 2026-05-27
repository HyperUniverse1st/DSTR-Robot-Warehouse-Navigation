#include "OrderQueue.cpp"
#include "../WarehouseTree.h"
#include "../Header/RobotList.hpp"
#include "../Header/RobotQueue.hpp"
#include <iostream>
using namespace std;

void assignTask(OrderNode *order, Robot &robot)
{
    robot.currOrder = order;
    robot.workLoad++;
}

int main()
{

    OrderManagement orderManagement;

    // Insert 100 dummy orders
    for (int i = 0; i < 100; i++)
    {
        orderManagement.addPendingOrder("test", "test", i + 1);
    }
    cout << endl
         << endl;

    // Initialise 5 robots
    int capacity = 5;
    RobotList *robots = new RobotList(10);
    RobotQueue *queue = new RobotQueue(capacity);
    for (int i = 0; i < robots->getSize(); i++)
    {
        string ID = "R" + to_string(i + 1);
        robots->insertAtTail(ID);
    }

    robots->displayList();

    // Loop while there are still orders
    while (!orderManagement.pendingQueue.isEmpty())
    {

        Robot &robot = robots->arr[robots->getNextIndex()];
        if (robot.status == AVAILABLE && !queue->isFull())
        {
            queue->enqueue(robot);
            robot.status = BUSY;
        }

        while (!queue->isEmpty())
        {

            OrderNode *currOrder = orderManagement.assignToRobot();

            Robot currRobot = queue->dequeue();
            if (currRobot.ID != "")
            {
                assignTask(currOrder, currRobot);
            }
        }

        // Assignment Logic
        // 1. Load all robots into masterlist
        // 2. Load robots that are available to work into queue with the cap of 5
        // 3. For each robot in the queue, assign task
    }

    cout << endl
         << endl;
    robots->displayList();
    return 0;
}
