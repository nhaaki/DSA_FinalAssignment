#include "Queue.h"
#include "Booking.h"
// constructor
Queue::Queue() {}
Queue::~Queue() {
	frontNode = NULL;
	backNode = NULL;
}

// enqueue (add) item at back of the queue
bool Queue::enqueue(ItemType item)
{
	Node* newNode = new Node;
	newNode->item = item;
	newNode->next = NULL;
	if (isEmpty()) {
		frontNode = newNode;
	}
	else {
		backNode->next = newNode;
	}
	backNode = newNode;
	return true;
}

// dequeue (remove) item from front of the queue
bool Queue::dequeue() {
	bool success = !isEmpty();
	if (success) {
		if (frontNode == backNode) {
			frontNode = NULL;
			backNode = NULL;
		}
		else {
			Node* temp = frontNode;
			frontNode = temp->next;
			temp->next = NULL;
			delete temp;
		}
	}
	return success;
}

// retrieve (get) and dequeue item from front of the queue
bool Queue::dequeue(ItemType& item) {
	bool success = !isEmpty();
	if (success) {
		if (frontNode == backNode) {
			frontNode = NULL;
			backNode = NULL;
		}
		else {
			Node* temp = frontNode;
			frontNode = temp->next;
			temp->next = NULL;
			item = temp->item;
			delete temp;
		}
	}
	return success;
}

// retrieve (get) item from front of queue
void Queue::getFront(ItemType& item) {
	if (!isEmpty()) {
		item = frontNode->item;
	}
}

// check if the queue is empty
bool Queue::isEmpty() {
	return frontNode == NULL;
}