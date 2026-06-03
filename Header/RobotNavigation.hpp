#ifndef ROBOTNAVIGATION_HPP
#define ROBOTNAVIGATION_HPP

#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "BinaryTreeNavigation.hpp"
#include "Task5_WarehouseTree.hpp"
#include "StackNavigation.hpp"

bool navigateGeneralTree(TreeNode *current, TreeNode *root, Stack &directStack, Stack &logStack, string targetName);
void runBinaryTree(BinaryTreeNode *root);
void runGeneralTree(WarehouseTree &tree);
void robotNavigationMenu();

#endif
