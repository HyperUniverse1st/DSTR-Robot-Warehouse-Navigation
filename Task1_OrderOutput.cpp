#include "Task4_WarehouseSystem.hpp"
#include "Task1_Order.hpp"

void inputOrders(OrderManagement &orderManagement, DoublyLinkedList &itemList)
{
	string customerName, itemName;
	double orderAmount;

	if (itemList.isEmpty())
	{

		cout << "\nNo items in warehouse inventory!" << endl;
		cout << "Please add items using Item Management (Option 6) first." << endl;
		return;
	}

	cout << "\n--- Enter Order Details ---" << endl;
	cout << "Enter customer name: ";
	cin.ignore(10000, '\n'); // Clear the input buffer before reading a string
	getline(cin, customerName);

	// Input correct item
	do
	{

		cout << "Enter item name: ";
		getline(cin, itemName);

		// Check the item id exist
		if (itemList.itemExists(itemName))
		{
			break;
		}
		else
		{
			cout << "--------------------------------------------------------------------------------" << endl;
			cout << "Invalid item name! '" << itemName << "' not found in warehouse." << endl;
			cout << "Please enter a valid item name from the inventory." << endl;

			// Display All items
			cout << "\nAvailable items: ";
			itemList.displayItemName();
		}
	} while (true);

	cout << "Enter order amount: ";
	cin >> orderAmount;

	if (cin.fail())
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Invalid amount. Please try again." << endl;
		return;
	}
	orderManagement.addPendingOrder(customerName, itemName, orderAmount);
}

void displayOrderMenu(OrderManagement &orderManagement, DoublyLinkedList &itemList)
{
	int choice;

	while (true)
	{
		cout << "\n----------------- Order Management System -----------------" << endl;
		cout << "1. Add New Order" << endl;
		cout << "2. Display All Orders" << endl;
		cout << "3. Display Order Summary" << endl;
		cout << "4. Return" << endl;
		cout << "Please select an option: ";
		cin >> choice;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Invalid input. Please enter a number." << endl;
			continue;
		}

		switch (choice)
		{
		case 1:
			inputOrders(orderManagement, itemList);
			break;
		case 2:
			orderManagement.displayAllOrders();
			break;
		case 3:
			orderManagement.displaySummary();
			break;
		case 4:
			cout << "Returning..." << endl;
			return;
		default:
			cout << "Invalid choice. Please try again." << endl;
			break;
		}
	}
}