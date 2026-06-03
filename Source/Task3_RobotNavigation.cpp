#include "../Header/Task3_RobotNavigation.hpp"

using namespace std;

void delay()
{
    this_thread::sleep_for(chrono::milliseconds(1500));
}

TreeNode *findChild(TreeNode *parent, TreeNode *target)
{

    TreeNode *child = parent->firstChild;

    while (child != nullptr)
    {
        if (child == target)
        {
            return child;
        }
        child = child->nextSibling;
    }
    return nullptr;
}

string invertMove(string move)
{
    if (move == "LEFT")
        return "RIGHT";
    if (move == "RIGHT")
        return "LEFT";
    return move;
}

string getReversePath(Stack stack)
{
    string result = "";
    bool first = true;

    while (!stack.isEmpty())
    {
        string move = stack.pop();
        move = invertMove(move);

        if (!first)
        {
            result += " -> ";
        }

        result += move;
        first = false;
    }

    return result;
}

string getForwardPath(Stack stack)
{
    Stack temp;
    string result = "";
    bool first = true;

    while (!stack.isEmpty())
    {
        temp.push(stack.pop());
    }

    while (!temp.isEmpty())
    {
        string move = temp.pop();
        move = invertMove(move);

        if (!first)
        {
            result += " -> ";
        }

        result += move;
        first = false;
    }

    return result;
}

void printBinaryTree(BinaryTreeNode *node, BinaryTreeNode *robotNode, string prefix, bool isLast)
{
    if (node == nullptr)
    {
        return;
    }

    if (prefix.empty())
    {
        if (node == robotNode)
        {
            cout << "[R:" << node->data << "]" << endl;
        }
        else
        {
            cout << node->data << endl;
        }
    }
    else
    {
        cout << prefix;

        if (isLast)
        {
            cout << "L_";
        }
        else
        {
            cout << "|- ";
        }

        if (node == robotNode)
        {
            cout << "[R:" << node->data << "]" << endl;
        }
        else
        {
            cout << node->data << endl;
        }
    }

    string newPrefix;

    if (prefix.empty())
    {
        newPrefix = "    ";
    }
    else if (isLast)
    {
        newPrefix = prefix + "    ";
    }
    else
    {
        newPrefix = prefix + "|   ";
    }

    if (node->left != nullptr)
    {
        printBinaryTree(node->left, robotNode, newPrefix, false);
    }

    if (node->right != nullptr)
    {
        printBinaryTree(node->right, robotNode, newPrefix, true);
    }
}

bool navigateBinaryTree(BinaryTreeNode *current, BinaryTreeNode *root, Stack &pathStack, Stack &logStack, string targetName)
{
    if (current == nullptr)
    {
        return false;
    }

    cout << "\n[FORWARD] Robot at: " << current->data << endl;
    logStack.push(current->data);

    printBinaryTree(root, current, "", true);
    delay();

    if (current->data == targetName)
    {

        cout << "\n=== [ITEM FOUND] ===\n";

        Stack directForwardStack = pathStack;
        Stack directReverseStack = pathStack;

        cout << "Direct Forward Path (Warehouse -> Item): ";
        cout << getForwardPath(directForwardStack) << endl;

        cout << "Direct Reverse Path (Item -> Warehouse): ";
        cout << getReversePath(directReverseStack) << "\n"
             << endl;

        Stack logForwardStack = logStack;
        Stack logReverseStack = logStack;

        cout << "Total Forward Path (Warehouse -> Item): ";
        cout << getForwardPath(logForwardStack) << endl;

        cout << "Total Reverse Path (Item -> Warehouse): ";
        cout << getReversePath(logReverseStack) << endl;

        return true;
    }

    if (current->left)
    {
        pathStack.push("LEFT");

        if (navigateBinaryTree(current->left, root, pathStack, logStack, targetName))
        {
            return true;
        }

        cout << "\n[BACKWARD] Robot at: " << current->data << endl;
        logStack.push(current->data);
        printBinaryTree(root, current, "", true);
        delay();

        pathStack.pop();
    }

    if (current->right)
    {
        pathStack.push("RIGHT");

        if (navigateBinaryTree(current->right, root, pathStack, logStack, targetName))
        {
            return true;
        }

        cout << "\n[BACKWARD] Robot at: " << current->data << endl;
        printBinaryTree(root, current, "", true);
        delay();

        pathStack.pop();
    }

    return false;
}

void runBinaryTree(BinaryTreeNode *root)
{

    if (root == nullptr)
    {
        cout << "[ERROR] Leaf Me Alone...I Tried...You Are Barking Up The Wrong Tree >:D\n";
        return;
    }

    displayBinaryTreeLayout(root);

    string targetName;

    cout << "Enter target item: ";
    getline(cin, targetName);

    if (!nodeExists(root, targetName))
    {
        cout << "[ERROR] '" << targetName << "' does not exist in the tree.\n";
        return;
    }

    Stack directStack;
    Stack logStack;

    cout << "\n============\n";

    navigateBinaryTree(root, root, directStack, logStack, targetName);
}

// yes..i am losing my mind T-T
void printGeneralTree(TreeNode *node, TreeNode *robotNode, string prefix, bool isLast)
{
    if (node == nullptr)
        return;

    if (prefix.empty())
    {
        if (node == robotNode)
            cout << "[R:" << node->name << "]" << endl;
        else
            cout << node->name << endl;
    }
    else
    {
        cout << prefix;

        if (isLast)
            cout << "L_";
        else
            cout << "|- ";

        if (node == robotNode)
            cout << "[R:" << node->name << "]" << endl;
        else
            cout << node->name << endl;
    }

    string newPrefix;

    if (prefix.empty())
        newPrefix = "    ";
    else if (isLast)
        newPrefix = prefix + "    ";
    else
        newPrefix = prefix + "|   ";

    TreeNode *child = node->firstChild;

    while (child != nullptr)
    {
        bool last = (child->nextSibling == nullptr);

        printGeneralTree(child, robotNode, newPrefix, last);

        child = child->nextSibling;
    }
}

