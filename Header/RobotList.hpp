#ifndef ROBOTLIST_HPP
#define ROBOTLIST_HPP
#include "Robot.hpp"

class RobotList
{

    int head;
    int tail;
    int curr;
    int capacity;

public:
    Robot *arr;
    RobotList(int);
    ~RobotList();
    bool isEmpty();
    Robot createNewNode(string);
    void extendArray();
    void insertAtTail(string);
    int getSize();
    string getStatus(Robot);
    void displayList();
    int getNextIndex();
};

#endif