#ifndef ROBOTQUEUE_HPP
#define ROBOTQUEUE_HPP
#include <iostream>
#include <iomanip>
#include "Robot.hpp"
using namespace std;

class RobotQueueList
{
    Robot *front;
    Robot *rear;
    int currSize;

public:
    int minLoad;
    string slowestRobot;

    RobotQueueList(int);
    ~RobotQueueList();
    bool isEmpty();
    bool isFull();
    int getCurrSize();
    Robot createNewNode(string);
    void enqueue(Robot *);
    Robot dequeue();
    void moveNthFront(Robot *);
    Robot peek();
    string getStatus(Robot);
    void displayQueue();
};

#endif