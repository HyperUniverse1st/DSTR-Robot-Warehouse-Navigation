#include "../Header/Task2_RobotService.hpp"
#include "../Header/Task3_RobotNavigation.hpp"
#include "../Header/Task4_WarehouseSystem.hpp"
#include "../Header/Task5_WarehouseTree.hpp"

// Function to simulate robot task assignment
void RobotService::simulateAssignment(OrderManagement &orderManagement, RobotList *robotList, WarehouseTree &warehouse, DoublyLinkedList &itemList)
{

    // Declare RobotQueue objects
    RobotQueue *queue = new RobotQueue();

    // Insert all robots in the array into queue
    for (int i = 0; i < robotList->getSize(); i++)
    {
        // Insert pointer to array element
        queue->enqueue(&robotList->arr[i]);
    }

    // Declare difference parameter to identify acceptable difference range in workload
    int diffParameter = 5;

    // Loop while there is still pending order
    while (!orderManagement.pendingQueue.isEmpty())
    {

        // Dequeue first robot
        Robot *currRobot = queue->dequeue();

        // Check the status
        // If available, assign task
        if (currRobot->status == AVAILABLE)
        {
            // If the current robot's workload is least, that means it's the slowest
            if (currRobot->workLoad < queue->minLoad)
            {
                // Set the new workload as the new minLoad
                queue->minLoad = currRobot->workLoad;

                // Identify slowest robot
                queue->leastLoadedRobot = currRobot->ID;
            }

            // If the difference in workload with the next in line is between difference parameter,
            // Assume the workload is balanced, so reset slowest robot
            int diff = currRobot->workLoad - queue->peek()->workLoad;

            // Also check if the value next in line is the same
            bool isSame = currRobot->workLoad == queue->peek()->workLoad;

            if ((currRobot->ID == queue->leastLoadedRobot && diff >= diffParameter) || isSame)
            {
                queue->minLoad = INT_MAX;
                queue->leastLoadedRobot = "";
            }

            // Get first pending order
            OrderNode *pendingOrder = orderManagement.assignToRobot();

            // Assign the pending order to the current robot
            assignTask(pendingOrder, *currRobot, *queue, warehouse, itemList);
            completeOrder(orderManagement, *currRobot, *queue);
        }
        else
        {
            // Else, enqueue the robot back to "skip" its turn
            queue->enqueue(currRobot);
        }
    }
}

// Function to assign tasks to robot
void RobotService::assignTask(OrderNode *order, Robot &robot, RobotQueue &queue, WarehouseTree &warehouse, DoublyLinkedList &itemList)
{
    cout << "Order ID: " << order->orderId << " is assigned to Robot with ID: " << robot.ID << endl;
    robot.currOrder = order;
    robot.status = BUSY;
    robot.workLoad++;

    //======================= Module 3 Part =======================
    string targetItem = order->itemName; // Get target item

    // Get Location and Path
    string itemLocation = itemList.getItemLocation(targetItem);
    TreeNode *targetNode = warehouse.findLocation(itemLocation);
    string routeForRobot = warehouse.getPath(itemLocation);

    cout << "\n===== Route Provided to Task 3 =====" << endl;
    if (targetNode != nullptr)
    {
        cout << "Target Node: " << targetNode->type << " - " << targetNode->name << endl;
        cout << "Route: " << routeForRobot << endl;
    }

    const int MAX_PATH_NODES = 10;
    TreeNode *pathNodes[MAX_PATH_NODES];
    int pathCount = warehouse.getPathNodes(itemLocation, pathNodes, MAX_PATH_NODES);

    Stack directStack;
    Stack logStack;

    TreeNode *root = warehouse.getRoot();

    // Print navigation
    navigateGeneralTree(root, root, directStack, logStack, itemLocation);

    //========================== END OF CODE ==================================
}

// Function to handle order completion
void RobotService::completeOrder(OrderManagement &orderManagement, Robot &robot, RobotQueue &queue)
{
    // After completion, enqueue back the robot
    robot.status = AVAILABLE;
    queue.enqueue(&robot);

    // Set order as completed
    orderManagement.completeOrder();

    // Print completion message
    cout << "Robot with ID: " << robot.ID << " has completed its order: " << robot.currOrder->orderId << endl;
    cout << string(60, '=') << endl;
}

// Function to display submenu for robot services (CRUD)
void RobotService::robotSubMenu(RobotList &robotList)
{
    int choice;
    int selection;
    while (true)
    {
        cout << "\n----------------- Order Management System -----------------" << endl;
        cout << "1. Add New Robot" << endl;
        cout << "2. Modify Robot Status" << endl;
        cout << "3. View Robot Details" << endl;
        cout << "4. Back" << endl;
        cout << "Please select an option: ";
        cin >> choice;
        checkInput(&choice);

        switch (choice)
        {
        case 1:
        {
            // Get last auto incremented value
            int lastID = robotList.getSize() + 1;

            // Create new robot and insert at the end
            string newID = "R" + to_string(lastID);

            robotList.insertAtEnd(newID);

            // Print successful message
            cout << "Robot with the ID: " << newID << " has been created successfully!";
        }
        break;
        case 2:
            // Display short lists of available robots
            cout << "\n----------------- List of Available Robots -----------------" << endl;
            robotList.displayShortList();
            cout << "Please select a robot: ";
            cin >> selection; // Prompt user to select a robot
            checkInput(&selection);

            // Display error message for invalid ID
            if (selection > robotList.getSize() || selection <= 0)
            {
                cout << "Invalid robot selection.";
            }
            else // Else, prompt for status selection
            {
                // Store selected ID as string
                int selectedID = selection;
                string ID = "R" + to_string(selectedID);

                // Get status selection and make it into 0-indexed
                int option = selectStatusMenu() - 1;

                Status chosenStatus;

                switch (option)
                {
                case 0:
                    chosenStatus = AVAILABLE;
                    break;

                case 1:
                    chosenStatus = MAINTENANCE;
                    break;

                case 2:
                    chosenStatus = BUSY;
                default:
                    cout << "Error!";
                }

                // Set status by ID
                robotList.setStatusByID(ID, chosenStatus);
            }

            break;
        case 3:
            cout << "\n----------------- List of Available Robots -----------------" << endl;
            robotList.displayList(); // Display the entire robot list
            break;
        case 4:
            cout << "Returning..." << endl;
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }
}

// Function to display robot status selection, then return option
int RobotService::selectStatusMenu()
{
    int option;

    cout << "1. Available" << endl
         << "2. Maintenance" << endl
         << "3. Busy" << endl;
    cout << "Please select a status to modify: ";
    cin >> option;
    checkInput(&option);

    return option;
}

// Function to validate input
void RobotService::checkInput(int *option)
{
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input!" << endl;
        cout << "Please select an option: ";
        cin >> *option;
    }
}
