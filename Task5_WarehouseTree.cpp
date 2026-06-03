#include "Task5_WarehouseTree.hpp"

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

bool WarehouseTree::buildPathNodes(TreeNode *node, string targetName, TreeNode *pathNodes[], int depth, int maxSize, int &resultCount)
{
    if (node == nullptr)
        return false;

    if (depth >= maxSize)
        return false;

    pathNodes[depth] = node;

    if (node->name == targetName)
    {
        resultCount = depth + 1;
        return true;
    }

    if (buildPathNodes(node->firstChild, targetName, pathNodes, depth + 1, maxSize, resultCount))
    {
        return true;
    }

    return buildPathNodes(node->nextSibling, targetName, pathNodes, depth, maxSize, resultCount);
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

int WarehouseTree::getPathNodes(string locationName, TreeNode *pathNodes[], int maxSize)
{
    int resultCount = 0;

    if (pathNodes == nullptr || maxSize <= 0)
    {
        return 0;
    }

    buildPathNodes(root, locationName, pathNodes, 0, maxSize, resultCount);

    return resultCount;
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

WarehouseTree WarehouseTree::createDefaultWarehouse()
{
    WarehouseTree warehouse;

    TreeNode *root = warehouse.getRoot();

    warehouse.addChild(root, "Zone A", "Zone");
    warehouse.addChild(root, "Zone B", "Zone");

    TreeNode *zoneA = warehouse.getRoot()->firstChild;
    TreeNode *zoneB = zoneA->nextSibling;

    warehouse.addChild(zoneA, "Aisle A1", "Aisle");
    warehouse.addChild(zoneA, "Aisle A2", "Aisle");

    warehouse.addChild(zoneB, "Aisle B1", "Aisle");
    warehouse.addChild(zoneB, "Aisle B2", "Aisle");

    TreeNode *aisleA1 = zoneA->firstChild;
    TreeNode *aisleA2 = aisleA1->nextSibling;

    TreeNode *aisleB1 = zoneB->firstChild;
    TreeNode *aisleB2 = aisleB1->nextSibling;

    warehouse.addChild(aisleA1, "Shelf A1-S1", "Shelf");
    warehouse.addChild(aisleA1, "Shelf A1-S2", "Shelf");

    warehouse.addChild(aisleA2, "Shelf A2-S1", "Shelf");
    warehouse.addChild(aisleA2, "Shelf A2-S2", "Shelf");

    warehouse.addChild(aisleB1, "Shelf B1-S1", "Shelf");
    warehouse.addChild(aisleB1, "Shelf B1-S2", "Shelf");

    warehouse.addChild(aisleB2, "Shelf B2-S1", "Shelf");
    warehouse.addChild(aisleB2, "Shelf B2-S2", "Shelf");

    return warehouse;
}
