#include "../Header/WarehouseTree.hpp"

TreeNode::TreeNode(string n, string t)
{
    name = n;
    type = t;
    firstChild = nullptr;
    nextSibling = nullptr;
    parent = nullptr;
}

WarehouseTree::WarehouseTree()
{
    root = new TreeNode("Main Warehouse", "Warehouse");
}

TreeNode *WarehouseTree::getRoot()
{
    return root;
}

void WarehouseTree::displayTree(TreeNode *node, int level)
{
    if (node == nullptr)
        return;

    for (int i = 0; i < level; i++)
    {
        cout << "  ";
    }

    cout << "- " << node->type << ": " << node->name << endl;

    displayTree(node->firstChild, level + 1);
    displayTree(node->nextSibling, level);
}

TreeNode *WarehouseTree::searchNode(TreeNode *node, string targetName)
{
    if (node == nullptr)
        return nullptr;

    if (node->name == targetName)
    {
        return node;
    }

    TreeNode *foundInChild = searchNode(node->firstChild, targetName);

    if (foundInChild != nullptr)
    {
        return foundInChild;
    }

    return searchNode(node->nextSibling, targetName);
}

bool WarehouseTree::buildPath(TreeNode *node, string targetName, string path, string &resultPath)
{
    if (node == nullptr)
        return false;

    string currentPath;

    if (path == "")
    {
        currentPath = node->name;
    }
    else
    {
        currentPath = path + " -> " + node->name;
    }

    if (node->name == targetName)
    {
        resultPath = currentPath;
        return true;
    }

    if (buildPath(node->firstChild, targetName, currentPath, resultPath))
    {
        return true;
    }

    return buildPath(node->nextSibling, targetName, path, resultPath);
}

void WarehouseTree::addChild(TreeNode *parent, string childName, string childType)
{
    if (parent == nullptr)
    {
        cout << "Parent location not found." << endl;
        return;
    }

    TreeNode *newNode = new TreeNode(childName, childType);
    newNode->parent = parent;

    if (parent->firstChild == nullptr)
    {
        parent->firstChild = newNode;
    }
    else
    {
        TreeNode *temp = parent->firstChild;

        while (temp->nextSibling != nullptr)
        {
            temp = temp->nextSibling;
        }

        temp->nextSibling = newNode;
    }
}

TreeNode *WarehouseTree::findLocation(string locationName)
{
    return searchNode(root, locationName);
}

bool WarehouseTree::isValidLocation(string locationName)
{
    return findLocation(locationName) != nullptr;
}

bool WarehouseTree::isShelfLocation(string locationName)
{
    TreeNode *result = findLocation(locationName);
    return result != nullptr && result->type == "Shelf";
}

string WarehouseTree::getPath(string locationName)
{
    string resultPath = "";

    buildPath(root, locationName, "", resultPath);

    return resultPath;
}

string WarehouseTree::getPathFromNode(TreeNode *node)
{
    if (node == nullptr)
    {
        return "";
    }

    if (node->parent == nullptr)
    {
        return node->name;
    }

    return getPathFromNode(node->parent) + " -> " + node->name;
}

void WarehouseTree::displayWarehouseLayout()
{
    cout << "\n===== Warehouse Layout =====" << endl;
    displayTree(root, 0);
}

void WarehouseTree::searchLocation(string locationName)
{
    TreeNode *result = searchNode(root, locationName);

    if (result != nullptr)
    {
        cout << "Location found: " << result->type
             << " - " << result->name << endl;
    }
    else
    {
        cout << "Location not found." << endl;
    }
}

void WarehouseTree::showPath(string locationName)
{
    cout << "\n===== Path Searching Result =====" << endl;

    string path = getPath(locationName);

    if (path == "")
    {
        cout << "No path found to " << locationName << endl;
    }
    else
    {
        cout << "Navigation Path: " << path << endl;
    }
}
