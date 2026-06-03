#include "../Header/WarehouseSystem.hpp"

// ==========================================
// CONSTRUCTOR
// ==========================================
DoublyLinkedList::DoublyLinkedList()
{
    head = nullptr;
    tail = nullptr;
}

// ==========================================
// INSERT ITEM (AUTO ID)
// ==========================================
void DoublyLinkedList::insertItem(Item item)
{

    Node *newNode = new Node;

    // AUTO GENERATE ITEM ID
    if (tail == nullptr)
        item.itemID = 1001;
    else
        item.itemID = tail->data.itemID + 1;

    newNode->data = item;

    newNode->next = nullptr;
    newNode->prev = nullptr;

    if (head == nullptr)
    {
        head = tail = newNode;
    }
    else
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    cout << "Item inserted successfully.\n";

    // Auto save to CSV after inserting an item
    autoSaveToCSV();
}

// ==========================================
// DISPLAY ITEMS
// ==========================================
void DoublyLinkedList::displayItems()
{

    if (head == nullptr)
    {
        cout << "No items available.\n";
        return;
    }

    Node *temp = head;

    cout << "\n===== ITEM LIST =====\n";

    while (temp != nullptr)
    {

        cout << "Item ID   : "
             << temp->data.itemID << endl;

        cout << "Item Name : "
             << temp->data.itemName << endl;

        cout << "Location  : "
             << temp->data.location << endl;

        cout << "Quantity  : "
             << temp->data.quantity << endl;

        cout << "-------------------------\n";

        temp = temp->next;
    }
}

bool DoublyLinkedList::isEmpty()
{
    return head == nullptr;
}

// Display all item name
void DoublyLinkedList::displayItemName()
{
    if (head == nullptr)
    {
        cout << "No items available.\n";
        return;
    }

    Node *temp = head;
    cout << "\n===== Item Name List =====\n";
    while (temp != nullptr)
    {
        cout << temp->data.itemName << "; ";
        temp = temp->next;
    }
    cout << endl;
}

// Check the item if exists
bool DoublyLinkedList::itemExists(string itemName)
{
    Node *temp = head;

    while (temp != nullptr)
    {
        if (temp->data.itemName == itemName)
        {
            return true;
        }
        temp = temp->next;
    }

    return false;
}

// ==========================================
// Get Item Location by Name
// ==========================================
string DoublyLinkedList::getItemLocation(string name)
{
    // Check if item exists
    if (itemExists(name))
    {
        Node *temp = head;

        // Loop through all nodes
        while (temp != nullptr)
        {

            // If the item is found, return its location
            if (temp->data.itemName == name)
            {
                return temp->data.location;
            }
            else
            {
                // Else move to next node
                temp = temp->next;
            }
        }
    }
    else // Print error message if does not exist
    {
        cout << "Item not found.\n";
        return "";
    }
    return "";
}

// ==========================================
// SEARCH BY ID
// ==========================================
void DoublyLinkedList::searchByID(int id)
{

    Node *temp = head;

    while (temp != nullptr)
    {

        if (temp->data.itemID == id)
        {

            cout << "\n===== ITEM FOUND =====\n";

            cout << "Item ID   : "
                 << temp->data.itemID << endl;

            cout << "Item Name : "
                 << temp->data.itemName << endl;

            cout << "Location  : "
                 << temp->data.location << endl;

            cout << "Quantity  : "
                 << temp->data.quantity << endl;

            return;
        }

        temp = temp->next;
    }

    cout << "Item not found.\n";
}

// ==========================================
// SEARCH BY NAME
// ==========================================
void DoublyLinkedList::searchByName(string name)
{

    Node *temp = head;

    bool found = false;

    while (temp != nullptr)
    {

        if (temp->data.itemName == name)
        {

            cout << "\n===== ITEM FOUND =====\n";

            cout << "Item ID   : "
                 << temp->data.itemID << endl;

            cout << "Item Name : "
                 << temp->data.itemName << endl;

            cout << "Location  : "
                 << temp->data.location << endl;

            cout << "Quantity  : "
                 << temp->data.quantity << endl;

            found = true;
        }

        temp = temp->next;
    }

    if (!found)
        cout << "Item not found.\n";
}

