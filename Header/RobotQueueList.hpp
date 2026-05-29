#ifndef ROBOTQUEUELIST_HPP
#define ROBOTQUEUELIST_HPP
#include <iostream>
#include <iomanip>
#include "Robot.hpp"
using namespace std;

class RobotQueueList
{
    Robot *front;
    Robot *rear;
    int size;

public:
    int minLoad;
    string slowestRobot;

    RobotQueueList();
    ~RobotQueueList();
    bool isEmpty();
    bool isFull();
    int getsize();
    void enqueue(Robot *);
    Robot *dequeue();
    void moveNthFront(Robot *);
    Robot *peek();
    string getStatus(Robot *);
    Robot *createNewNode(string);
    void displayQueue();
    void setStatusByID(string, Status);
};

#endif