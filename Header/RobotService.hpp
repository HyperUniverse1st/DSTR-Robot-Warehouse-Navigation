#include "../Header/RobotList.hpp"
#include "../Header/RobotQueue.hpp"
#include <limits>
#include <iostream>
using namespace std;

class RobotService
{
public:
    // Function to simulate robot task assignment
    void simulateAssignment(OrderManagement &, RobotList *);

    // Function to assign tasks to robot
    void assignTask(OrderNode *, Robot &, RobotQueue &);

    // Function to handle order completion
    void completeOrder(OrderManagement &, Robot &, RobotQueue &);

    // Function to display submenu for robot services (CRUD)
    void robotSubMenu(RobotList &);

    // Function to display robot status selection, then return option
    int selectStatusMenu();

    // Function to validate input
    void checkInput(int *);
};