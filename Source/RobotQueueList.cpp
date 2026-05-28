#include "../Header/RobotQueueList.hpp"

RobotQueueList::RobotQueueList(int capacity)
{
    front = rear = nullptr;
    minLoad = INT_MAX;
    slowestRobot = "";
    currSize = 0;
}

RobotQueueList::~RobotQueueList()
{
    // TODO
}

bool RobotQueueList::isEmpty()
{
    return front == nullptr;
}

bool RobotQueueList::isFull()
{
    return rear->next == front;
}

int RobotQueueList::getCurrSize()
{
    return currSize;
}

Robot RobotQueueList::createNewNode(string ID)
{
    Robot newRobot;

    newRobot.ID = ID;
    newRobot.status = AVAILABLE;
    newRobot.workLoad = 0;
    newRobot.currOrder = nullptr;
    newRobot.next = nullptr;
    newRobot.prev = nullptr;

    return newRobot;
}

// Function to insert robot into queue
void RobotQueueList::enqueue(Robot *robot)
{
    // If the queue is currently full, print error message and then return
    if (isFull())
    {
        cout << "The queue is now full!" << endl;
        return;
    }

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

    currSize++;

    // If the current robot is the slowest robot, move to front
    if (robot->ID == slowestRobot)
    {
        displayQueue();
        moveNthFront(rear);
    }
}

// Function to move Nth indexed robot to front as priority queue
void RobotQueueList::moveNthFront(Robot *robot)
{

    // Reminder: robot is ALWAYS REAR
    //  Case 1:
    //   R1(front) -> R2 -> R3 -> R5 -> R4 (robot) (rear)
    //   R1 (front) -> R2 -> R3 -> R5 (rear) -> R4 (robot)
    //  R1 -> R2 -> R3 -> R5 -> R1      detached -- R4
    //   R4(robot)(front) -> R1 -> R2 -> R3 -> R5(rear)

    // Case 2:
    //  R1 -> R2 (front) -> R3 -> R5 -> R4(robot) (rear)  //Print R2, R3, R5, R4
    // R1- > R4 (robot) (front) -> R2 -> R3 -> R5 (rear) //Print R4,R2,R3,R5

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
Robot RobotQueueList::dequeue()
{
    // If the queue is empty, print error message and return empty value
    if (isEmpty())
    {
        cout << "Queue underflow! The queue is currently empty.";
        return Robot(); // Return default constructor value as "null" value
    }

    // Store front value as temporary value
    Robot temp = queue[front];

    // Check if end of queue
    if (front == rear)
    {

        // Set queue as empty
        front = rear = -1;
    }
    else
    {
        // Else, increment front value and then bound the value based on capacity, using the modulo operator
        // To enforce cycle in the queue
        front = (front + 1) % capacity;
    }

    // Decrease current element size
    currSize--;

    // Return temp value
    return temp;
}

// Function to view first item
Robot RobotQueueList::peek()
{
    // If queue is empty, display error message
    if (isEmpty())
    {
        cout << "The queue is currently empty.";
        return Robot();
    }

    // Else Return the first item
    return queue[front];
}

// Function to convert the enum Status into string value
string RobotQueueList::getStatus(Robot robot)
{

    // Switch case for enum since it's indexed
    switch (robot.status)
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
void RobotQueueList::displayQueue()
{
    // If queue is empty, display error message
    if (isEmpty())
    {
        cout << "The queue is currently empty.";
        return;
    }

    // Declare temp variable to hold front index
    int temp = front;

    // Loop from front until rear
    while (true)
    {
        // Print each robot details
        // cout << "Robot ID: " << queue[temp].ID << endl
        //      << "Work Load: " << queue[temp].workLoad << endl;

        cout << queue[temp].ID << " : " << temp << " : " << queue[temp].workLoad << " , ";

        // If temp is rear, break the loop
        if (temp == rear)
        {
            break;
        }

        // Increment temp by 1 with cycle
        temp = (temp + 1) % capacity;
    }
}