// ==========================================
// SEARCH BY LOCATION
// ==========================================
void DoublyLinkedList::searchByLocation(string loc)
{

    Node *temp = head;

    bool found = false;

    while (temp != nullptr)
    {

        if (temp->data.location == loc)
        {

            cout << "\n===== ITEM FOUND =====\n";

            cout << "Item ID   : "
                 << temp->data.itemID << endl;

            cout << "Item Name : "
                 << temp->data.itemName << endl;

            cout << "Location  : "
                 << temp->data.location << endl;

            cout << "Quantity  : "
                 << temp->data.quantity << endl;

            found = true;
        }

        temp = temp->next;
    }

    if (!found)
        cout << "Item not found.\n";
}

// ==========================================
// UPDATE ITEM
// ==========================================
void DoublyLinkedList::updateItem(int id)
{

    Node *temp = head;

    while (temp != nullptr)
    {

        if (temp->data.itemID == id)
        {

            cin.ignore();

            cout << "\nEnter New Item Name : ";
            getline(cin, temp->data.itemName);

            cout << "Enter New Location : ";
            getline(cin, temp->data.location);

            cout << "Enter New Quantity : ";
            cin >> temp->data.quantity;

            cout << "Item updated successfully.\n";

            return;
        }

        temp = temp->next;
    }

    cout << "Item not found.\n";

    // Auto save to CSV after updating an item
    autoSaveToCSV();
}

// ==========================================
// DELETE ITEM
// ==========================================
void DoublyLinkedList::deleteItem(int id)
{

    Node *temp = head;

    while (temp != nullptr &&
           temp->data.itemID != id)
    {

        temp = temp->next;
    }

    if (temp == nullptr)
    {

        cout << "Item not found.\n";
        return;
    }

    if (temp == head)
    {

        head = head->next;

        if (head)
            head->prev = nullptr;
    }

    else if (temp == tail)
    {

        tail = tail->prev;

        if (tail)
            tail->next = nullptr;
    }

    else
    {

        temp->prev->next =
            temp->next;

        temp->next->prev =
            temp->prev;
    }

    delete temp;

    cout << "Item deleted successfully.\n";

    // Auto save to CSV after deleting an item
    autoSaveToCSV();
}

// ==========================================
// MENU
// ==========================================
void menuItemManagement(DoublyLinkedList &itemList)
{

    int choice;
    do
    {

        cout << "\n========== WAREHOUSE SYSTEM ==========\n";

        cout << "1 Insert Item\n";
        cout << "2 Display Items\n";
        cout << "3 Search By ID\n";
        cout << "4 Search By Name\n";
        cout << "5 Search By Location\n";
        cout << "6 Update Item\n";
        cout << "7 Delete Item\n";
        cout << "0 Return\n";

        cout << "\nEnter Choice : ";
        cin >> choice;

        switch (choice)
        {

        case 1:
        {

            Item item;

            cin.ignore();

            cout << "Enter Item Name : ";
            getline(cin,
                    item.itemName);

            cout << "Enter Location : ";
            getline(cin,
                    item.location);

            cout << "Enter Quantity : ";
            cin >> item.quantity;

            itemList.insertItem(item);

            break;
        }

        case 2:
            itemList.displayItems();
            break;

        case 3:
        {

            int id;

            cout << "Enter Item ID : ";
            cin >> id;

            itemList.searchByID(id);

            break;
        }

        case 4:
        {

            string name;

            cin.ignore();

            cout << "Enter Name : ";
            getline(cin, name);

            itemList.searchByName(name);

            break;
        }

        case 5:
        {

            string location;

            cin.ignore();

            cout << "Enter Location : ";
            getline(cin, location);

            itemList.searchByLocation(location);

            break;
        }

        case 6:
        {

            int id;

            cout << "Enter Item ID : ";
            cin >> id;

            itemList.updateItem(id);

            break;
        }

        case 7:
        {

            int id;

            cout << "Enter Item ID : ";
            cin >> id;

            itemList.deleteItem(id);

            break;
        }

        case 0:
            cout << "Returning....\n";
            break;

        default:

            cout << "Invalid choice.\n";
        }

    } while (choice != 0);
}