bool navigateGeneralTree(TreeNode *current, TreeNode *root, Stack &directStack, Stack &logStack, string targetName)
{
    if (current == nullptr)
    {
        return false;
    }

    cout << "\n[FORWARD] Robot at: " << current->name << endl;

    directStack.push(current->name);
    logStack.push(current->name);

    printGeneralTree(root, current, "", true);
    delay();

    if (current->name == targetName)
    {
        cout << "\n=== [ITEM FOUND] ===\n";

        Stack directForward = directStack;
        Stack directReverse = directStack;

        cout << "\nDirect Forward Path: " << getForwardPath(directForward) << endl;
        cout << "\nDirect Reverse Path: " << getReversePath(directReverse) << endl;

        Stack logForward = logStack;
        Stack logReverse = logStack;

        cout << "\nTotal Forward Path: " << getForwardPath(logForward) << endl;
        cout << "\nTotal Reverse Path: " << getReversePath(logReverse) << endl;

        return true;
    }

    TreeNode *child = current->firstChild;

    while (child != nullptr)
    {

        if (navigateGeneralTree(child, root, directStack, logStack, targetName))
        {
            return true;
        }

        cout << "\n[BACKWARD] Robot at: " << current->name << endl;

        logStack.push(current->name);

        printGeneralTree(root, current, "", true);
        delay();

        child = child->nextSibling;
    }
    directStack.pop();

    return false;
}

void navigateGeneralByPath(WarehouseTree &tree, TreeNode *root, Stack &directStack, Stack &logStack, string targetName)
{
    TreeNode *path[100];

    int count = tree.getPathNodes(targetName, path, 100);

    if (count == 0)
    {
        cout << "Target not found.\n";
        return;
    }

    TreeNode *current = path[0];

    for (int i = 0; i < count; i++)
    {
        TreeNode *next = path[i];

        if (i == 0)
        {
            cout << "\n[START] Robot at: " << next->name << endl;
        }
        else if (i == count - 1)
        {
            cout << "\n[END] Robot moved to: " << next->name << endl;
        }
        else
        {
            cout << "\n[FORWARD] Robot moved to: " << next->name << endl;
        }

        logStack.push(next->name);
        directStack.push(next->name);

        printGeneralTree(root, next, "", true);
        delay();

        current = next;
    }

    cout << "\n=== [ITEM FOUND] ===\n";

    cout << "\nProvided Path: ";

    for (int i = 0; i < count; i++)
    {
        cout << path[i]->name;

        if (i < count - 1)
        {
            cout << " -> ";
        }
    }

    cout << "\n";

    Stack directForward = directStack;
    Stack directReverse = directStack;

    cout << "\nDirect Forward Path: " << getForwardPath(directForward) << endl;
    cout << "\nDirect Reverse Path: " << getReversePath(directReverse) << endl;

    Stack logForward = logStack;
    Stack logReverse = logStack;

    cout << "\nTotal Forward Path: " << getForwardPath(logForward) << endl;
    cout << "\nTotal Reverse Path: " << getReversePath(logReverse) << endl;
}

void runGeneralTree(WarehouseTree &tree)
{

    TreeNode *root = tree.getRoot();

    if (root == nullptr)
    {
        cout << "[ERROR] General tree ... has been uprooted...literally...I am a very funny person...ya I know this message wont be seen but...yes..I saw the pun and went with it...why are you still reading this? >:D\n";
        return;
    }

    tree.displayWarehouseLayout();

    string targetName;

    TreeNode *path[100];
    int count = 0;

    while (true)
    {
        cout << "\nEnter target item (or type EXIT to quit): ";
        getline(cin, targetName);

        if (targetName == "EXIT")
        {
            cout << "Exiting...\n";
            return;
        }

        count = tree.getPathNodes(targetName, path, 100);

        if (count > 0)
        {
            break;
        }
        cout << "[ERROR] '" << targetName << "' does not exist in the tree.\n";
    }

    int choice;

    while (true)
    {
        cout << "\n============\n";

        cout << "\nChoose method:\n";
        cout << "1. DFS Navigation\n";
        cout << "2. Path Navigation (getPathNodes)\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        cout << "\n============\n";

        if (choice == 1)
        {
            Stack directStack;
            Stack logStack;

            navigateGeneralTree(root, root, directStack, logStack, targetName);
        }
        else if (choice == 2)
        {
            Stack directStack;
            Stack logStack;

            navigateGeneralByPath(tree, root, directStack, logStack, targetName);
        }
        else if (choice == 3)
        {
            cout << "Exiting...\n";
            break;
        }
        else
        {
            cout << "[ERROR] Invalid choice. Try again.\n";
        }
    }
}

void robotNavigationMenu()
{
    while (true)
    {
        cout << "\n=== MAIN MENU ===\n";
        cout << "1. Binary Tree Navigation\n";
        cout << "2. General Tree Navigation\n";
        cout << "3. Exit\n";
        cout << "Choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1)
        {
            BinaryTreeNode *root = buildTree();
            runBinaryTree(root);
        }
        else if (choice == 2)
        {
            WarehouseTree warehouse;
            warehouse = warehouse.createDefaultWarehouse();
            runGeneralTree(warehouse);
        }
        else
        {
            break;
        }
    }
}
