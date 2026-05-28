#include "../Header/RobotList.hpp"

RobotList::RobotList(int capacity)
{
    head = tail = -1;
    this->capacity = capacity;
    curr = 0;
    arr = new Robot[capacity];
}

RobotList::~RobotList()
{
    delete[] arr;
    cout << "List have been deleted." << endl;
}

Robot RobotList::createNewNode(string ID)
{

    // Step 1. Create a new Robot object
    Robot robot;

    // Step 2. Initialise variables
    robot.ID = ID;
    robot.status = AVAILABLE;
    robot.workLoad = 0;
    robot.currOrder = nullptr;

    // Step 3. Return value
    return robot;
}

bool RobotList::isEmpty()
{
    return head == -1;
}

// TODO LIST:
// 1. Complete Array Structure as master list
// 2. Complete Circular Queue Structure
// 3. If got time, complete min-heap structure for testing
// 4. Test if I can pass in master list and queue as argument to update the queue
// 5. Create 1000 order test and testing function for simulating working

void RobotList::insertAtTail(string ID)
{
    Robot newNode = createNewNode(ID);

    if (curr == capacity)
    {
        extendArray();
    }

    else if (isEmpty())
    {
        head = tail = 0;
    }

    arr[tail++] = newNode;
}

// Function to expand the capacity of the original arr
void RobotList::extendArray()
{
    // Step 1. Create a new arr with one additional capacity
    capacity = capacity * 2;
    Robot *newArr = new Robot[capacity];

    // Step 2. Deep copy from old arr to new arr
    for (int i = 0; i < tail; i++)
    {
        newArr[i] = arr[i];
    }

    // Step 3. Delete current array to free space
    delete[] arr;

    // Step 4. Assign current array as new array
    arr = newArr;
}

int RobotList::getSize()
{
    return capacity;
}

string RobotList::getStatus(Robot robot)
{
    switch (robot.status)
    {
    case 0:
        return "Available";
    case 1:
        return "Maintenance";
    case 2:
        return "Busy";

    default:
        return "Error.";
    }
}

void RobotList::displayList()
{

    for (int i = 0; i < capacity; i++)
    {
        cout << (i + 1) << ")" << setw(5) << "Robot ID: " << arr[i].ID << endl
             << setw(8) << "Status: " << getStatus(arr[i]) << endl
             << setw(8) << "Workload: " << arr[i].workLoad << endl;
    }
}

int RobotList::getNextIndex()
{
    int temp = curr;
    curr = (curr + 1) % capacity;
    return temp;
}
