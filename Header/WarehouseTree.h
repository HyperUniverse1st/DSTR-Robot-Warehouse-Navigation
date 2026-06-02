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
    TreeNode* parent;

    TreeNode(string n, string t);
};

class WarehouseTree {
private:
    TreeNode* root;

    void displayTree(TreeNode* node, int level);
    TreeNode* searchNode(TreeNode* node, string targetName);
    bool buildPath(TreeNode* node, string targetName, string path, string& resultPath);
    bool buildPathNodes(TreeNode* node, string targetName, TreeNode* pathNodes[], int depth, int maxSize, int& resultCount);

public:
    WarehouseTree();

    TreeNode* getRoot();

    void addChild(TreeNode* parent, string childName, string childType);

    TreeNode* findLocation(string locationName);

    bool isValidLocation(string locationName);

    bool isShelfLocation(string locationName);

    string getPath(string locationName);

    int getPathNodes(string locationName, TreeNode* pathNodes[], int maxSize);

    string getPathFromNode(TreeNode* node);

    void displayWarehouseLayout();

    void searchLocation(string locationName);

    void showPath(string locationName);
};

#endif
