#ifndef ROBOTLIST_HPP
#define ROBOTLIST_HPP
#include "Robot.hpp"

class RobotList
{

    int head;
    int size;
    int capacity;

public:
    Robot *arr;
    RobotList(int);
    ~RobotList();
    bool isEmpty();
    Robot createNewNode(string);
    void extendArray();
    void insertAtEnd(string);
    int getSize();
    string getStatus(Robot);
    void displayList();
    void displayShortList();
    void setStatusByID(string, Status);
};

#endif