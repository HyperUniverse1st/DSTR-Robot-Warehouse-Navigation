#ifndef ROBOTQUEUE_HPP
#define ROBOTQUEUE_HPP
#include <iostream>
#include <iomanip>
#include "Robot.hpp"
using namespace std;

class RobotQueue
{
    Robot *queue;
    int front;
    int rear;
    int capacity;

public:
    RobotQueue(int);
    ~RobotQueue();
    bool isEmpty();
    bool isFull();
    void enqueue(Robot &);
    Robot dequeue();
    void peek();
    void displayQueue();
};

#endif