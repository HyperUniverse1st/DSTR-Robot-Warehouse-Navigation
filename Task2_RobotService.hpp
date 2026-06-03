#include "Task2_RobotList.hpp"
#include "Task2_RobotQueue.hpp"
#include "Task4_WarehouseSystem.hpp"
#include "Task5_WarehouseTree.hpp"

#include <limits>
#include <iostream>
using namespace std;

class RobotService
{
public:
    // Function to simulate robot task assignment
    void simulateAssignment(OrderManagement &, RobotList *, WarehouseTree &, DoublyLinkedList &);

    // Function to assign tasks to robot
    void assignTask(OrderNode *, Robot &, RobotQueue &, WarehouseTree &warehouse, DoublyLinkedList &);

    // Function to handle order completion
    void completeOrder(OrderManagement &, Robot &, RobotQueue &);

    // Function to display submenu for robot services (CRUD)
    void robotSubMenu(RobotList &);

    // Function to display robot status selection, then return option
    int selectStatusMenu();

    // Function to validate input
    void checkInput(int *);
};