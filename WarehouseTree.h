#pragma once
#ifndef WAREHOUSETREE_H
#define WAREHOUSETREE_H

#include <iostream>
#include <string>
using namespace std;

class TreeNode {
public:
    string name;
    string type;
    TreeNode* firstChild;
    TreeNode* nextSibling;

    TreeNode(string n, string t);
};

class WarehouseTree {
private:
    TreeNode* root;

    void displayTree(TreeNode* node, int level);
    TreeNode* searchNode(TreeNode* node, string targetName);
    bool findPath(TreeNode* node, string targetName, string path);

public:
    WarehouseTree();

    TreeNode* getRoot();

    void addChild(TreeNode* parent, string childName, string childType);

    void displayWarehouseLayout();

    void searchLocation(string locationName);

    void showPath(string locationName);
};

#endif