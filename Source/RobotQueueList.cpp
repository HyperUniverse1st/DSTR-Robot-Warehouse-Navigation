#include "../Header/RobotQueue.hpp"

RobotQueue::RobotQueue()
{
    front = rear = nullptr;
    minLoad = INT_MAX;
    slowestRobot = "";
    size = 0;
}

RobotQueue::~RobotQueue()
{
    Robot *temp = front;

    while (true)
    {
        if (temp == rear)
        {
            break;
        }

        front = front->next;
        delete temp;

        temp = front;
    }

    delete temp;
}

bool RobotQueue::isEmpty()
{
    return front == nullptr;
}

int RobotQueue::getsize()
{
    return size;
}

Robot *RobotQueue::createNewNode(string ID)
{
    Robot *newRobot = new Robot();

    newRobot->ID = ID;
    newRobot->status = AVAILABLE;
    newRobot->workLoad = 0;
    newRobot->currOrder = nullptr;
    newRobot->next = nullptr;
    newRobot->prev = nullptr;

    return newRobot;
}

// Function to insert robot into queue
void RobotQueue::enqueue(Robot *robot)
{
    // If the queue is currently empty, set front and rear to 0 index
    if (isEmpty())
    {
        front = rear = robot;
    }
    else
    {
        // Else, insert the robot at the rear, then update the new rear value
        rear->next = robot;
        robot->prev = rear;
        robot->next = front;

        rear = robot;
    }

    size++;

    // If the current robot is the slowest robot, move to front
    if (robot->ID == slowestRobot)
    {
        displayQueue();
        moveNthFront(rear);
    }
}

// Function to move Nth indexed robot to front as priority queue
void RobotQueue::moveNthFront(Robot *robot)
{

    // Keep looping until the index is at front
    while (true)
    {

        // If the robot is already front, break the loop
        if (robot == front)
        {
            break;
        }

        // Since robot is always rear, move rear to the previous value
        rear = robot->prev;

        // If robot next is front, just make robot as front, else swap pointers
        if (robot->next == front)
        {
            front = robot;
        }
        else
        {
            // Swap the pointer locations to move robot to the front
            // Detach robot from the list
            robot->prev->next = robot->next;

            // Insert robot at front
            robot->next = front;
            front->prev->next = robot;

            robot->prev = front->prev;
            front->prev = robot;

            // Make robot as front
            front = robot;
        }
    }
}

// Function to remove first item in queue
Robot *RobotQueue::dequeue()
{
    // If the queue is empty, print error message and return empty value
    if (isEmpty())
    {
        cout << "Queue underflow! The queue is currently empty.";
        return nullptr;
    }

    // Store front value as temporary value
    Robot *temp = front;

    // Check if end of queue
    if (front == rear)
    {

        // Set queue as empty
        front = rear = nullptr;
    }
    else
    {
        // Else, detach front from the queue, then set the next in line as front
        rear->next = front->next;
        front->next->prev = front->prev;

        front = front->next;
    }

    // Decrease current element size
    size--;

    // Return temp value
    return temp;
}

// Function to view first item
Robot *RobotQueue::peek()
{
    // If queue is empty, display error message
    if (isEmpty())
    {
        cout << "The queue is currently empty.";
        return nullptr;
    }

    // Else Return the first item
    return front;
}

// Function to convert the enum Status into string value
string RobotQueue::getStatus(Robot *robot)
{

    // Switch case for enum since it's indexed
    switch (robot->status)
    {
    case 0:
        return "Available"; // First status
    case 1:
        return "Maintenance"; // Second status
    case 2:
        return "Busy"; // Third status
    default:
        return "Error"; // Error handling
    }
}

// Function to display queue
void RobotQueue::displayQueue()
{
    // If queue is empty, display error message
    if (isEmpty())
    {
        cout << "The queue is currently empty.";
        return;
    }

    // Declare temp variable to hold front index
    Robot *temp = front;

    // Loop from front until rear
    while (true)
    {
        // Print each robot details
        // cout << "Robot ID: " << queue[temp].ID << endl
        //      << "Work Load: " << queue[temp].workLoad << endl;

        cout << temp->ID << " : " << temp->workLoad << " , ";

        // If temp is rear, break the loop
        if (temp == rear)
        {
            break;
        }

        // Move temp to next value
        temp = temp->next;
    }
}

void RobotQueue::setStatusByID(string ID, Status status)
{
    Robot *temp = front;
    while (true)
    {
        if (temp->ID == ID)
        {
            temp->status = status;
            return;
        }
        if (temp == rear)
            break;
        temp = temp->next;
    }
}