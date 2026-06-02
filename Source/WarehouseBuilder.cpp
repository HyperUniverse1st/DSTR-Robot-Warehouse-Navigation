#include "WarehouseBuilder.hpp"

WarehouseTree WarehouseBuilder::createDefaultWarehouse()
{
    WarehouseTree warehouse;

    TreeNode* root = warehouse.getRoot();

    warehouse.addChild(root, "Zone A", "Zone");
    warehouse.addChild(root, "Zone B", "Zone");

    TreeNode* zoneA = root->firstChild;
    TreeNode* zoneB = zoneA->nextSibling;

    warehouse.addChild(zoneA, "Aisle A1", "Aisle");
    warehouse.addChild(zoneA, "Aisle A2", "Aisle");

    warehouse.addChild(zoneB, "Aisle B1", "Aisle");
    warehouse.addChild(zoneB, "Aisle B2", "Aisle");

    return warehouse;
}