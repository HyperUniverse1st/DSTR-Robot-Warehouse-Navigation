
#include "Task4_WarehouseSystem.hpp"
#include "Task1_Order.hpp"
#include "Task2_RobotList.hpp"
#include "Task2_RobotService.hpp"
#include "Task5_WarehouseTree.hpp"
#include "Task3_RobotNavigation.hpp"

void displayMenu(OrderManagement &orderManagement, RobotList &robotList, DoublyLinkedList &itemList, WarehouseTree &warehouse);

int main()
{
	OrderManagement orderManagement;
	DoublyLinkedList itemList;
	RobotList *robotList = new RobotList(5);

	// read the inventory from CSV file
	itemList.loadFromCSV("Item_Data.csv");

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

	// Task 5: Warehouse Layout and Navigation Module
	WarehouseTree warehouse = warehouse.createDefaultWarehouse();
	//==============================  End of Initialisation ==================================

	// Display Menu
	displayMenu(orderManagement, *robotList, itemList, warehouse);

	return 0;
}

void displayMenu(OrderManagement &orderManagement, RobotList &robotList, DoublyLinkedList &itemList, WarehouseTree &warehouse)
{
	int choice;
	RobotService robotService;

	while (true)
	{
		cout << "\n----------------- Order Management System -----------------" << endl;
		cout << "1. Order Management" << endl;
		cout << "2. Robot Management" << endl;
		cout << "3. Robot Navigation" << endl;
		cout << "4. Item Management" << endl;
		cout << "5. Display Warehouse Layout" << endl;
		cout << "6. Start order processing" << endl;
		cout << "7. Exit" << endl;
		cout << "Please select an option: ";
		cin >> choice;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Invalid input. Please enter a number." << endl;
			continue;
		}
		else
		{
			cin.ignore(10000, '\n');
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
			robotNavigationMenu();
			break;
		case 4:
			menuItemManagement(itemList);
			break;
		case 5:
			warehouse.displayWarehouseLayout();
			break;
		case 6:
			robotService.simulateAssignment(orderManagement, &robotList, warehouse, itemList);
			break;
		case 7:
			cout << "Exiting the program." << endl;
			return;
		default:
			cout << "Invalid choice. Please try again." << endl;
			break;
		}
	}
}
