#include "StackNavigation.hpp"

Stack::Stack() {
    top = NULL;
}

bool Stack::isEmpty() {
    return top == NULL;
}

void Stack::push(string x) {

    StackNode* temp = new StackNode();

    temp->data = x;
    temp->next = top;

    top = temp;
}

string Stack::pop() {

    if (isEmpty()) {
        cout << "Stack Underflow\n";
        return "";
    }

    string val = top->data;

    StackNode* temp = top;
    top = top->next;

    delete temp;

    return val;
}

string Stack::peek() {

    if (isEmpty())
        return "";

    return top->data;
}

void Stack::display() {

    StackNode* current = top;

    while (current != NULL) {

        cout << current->data << endl;

        current = current->next;
    }
}

Stack::Stack(const Stack& other)
{
    top = nullptr;

    if (other.top == nullptr)
        return;

    StackNode* curr = other.top;
    StackNode* reversed = nullptr;

    while (curr != nullptr)
    {
        StackNode* node = new StackNode();
        node->data = curr->data;
        node->next = reversed;
        reversed = node;

        curr = curr->next;
    }

    top = reversed;
}