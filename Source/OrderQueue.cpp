#include "../Header/Robot.hpp"
#include <iostream>
#include <string>

using namespace std;

class OrderQueue
{
private:
	OrderNode *front;
	OrderNode *rear;
	int count; // Number of orders in the queue

public:
	OrderQueue()
	{
		front = nullptr;
		rear = nullptr;
		count = 0;
	}
	~OrderQueue()
	{
		OrderNode *current = front;
		while (current != nullptr)
		{
			OrderNode *temp = current;
			current = current->next;
			delete temp;
		}
	}

	bool isEmpty()
	{
		return front == NULL;
	}

	int getCount()
	{
		return count;
	}

	// Enqueue a new order to the rear of the queue
	void enqueue(OrderNode *newOrder)
	{
		if (newOrder == nullptr)
		{
			cout << "\nInvalid order. Cannot add to the queue." << endl;
			return;
		}
		newOrder->next = nullptr; // Ensure the new queue's next pointer is null

		if (isEmpty())
		{
			front = rear = newOrder; // the first order
		}
		else
		{
			rear->next = newOrder;
			rear = newOrder; // Update rear to the new last node
		}
		count++;
	}

	// Dequeue the order at the front of the queue
	OrderNode *dequeue()
	{

		if (isEmpty())
		{
			cout << "\nNo orders in the queue to process." << endl;
			return nullptr;
		}
		else
		{
			OrderNode *current = front;
			front = front->next;

			if (front == nullptr)
			{
				rear = nullptr; // If the queue becomes empty, update rear to nullptr
			}

			current->next = nullptr; // Detach the dequeued node from the queue
			count--;
			return current;
		}
	}

	// Get the order at the front of the queue without removing it
	OrderNode *getFront()
	{
		if (isEmpty())
		{
			cout << "\nNo orders in the queue." << endl;
			return nullptr;
		}
		else
		{
			return front; // Return the front order without removing it
		}
	}

	// Display all orders in the queue
	void displayQueue()
	{
		if (isEmpty())
		{
			cout << "No orders in the queue." << endl;
		}
		else
		{
			OrderNode *current = front;

			while (current != nullptr)
			{
				cout << "Order ID: " << current->orderId << "; Status: " << current->status << endl;
				current = current->next;
			}
		}
	}
};

class OrderManagement
{
private:
	OrderQueue processingQueue;
	OrderQueue completedQueue;
	int nextOrderId = 1000; // To generate unique order IDs
	int totalOrders = 0;	// To keep track of total orders

public:
	OrderQueue pendingQueue;
	OrderManagement() {};

	// add the new order
	void addPendingOrder(string customerName, string itemList, double orderAmount)
	{

		OrderNode *newOrder = new OrderNode(nextOrderId, customerName, itemList, orderAmount);
		pendingQueue.enqueue(newOrder);

		cout << "\n----------- Successful add new order in the queue -------------\nOrder ID: " << newOrder->orderId << "\nCustomer: " << newOrder->customerName << "\nAmount: " << newOrder->orderAmount << "\nStatus: Pending" << endl;

		nextOrderId++; // Increment the order ID for the next order
		totalOrders++;
	}

	// Process the order
	// Move the order from pending to processing and return the pointer.
	// For Task 2
	OrderNode *assignToRobot()
	{
		if (pendingQueue.isEmpty())
		{
			cout << "\nNo pending orders to process." << endl;
			return nullptr;
		}
		else
		{
			OrderNode *processingOrderNode = pendingQueue.dequeue();
			processingOrderNode->status = "Processing"; // Update the status to Processing

			processingQueue.enqueue(processingOrderNode);

			cout << "\nOrder " << processingOrderNode->orderId << " is now being processed." << "\nOrder Status: " << processingOrderNode->status << endl;
			return processingOrderNode;
		}
	}

	// Get the front processing order queue.
	OrderNode *getCurrentProcessingOrder()
	{
		return processingQueue.getFront();
	}

	// Complete the order
	// Move the order from processing to completed and return the pointer.
	// For Task 3
	bool completeOrder()
	{
		if (processingQueue.isEmpty())
		{
			cout << "\nNo processing orders to complete." << endl;
			return false;
		}
		else
		{
			OrderNode *completedOrderNode = processingQueue.dequeue();

			completedOrderNode->status = "Completed"; // Update the status to Completed

			completedQueue.enqueue(completedOrderNode);

			cout << "\nOrder " << completedOrderNode->orderId << " has been completed." << "\nOrder Status: " << completedOrderNode->status << endl;
			return true;
		}
	}

	// Display all orders in the pending, processing, and completed queues.
	void displayPending()
	{
		cout << "\n------------- Pending Orders -------------" << endl;
		pendingQueue.displayQueue();
		cout << "The count of pending orders: " << pendingQueue.getCount() << endl;
	}
	void displayProcessing()
	{
		cout << "\n------------- Processing Orders ---------------" << endl;
		processingQueue.displayQueue();
		cout << "The count of processing orders: " << processingQueue.getCount() << endl;
	}
	void displayCompleted()
	{
		cout << "\n------------- Completed Orders -------------" << endl;
		completedQueue.displayQueue();
		cout << "The count of completed orders: " << completedQueue.getCount() << endl;
	}
	void displayAllOrders()
	{
		cout << "\n------------ All Orders --------------" << endl;
		displayPending();
		displayProcessing();
		displayCompleted();
	}
	void displaySummary()
	{
		cout << "\n-------------- Order Summary -----------------" << endl;
		cout << "Total Orders: " << totalOrders << endl;
		cout << "Pending Orders: " << pendingQueue.getCount() << endl;
		cout << "Processing Orders: " << processingQueue.getCount() << endl;
		cout << "Completed Orders: " << completedQueue.getCount() << endl;
	}
};
void inputOrders(OrderManagement &orderManagement)
{
	string customerName, itemList;
	double orderAmount;

	cout << "\n--- Enter Order Details ---" << endl;
	cout << "Enter customer name: ";
	cin.ignore(10000, '\n'); // Clear the input buffer before reading a string
	getline(cin, customerName);

	cout << "Enter item list: ";
	getline(cin, itemList);

	cout << "Enter order amount: ";
	cin >> orderAmount;

	if (cin.fail())
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Invalid amount. Please try again." << endl;
		return;
	}
	orderManagement.addPendingOrder(customerName, itemList, orderAmount);
}

void displayMenu(OrderManagement &orderManagement)
{
	int choice;

	while (true)
	{
		cout << "\n----------------- Order Management System -----------------" << endl;
		cout << "1. Add New Order" << endl;
		cout << "2. Assign Order to Robot (Process Order)" << endl;
		cout << "3. Complete Order" << endl;
		cout << "4. Display All Orders" << endl;
		cout << "5. Display Order Summary" << endl;
		cout << "6. Exit" << endl;

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
			inputOrders(orderManagement);
			break;
		case 2:
			orderManagement.assignToRobot();
			break;
		case 3:
			orderManagement.completeOrder();
			break;
		case 4:
			orderManagement.displayAllOrders();
			break;
		case 5:
			orderManagement.displaySummary();
			break;
		case 6:
			cout << "Exiting the program." << endl;
			return;
		default:
			cout << "Invalid choice. Please try again." << endl;
			break;
		}
	}
}
