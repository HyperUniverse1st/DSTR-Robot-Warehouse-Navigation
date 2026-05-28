#include "../Header/RobotQueue.hpp"

RobotQueue::RobotQueue(int capacity)
{
    front = rear = -1;
    this->capacity = capacity;
    queue = new Robot[capacity];
    minLoad = INT_MAX;
    slowestRobot = "";
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

int RobotQueue::getCapacity()
{
    return capacity;
}

Robot RobotQueue::createNewNode(string ID)
{
    Robot newRobot;

    newRobot.ID = ID;
    newRobot.status = AVAILABLE;
    newRobot.workLoad = 0;
    newRobot.currOrder = nullptr;

    return newRobot;
}

// Function to insert robot into queue
void RobotQueue::enqueue(Robot &robot)
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
        front = rear = 0;
    }
    else
    {
        // Else, increment rear value and then bound the value based on capacity, using the modulo operator
        // To enforce cycle in the queue
        rear = (rear + 1) % capacity;
    }

    // Insert robot into queue
    queue[rear] = robot;

    // If the current robot is the slowest robot, move to front
    if (robot.ID == slowestRobot)
    {
        displayQueue();
        moveNthFront(rear);
    }
}

// Function to move Nth indexed robot to front as priority queue
void RobotQueue::moveNthFront(int index)
{
    if (index > capacity)
    {
        cout << "Index is higher than capacity. Invalid value!";
        return;
    }

    // Case 1:
    //  0           1      2    3            4
    //  1(front)  -> 2  -> 3 -> 4 (index) -> 5 (rear)
    // 1(front) -> 2 -> 3 -> 5(rear) -> 4 [Swap index 3 with 4]
    // 1 -> 2 -> 3 -> 5 (rear) -> 4 (front) [If index + 1 is front, make front = index]

    // Case 2:
    //  0   1     2           3           4
    //  1 -> 2 -> 3(front) -> 4(index) -> 5(rear)

    //  0   1    2    3    4 (index)
    //  1-> 2 -> 3(front) -> 5(rear) -> 4
    //  4 -> 2 -> 3 -> 5 -> 1
    //  2 -> 4(front) -> 3 -> 5 (rear) -> 1

    // Case 3:
    //  1 -> 2(front) -> 3 -> 4 -> 5(index) (rear)
    //  1 -> 2 -> 3 -> 4(rear) -> 5 (index) [swap 5 with 1]
    //  5(front) -> 2 -> 3 -> 4 (rear) -> 1

    // Case nothing..
    //  0      1     2        3    4
    //  4 -> 1(front) -> 2 -> 3 -> 5 (rear)

    // Shift: 0 -> 1, 1 -> 2 currVal[i] = currVal[i-1]

    // Keep looping until the index is at front
    while (true)
    {

        // If index is already front, break
        if (index == front)
        {
            break;
        }

        // If index is rear, make the previous value as rear
        if (index == rear)
        {
            rear = (index - 1 + capacity) % capacity;
        }

        // If next value is not front, then swap
        if ((index + 1) % capacity != front)
        {
            // Create temp value to swap
            Robot temp = queue[index];
            queue[index] = queue[(index + 1) % capacity];

            // Increment index after swapping with next value
            index = (index + 1) % capacity;

            // Insert temp into new index
            queue[index] = temp;
        }
        else
        {
            // Else, just make current index as front
            front = index;
            break;
        }
    }
}

// Function to remove first item in queue
Robot RobotQueue::dequeue()
{
    // If the queue is empty, print error message and return empty value
    if (isEmpty())
    {
        cout << "Queue underflow! The queue is currently empty.";
        return Robot(); // Return default constructor value as "null" value
    }

    // Store front value as temporary value
    Robot temp = queue[front];

    // Remove the front value
    queue[front] = Robot();

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

    // Return temp value
    return temp;
}

// Function to view first item
Robot RobotQueue::peek()
{
    // If queue is empty, return blank values
    if (isEmpty())
    {
        return Robot();
    }

    // Else Return the first item
    return queue[front];
}

// Function to convert the enum Status into string value
string RobotQueue::getStatus(Robot robot)
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
void RobotQueue::displayQueue()
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

void RobotQueue::setStatusByID(string ID, Status status)
{
    int temp = front;
    while (true)
    {
        if (queue[temp].ID == ID)
        {
            queue[temp].status = status;
            return;
        }
        if (temp == rear)
            break;
        temp = (temp + 1) % capacity;
    }
}