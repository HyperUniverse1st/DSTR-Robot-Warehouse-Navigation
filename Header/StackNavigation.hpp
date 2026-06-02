#ifndef STACKNAVIGATION_HPP
#define STACKNAVIGATION_HPP

#include <iostream>
#include <string>

using namespace std;

struct StackNode {
    string data;
    StackNode* next;
};

class Stack {

private:
    StackNode* top;

public:

    Stack();

    bool isEmpty();

    void push(string x);

    string pop();

    string peek();

    void display();

    Stack(const Stack& other);
};

#endif