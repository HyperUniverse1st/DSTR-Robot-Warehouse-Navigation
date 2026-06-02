#ifndef BINARYTREENAVIGATION_HPP
#define BINARYTREENAVIGATION_HPP

#include <iostream>
#include <string>

using namespace std;

struct BinaryTreeNode
{
    string data;
    BinaryTreeNode* left;
    BinaryTreeNode* right;

    BinaryTreeNode(string val);
};
    void displayBinaryTreeLayout(BinaryTreeNode* root);

    bool nodeExists(BinaryTreeNode* root, string& target);

    BinaryTreeNode* buildTree();

#endif