#include "RoomList.h"
#include "Room.h"
#include <time.h>
#include <sstream>
#include <iostream>
#include <string>

RoomList::RoomList() { size = 0; }

// add a new item to the back of the list (append)
// pre : size < MAX_SIZE
// post: new item is added to the back of the list
//       size of list is increased by 1
void RoomList::add(Room newItem)
{
	Node* newNode = new Node;
	newNode->item = newItem;
	newNode->next = NULL;

	if (isEmpty())
		firstNode = newNode;
	else {
		Node* temp = firstNode;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newNode;
	}
	size++;
}

// remove an item at a specified position in the list
// pre : 1 <= index <= size
// post: item is removed the specified position in the list
//       items after the position are shifted forward by 1 position
//       size of list is decreased by 1
void RoomList::remove(int index)
{
	bool success = (index >= 0) && (index < size);
	if (success)
	{
		if (index == 0)
		{
			Node* temp = firstNode;
			firstNode = firstNode->next;
			temp->next = NULL;
			delete temp;
		}
		else
		{
			Node* current = firstNode;
			Node* previous = firstNode;
			for (int i = 0; i < index; i++)
			{
				previous = current;
				current = current->next;
			}
			previous->next = current->next;
			current->next = NULL;
			delete current;
		}
		size--;
	}
}

// get an item at a specified position of the list (retrieve)
// pre : 1 <= index <= size
// post: none
// return the item in the specified index of the list
Room RoomList::get(int index)
{
	bool success = (index >= 0) && (index < size);
	if (success)
	{
		if (index == 0)
		{
			return firstNode->item;
		}
		else
		{
			Node* temp = firstNode;
			for (int i = 0; i < index - 1; i++)
			{
				temp = temp->next;
			}
			return temp->item;
		}
	}
}

// check if the list is empty
// pre : none
// post: none
// return true if the list is empty; otherwise returns false
bool RoomList::isEmpty()
{
	return size == 0;
}

// check the size of the list
// pre : none
// post: none
// return the number of items in the list
int RoomList::getLength()
{
	return size;
}