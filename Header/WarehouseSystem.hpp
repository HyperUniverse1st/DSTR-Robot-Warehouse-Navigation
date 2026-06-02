#ifndef WAREHOUSESYSTEM_H
#define WAREHOUSESYSTEM_H

#include <iostream>
#include <string>

using namespace std;

// ITEM
struct Item {
    int itemID;
    string itemName;
    string location;
    int quantity;
};

// NODE
struct Node {
    Item data;
    Node* next;
    Node* prev;
};

// CLASS
class DoublyLinkedList {

private:
    Node* head;
    Node* tail;

public:

    DoublyLinkedList();

    void insertItem(Item item);
    void displayItems();

    bool isEmpty();
    bool itemExists(string itemName);
    void displayItemName();

    void searchByID(int id);
    void searchByName(string name);
    void searchByLocation(string loc);

    void updateItem(int id);
    void deleteItem(int id);


    void autoSaveToCSV();           // Auto save
    void saveToCSV(string filename); // Save to file
    void loadFromCSV(string filename); // Read file
};

// MENU
void menuItemManagement(DoublyLinkedList& itemList);



#endif