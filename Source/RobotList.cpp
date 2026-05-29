#include "../Header/RobotList.hpp"

RobotList::RobotList(int capacity)
{
    head = -1;
    size = 0;
    this->capacity = capacity;
    arr = new Robot[capacity];
}

RobotList::~RobotList()
{
    delete[] arr;
    cout << "List have been deleted." << endl;
}

Robot RobotList::createNewNode(string ID)
{

    // Create a new Robot object
    Robot robot;

    // Initialise variables
    robot.ID = ID;
    robot.status = AVAILABLE;
    robot.workLoad = 0;
    robot.currOrder = nullptr;

    // Return value
    return robot;
}

// Function to check if the array is currently empty
bool RobotList::isEmpty()
{
    return head == -1;
}

// Function to insert robort at the end of the array
void RobotList::insertAtEnd(string ID)
{
    // Crete a new robot
    Robot newRobot = createNewNode(ID);

    // If the size has reached its capacity, extend current array
    if (size == capacity)
    {
        extendArray();
    }

    // If the array is empty, set head to 0
    if (isEmpty())
    {
        head = 0;
    }

    // Insert new robot into array, then increment size vaue
    arr[size++] = newRobot;
}

// Function to expand the capacity of the original arr
void RobotList::extendArray()
{
    // Create a new arr with one additional capacity
    capacity = capacity * 2;
    Robot *newArr = new Robot[capacity];

    // Deep copy from old arr to new arr
    for (int i = 0; i < size; i++)
    {
        newArr[i] = arr[i];
    }

    // Delete current array to free space
    delete[] arr;

    // Assign current array as new array
    arr = newArr;
}

int RobotList::getSize()
{
    return size;
}

// Function to convert Status enum in robot into string
string RobotList::getStatus(Robot robot)
{
    // Switch case based on enum value
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

// Function to print all robots in the array
void RobotList::displayList()
{

    // Print Table Header
    cout << left << setw(5) << "No."
         << setw(12) << "Robot ID"
         << setw(20) << "Status"
         << setw(16) << "Workload" << "\n";
    cout << string(42, '-') << "\n";

    // Print Table Rows
    for (int i = 0; i < size; i++)
    {
        cout << left << setw(5) << (i + 1)
             << setw(12) << arr[i].ID
             << setw(15) << getStatus(arr[i])
             << setw(10) << arr[i].workLoad << "\n";
    }
}

// Function to display short list of robots
void RobotList::displayShortList()
{
    // Loop through every element in the array
    // Print only the Robot ID
    for (int i = 0; i < size; i++)
    {
        cout << (i + 1) << ") Robot ID: " << arr[i].ID << endl;
    }
}

// Setter method to modify status based on ID
void RobotList::setStatusByID(string ID, Status newStatus)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i].ID == ID)
        {
            arr[i].status = newStatus;
        }
    }
}