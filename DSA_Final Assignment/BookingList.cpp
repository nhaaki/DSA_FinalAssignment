#include "BookingList.h"
#include "Booking.h"
#include <time.h>
#include <sstream>
#include <iostream>
#include <string>

BookingList::BookingList() { size = 0; }

// add a new item to the back of the list (append)
// pre : size < MAX_SIZE
// post: new item is added to the back of the list
//       size of list is increased by 1
void BookingList::add(Booking newItem)
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
void BookingList::remove(int index)
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
Booking BookingList::get(int index)
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
bool BookingList::isEmpty()
{
	return size == 0;
}

// check the size of the list
// pre : none
// post: none
// return the number of items in the list
int BookingList::getLength()
{
	return size;
}

//------------------- Other useful functions -----------------

// display the items in the list
/*void List::print()
{
	Node* temp = firstNode;
	if (!isEmpty())
	{
		while (temp != NULL)
		{
			cout << temp->item << endl;
			temp = temp->next;
		}
		cout << "\n";
	}
	else
		cout << "The list is empty." << endl;
}*/

int BookingList::getGuestDate(const char* userDate)
{
	if (!isEmpty())
	{
		tm result;
		sscanf_s(userDate, "%2d/%2d/%4d",
			&result.tm_mday, &result.tm_mon, &result.tm_year);
		int count = 0;
		int test = result.tm_year;
		while (test != 0)
		{
			test = test / 10;
			++count;
		}
		if (result.tm_mday < 0 || result.tm_mon < 0 || result.tm_year < 0 ||count < 4)
			return -1;
		else
		{
			result.tm_hour = 0;
			result.tm_min = 0;
			result.tm_sec = 0;
			result.tm_year -= 1900;
			result.tm_mon -= 1;
			time_t inputDate = mktime(&result);

			int count1 = 0;
			Node* temp = firstNode;
			while (temp != NULL)
			{
				if (temp->item.getStatus() == "Checked Out")
				{
					string x = temp->item.getCheckIn();
					const char* array1 = x.c_str();
					sscanf_s(array1, "%2d/%2d/%4d",
						&result.tm_mday, &result.tm_mon, &result.tm_year);
					result.tm_hour = 0;
					result.tm_min = 0;
					result.tm_sec = 0;
					result.tm_year -= 1900;
					result.tm_mon -= 1;
					time_t checkInDate = mktime(&result);

					x = temp->item.getCheckOut();
					const char* array2 = x.c_str();
					sscanf_s(array2, "%2d/%2d/%4d",
						&result.tm_mday, &result.tm_mon, &result.tm_year);
					result.tm_hour = 0;
					result.tm_min = 0;
					result.tm_sec = 0;
					result.tm_year -= 1900;
					result.tm_mon -= 1;
					time_t checkOutDate = mktime(&result);

					if (difftime(inputDate, checkInDate) >= 0 && difftime(checkOutDate, inputDate) >= 0)
					{
						count1++;
						temp->item.displayDetails();
					}
				}
				temp = temp->next;
			}
			if (count1 == 0)
				cout << "No guests on this date" << endl;
			return 1;
		}
	}
}