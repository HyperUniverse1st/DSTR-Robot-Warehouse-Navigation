#ifndef ROBOT_HPP
#define ROBOT_HPP
#include <iostream>
#include <iomanip>
#include "Task1_Order.hpp"
using namespace std;

enum Status
{
    AVAILABLE,
    MAINTENANCE,
    BUSY
};

struct Robot
{
    string ID;
    Status status;
    int workLoad;
    OrderNode *currOrder;
    Robot *next;
    Robot *prev;
};

#endif