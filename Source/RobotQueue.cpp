#include "../Header/RobotQueue.hpp"

RobotQueue::RobotQueue(int capacity)
{
    front = rear = -1;
    this->capacity = capacity;
    queue = new Robot[capacity];
}

RobotQueue::~RobotQueue()
{
    delete[] queue;
}

bool RobotQueue::isEmpty()
{
    return front == -1;
}

bool RobotQueue::isFull()
{
    return (rear + 1) % capacity == front;
}

void RobotQueue::enqueue(Robot &robot)
{
    if (isFull())
    {
        cout << "Robot Queue is full! Unable to add more" << endl;
        return;
    }

    if (isEmpty())
    {
        front = rear = 0;
    }
    else
    {
        rear = (rear + 1) % capacity;
    }

    queue[rear] = robot;
}

Robot RobotQueue::dequeue()
{
    if (isEmpty())
    {
        cout << "Queue underflow! No robots available at the moment." << endl;
        return Robot();
    }

    Robot robot = queue[front];

    if (front == rear)
    {
        front = rear = -1;
    }
    else
    {
        front = (front + 1) % capacity;
    }

    return robot;
}

void RobotQueue::peek()
{
    if (isEmpty())
    {
        cout << "Queue underflow! No robots available at the moment." << endl;
        return;
    }

    cout << "Next Robot in Queue: " << queue[front].ID << endl;
}

void RobotQueue::displayQueue()
{
    if (isEmpty())
    {
        cout << "No robots available at the moment." << endl;
        return;
    }

    int i = front;

    while (true)
    {
        cout << "Robot ID: " << queue[i].ID << endl;

        if (i == rear)
            break;

        i = (i + 1) % capacity;
    }
}