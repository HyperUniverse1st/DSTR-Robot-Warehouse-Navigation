#include "../Header/Order.hpp"

// add the new order
void OrderManagement::addPendingOrder(string customerName, string itemName, double orderAmount)
{

	OrderNode *newOrder = new OrderNode(nextOrderId, customerName, itemName, orderAmount);
	pendingQueue.enqueue(newOrder);

	cout << "\n----------- Successful add new order in the queue -------------\nOrder ID: " << newOrder->orderId << "\nCustomer: " << newOrder->customerName << "\nAmount: " << newOrder->orderAmount << "\nStatus: Pending" << endl;

	nextOrderId++; // Increment the order ID for the next order
	totalOrders++;
}

// Process the order
// Move the order from pending to processing and return the pointer.
// For Task 2
OrderNode *OrderManagement::assignToRobot()
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
OrderNode *OrderManagement::getCurrentProcessingOrder()
{
	return processingQueue.getFront();
}

// Complete the order
// Move the order from processing to completed and return the pointer.
// For Task 3
bool OrderManagement::completeOrder()
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
void OrderManagement::displayPending()
{
	cout << "\n------------- Pending Orders -------------" << endl;
	pendingQueue.displayQueue();
	cout << "The count of pending orders: " << pendingQueue.getCount() << endl;
}
void OrderManagement::displayProcessing()
{
	cout << "\n------------- Processing Orders ---------------" << endl;
	processingQueue.displayQueue();
	cout << "The count of processing orders: " << processingQueue.getCount() << endl;
}
void OrderManagement::displayCompleted()
{
	cout << "\n------------- Completed Orders -------------" << endl;
	completedQueue.displayQueue();
	cout << "The count of completed orders: " << completedQueue.getCount() << endl;
}
void OrderManagement::displayAllOrders()
{
	cout << "\n------------ All Orders --------------" << endl;
	displayPending();
	displayProcessing();
	displayCompleted();
}
void OrderManagement::displaySummary()
{
	cout << "\n-------------- Order Summary -----------------" << endl;
	cout << "Total Orders: " << totalOrders << endl;
	cout << "Pending Orders: " << pendingQueue.getCount() << endl;
	cout << "Processing Orders: " << processingQueue.getCount() << endl;
	cout << "Completed Orders: " << completedQueue.getCount() << endl;
}
