// DSTR-Robot-Warehouse-Navigation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "WarehouseTree.h"

int main()
{
    std::cout << "Hello World!\n";
    
    
    
    
    //Task 5: Warehouse Layout and Navigation Module
    WarehouseTree warehouse;

    TreeNode* root = warehouse.getRoot();

    warehouse.addChild(root, "Zone A", "Zone");
    warehouse.addChild(root, "Zone B", "Zone");

    TreeNode* zoneA = warehouse.getRoot()->firstChild;
    TreeNode* zoneB = zoneA->nextSibling;

    warehouse.addChild(zoneA, "Aisle A1", "Aisle");
    warehouse.addChild(zoneA, "Aisle A2", "Aisle");

    warehouse.addChild(zoneB, "Aisle B1", "Aisle");
    warehouse.addChild(zoneB, "Aisle B2", "Aisle");

    TreeNode* aisleA1 = zoneA->firstChild;
    TreeNode* aisleA2 = aisleA1->nextSibling;

    TreeNode* aisleB1 = zoneB->firstChild;
    TreeNode* aisleB2 = aisleB1->nextSibling;

    warehouse.addChild(aisleA1, "Shelf A1-S1", "Shelf");
    warehouse.addChild(aisleA1, "Shelf A1-S2", "Shelf");

    warehouse.addChild(aisleA2, "Shelf A2-S1", "Shelf");
    warehouse.addChild(aisleA2, "Shelf A2-S2", "Shelf");

    warehouse.addChild(aisleB1, "Shelf B1-S1", "Shelf");
    warehouse.addChild(aisleB1, "Shelf B1-S2", "Shelf");

    warehouse.addChild(aisleB2, "Shelf B2-S1", "Shelf");
    warehouse.addChild(aisleB2, "Shelf B2-S2", "Shelf");

    warehouse.displayWarehouseLayout();

    cout << endl;

    warehouse.searchLocation("Shelf A1-S2");

    warehouse.showPath("Shelf A1-S2");

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
