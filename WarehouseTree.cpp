#define  _CRT_SECURE_NO_WARNINGS
#include "WarehouseTree.h"

TreeNode::TreeNode(string n, string t) {
    name = n;
    type = t;
    firstChild = nullptr;
    nextSibling = nullptr;
}

WarehouseTree::WarehouseTree() {
    root = new TreeNode("Main Warehouse", "Warehouse");
}

TreeNode* WarehouseTree::getRoot() {
    return root;
}

void WarehouseTree::displayTree(TreeNode* node, int level) {
    if (node == nullptr) return;

    for (int i = 0; i < level; i++) {
        cout << "  ";
    }

    cout << "- " << node->type << ": " << node->name << endl;

    displayTree(node->firstChild, level + 1);
    displayTree(node->nextSibling, level);
}

TreeNode* WarehouseTree::searchNode(TreeNode* node, string targetName) {
    if (node == nullptr) return nullptr;

    if (node->name == targetName) {
        return node;
    }

    TreeNode* foundInChild = searchNode(node->firstChild, targetName);

    if (foundInChild != nullptr) {
        return foundInChild;
    }

    return searchNode(node->nextSibling, targetName);
}

bool WarehouseTree::findPath(TreeNode* node, string targetName, string path) {
    if (node == nullptr) return false;

    string currentPath = path + " -> " + node->name;

    if (node->name == targetName) {
        cout << "Navigation Path: " << currentPath << endl;
        return true;
    }

    if (findPath(node->firstChild, targetName, currentPath)) {
        return true;
    }

    return findPath(node->nextSibling, targetName, path);
}

void WarehouseTree::addChild(TreeNode* parent, string childName, string childType) {
    if (parent == nullptr) {
        cout << "Parent location not found." << endl;
        return;
    }

    TreeNode* newNode = new TreeNode(childName, childType);

    if (parent->firstChild == nullptr) {
        parent->firstChild = newNode;
    }
    else {
        TreeNode* temp = parent->firstChild;

        while (temp->nextSibling != nullptr) {
            temp = temp->nextSibling;
        }

        temp->nextSibling = newNode;
    }
}

void WarehouseTree::displayWarehouseLayout() {
    cout << "\n===== Warehouse Layout =====" << endl;
    displayTree(root, 0);
}

void WarehouseTree::searchLocation(string locationName) {
    TreeNode* result = searchNode(root, locationName);

    if (result != nullptr) {
        cout << "Location found: " << result->type
            << " - " << result->name << endl;
    }
    else {
        cout << "Location not found." << endl;
    }
}

void WarehouseTree::showPath(string locationName) {
    cout << "\n===== Path Searching Result =====" << endl;

    bool found = findPath(root, locationName, "");

    if (!found) {
        cout << "No path found to " << locationName << endl;
    }
}