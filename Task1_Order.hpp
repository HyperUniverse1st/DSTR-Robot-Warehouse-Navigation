
#ifndef ORDER_H
#define ORDER_H

#include "Task4_WarehouseSystem.hpp"

#include <iostream>
#include <string>
using namespace std;

// Order Node Structure
struct OrderNode
{
	string orderId;
	string customerName;
	string itemName;
	string status; //""Pending"", ""Processing"", ""Completed""
	double orderAmount;
	OrderNode *next;

	OrderNode(int id, string name, string item, double amount)
	{
		orderId = "OD" + to_string(id);
		customerName = name;
		itemName = item;
		status = "Pending";
		orderAmount = amount;
		next = nullptr;
	}
};

class OrderQueue
{
private:
	OrderNode *front;
	OrderNode *rear;
	int count; // Number of orders in the queue

public:
	OrderQueue();
	~OrderQueue();
	bool isEmpty();
	int getCount();
	void enqueue(OrderNode *newOrder);
	OrderNode *dequeue();
	OrderNode *getFront();

	void displayQueue();
};

class OrderManagement
{
private:
	OrderQueue processingQueue;
	OrderQueue completedQueue;
	int nextOrderId = 100001; // To generate unique order IDs
	int totalOrders = 0;	  // To keep track of total orders

public:
	OrderQueue pendingQueue;
	OrderManagement() {}
	void addPendingOrder(string customerName, string itemList, double orderAmount);
	OrderNode *assignToRobot();
	OrderNode *getCurrentProcessingOrder();
	bool completeOrder();
	void displayPending();
	void displayProcessing();
	void displayCompleted();
	void displayAllOrders();
	void displaySummary();

	// read sample data from CSV file
	void loadOrdersFromCSV(string filename);

	// get next order ID (for testing purpose)
	void updateNextOrderIdFromQueue();
};

void inputOrders(OrderManagement &orderManagement, DoublyLinkedList &itemList);
void displayOrderMenu(OrderManagement &orderManagement, DoublyLinkedList &itemList);

#endif