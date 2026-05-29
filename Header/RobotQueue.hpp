#ifndef ROBOTQUEUELIST_HPP
#define ROBOTQUEUELIST_HPP
#include <iostream>
#include <iomanip>
#include "Robot.hpp"
using namespace std;

class RobotQueue
{
    Robot *front;
    Robot *rear;
    int size;

public:
    int minLoad;
    string slowestRobot;

    RobotQueue();
    ~RobotQueue();
    bool isEmpty();
    bool isFull();
    int getsize();
    void enqueue(Robot *);
    Robot *dequeue();
    void moveNthFront(Robot *);
    Robot *peek();
};

#endif