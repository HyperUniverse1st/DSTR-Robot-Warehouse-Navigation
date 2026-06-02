#include "../Header/Order.hpp"

OrderQueue::OrderQueue()
{
	front = nullptr;
	rear = nullptr;
	count = 0;
}
OrderQueue::~OrderQueue()
{
	OrderNode *current = front;
	while (current != nullptr)
	{
		OrderNode *temp = current;
		current = current->next;
		delete temp;
	}
}

bool OrderQueue::isEmpty()
{
	return front == NULL;
}

int OrderQueue::getCount()
{
	return count;
}

// Enqueue a new order to the rear of the queue
void OrderQueue::enqueue(OrderNode *newOrder)
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
OrderNode *OrderQueue::dequeue()
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
OrderNode *OrderQueue::getFront()
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
void OrderQueue::displayQueue()
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