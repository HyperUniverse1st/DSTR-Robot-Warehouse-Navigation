#include "../Header/Task4_WarehouseSystem.hpp"
#include "../Header/Task1_Order.hpp"
#include <fstream>
#include <sstream>

void DoublyLinkedList::autoSaveToCSV()
{
    saveToCSV("Data/Item_Data.csv");
}

// Save to CSV
void DoublyLinkedList::saveToCSV(string filename)
{
    ofstream file(filename);

    if (!file.is_open())
    {
        cout << "[ERROR] Cannot open file " << filename << " for writing!" << endl;
        return;
    }

    // write the head line
    file << "ItemID,ItemName,Location,Quantity\n";

    // read the item list and write in CSV
    Node *temp = head;
    while (temp != nullptr)
    {
        file << temp->data.itemID << ","
             << temp->data.itemName << ","
             << temp->data.location << ","
             << temp->data.quantity << "\n";
        temp = temp->next;
    }

    file.close();
    cout << "Data saved to " << filename << endl;
}

// Read CSV
void DoublyLinkedList::loadFromCSV(string filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cout << "[INFO] " << filename << " not found the file." << endl;
        return;
    }

    string line;
    bool isFirstLine = true;
    int loadedCount = 0;

    while (getline(file, line))
    {

        // skip head line
        if (isFirstLine)
        {
            isFirstLine = false;
            continue;
        }

        // skip empty line
        if (line.empty())
            continue;

        stringstream ss(line);
        string idStr, name, location, qtyStr;

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, location, ',');
        getline(ss, qtyStr, ',');

        // string --> int
        int id = stoi(idStr);
        int quantity = stoi(qtyStr);

        // Create item
        Item item;
        item.itemID = id;
        item.itemName = name;
        item.location = location;
        item.quantity = quantity;

        insertItem(item);
        loadedCount++;
    }

    file.close();

    if (loadedCount > 0)
    {
        cout << "[Load] Loaded " << loadedCount << " items from " << filename << endl;
    }
}
