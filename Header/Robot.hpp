#ifndef ROBOT_HPP
#define ROBOT_HPP
#include <iostream>
#include <iomanip>
using namespace std;

// Order Node Structure
struct OrderNode
{
    int orderId;
    string customerName;
    string itemList;
    string status; //""Pending"", ""Processing"", ""Completed""
    double orderAmount;
    OrderNode *next;

    OrderNode(int id, string name, string items, double amount)
    {
        orderId = id;
        customerName = name;
        itemList = items;
        status = "Pending";
        orderAmount = amount;
        next = nullptr;
    }
};

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
};

#endif