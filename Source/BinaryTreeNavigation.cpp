#include "BinaryTreeNavigation.hpp"

BinaryTreeNode::BinaryTreeNode(string val)
{
    data = val;
    left = NULL;
    right = NULL;
    back = NULL;
}

bool nodeExists(BinaryTreeNode* root, string& target) {
    if (root == nullptr) {
        return false;
    }

    if (root->data == target) {
        return true;
    }

    return nodeExists(root->left, target) || nodeExists(root->right, target);
}

void printBinaryTreeLayout(BinaryTreeNode* node, int level)
{
    if (node == nullptr) {
        return;
    }

    for (int i = 0; i < level; i++) {
        cout << "  ";
    }

    cout << "- " << node->data << endl;

    printBinaryTreeLayout(node->left, level + 1);
    printBinaryTreeLayout(node->right, level + 1);
}

void displayBinaryTreeLayout(BinaryTreeNode* root)
{
    cout << "\n===== Binary Tree Layout =====" << endl;
    printBinaryTreeLayout(root, 0);
}

BinaryTreeNode* buildTree()
{
    BinaryTreeNode* warehouse = new BinaryTreeNode("Warehouse");

    BinaryTreeNode* zoneA = new BinaryTreeNode("Zone A");
    BinaryTreeNode* zoneB = new BinaryTreeNode("Zone B");

    BinaryTreeNode* a1 = new BinaryTreeNode("A1");
    BinaryTreeNode* a2 = new BinaryTreeNode("A2");

    BinaryTreeNode* b1 = new BinaryTreeNode("B1");
    BinaryTreeNode* b2 = new BinaryTreeNode("B2");

    warehouse->left = zoneA;
    warehouse->right = zoneB;

    zoneA->back = warehouse;
    zoneB->back = warehouse;

    zoneA->left = a1;
    zoneA->right = a2;

    a1->back = zoneA;
    a2->back = zoneA;

    zoneB->left = b1;
    zoneB->right = b2;

    b1->back = zoneB;
    b2->back = zoneB;

    return warehouse;
}