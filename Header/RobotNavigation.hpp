#ifndef ROBOTNAVIGATION_HPP
#define ROBOTNAVIGATION_HPP

#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "BinaryTreeNavigation.hpp"
#include "WarehouseTree.hpp"
#include "StackNavigation.hpp"

void runBinaryTree(BinaryTreeNode *root);
void runGeneralTree(WarehouseTree &tree);
void robotNavigationMenu();

#endif
