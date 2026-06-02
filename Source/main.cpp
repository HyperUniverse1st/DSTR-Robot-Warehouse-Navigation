
#include "../Header/WarehouseSystem.hpp"
#include "../Header/Order.hpp"
#include "../Header/RobotList.hpp"
#include "../Header/RobotService.hpp"

void displayMenu(OrderManagement &orderManagement, RobotList &robotList, DoublyLinkedList &itemList);

int main()
{
	OrderManagement orderManagement;
	DoublyLinkedList itemList;
	RobotList *robotList = new RobotList(5);

	// read the inventory from CSV file
	itemList.loadFromCSV("Data/Item_Data.csv");

	// Add sample order data
	orderManagement.addPendingOrder("Lisa", "Football", 150.00);
	orderManagement.addPendingOrder("Amber", "Basketball", 89.90);
	orderManagement.addPendingOrder("Joe", "Clock", 150.00);
	orderManagement.addPendingOrder("Nancy", "Basketball", 89.90);
	orderManagement.addPendingOrder("Peter", "Football", 150.00);
	orderManagement.addPendingOrder("Ali", "Football", 69.00);
	orderManagement.addPendingOrder("Abu", "Basketball", 420.90);

	// Add sample robot data
	// Initialise 10 robots in the RobotList
	for (int i = 0; i < robotList->getCapacity(); i++)
	{
		string ID = "R" + to_string(i + 1);
		robotList->insertAtEnd(ID);
	}

	displayMenu(orderManagement, *robotList, itemList);

	return 0;
}

void displayMenu(OrderManagement &orderManagement, RobotList &robotList, DoublyLinkedList &itemList)
{
	int choice;
	RobotService robotService;

	while (true)
	{
		cout << "\n----------------- Order Management System -----------------" << endl;
		cout << "1. Order Management" << endl;
		cout << "2. Robot Management" << endl;
		cout << "3. Item Management" << endl;
		cout << "4. Simulate assignment" << endl;
		cout << "5. Exit" << endl;
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
			displayOrderMenu(orderManagement, itemList);
			break;
		case 2:
			robotService.robotSubMenu(robotList);
			break;
		case 3:
			menuItemManagement(itemList);
			break;
		case 4:
			robotService.simulateAssignment(orderManagement, &robotList);
			break;
		case 5:
			cout << "Exiting the program." << endl;
			return;
		default:
			cout << "Invalid choice. Please try again." << endl;
			break;
		}
	}
}