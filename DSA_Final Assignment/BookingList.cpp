// Team member names: Lim Jun Keat (s10205540) & Nur Hakimi B Mohd Yasman (s10206177)
// Group: 2 
// Linked list structure used to hold bookings. This class helps to locate when rooms are used, and a merge sort function.


#include "BookingList.h"
#include "Booking.h"
#include "Room.h"
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
	bool success = (index >= 0) && (index <= size);
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

// Given a check-in time, check-out time and room type, find a room that has not been checked-in between this period
string BookingList::findEmptyRoom(const char* ci, const char* co, string rn) {

	string room ="";
	if (!isEmpty()) {
		tm x;
		sscanf_s(ci, "%2d/%2d/%4d",
			&x.tm_mday, &x.tm_mon, &x.tm_year);
		x.tm_hour = 0;
		x.tm_min = 0;
		x.tm_sec = 0;
		x.tm_year -= 1900;
		x.tm_mon -= 1;
		time_t checkin = mktime(&x);

		tm y;
		sscanf_s(co, "%2d/%2d/%4d",
			&y.tm_mday, &y.tm_mon, &y.tm_year);
		y.tm_hour = 0;
		y.tm_min = 0;
		y.tm_sec = 0;
		y.tm_year -= 1900;
		y.tm_mon -= 1;
		time_t checkout= mktime(&y);

		Node* tempNode = firstNode;
		while (tempNode != NULL) {
			if (tempNode->item.getStatus() == "Booked") {
				tempNode = tempNode->next;
				continue;
			}
			else if (tempNode->item.getRoomNo()==rn){

				tm q;
				string xx = tempNode->item.getCheckIn();
				const char* arrayC = xx.c_str();
				sscanf_s(arrayC, "%2d/%2d/%4d",
					&q.tm_mday, &q.tm_mon, &q.tm_year);
				q.tm_hour = 0;
				q.tm_min = 0;
				q.tm_sec = 0;
				q.tm_year -= 1900;
				q.tm_mon -= 1;
				time_t cicompare = mktime(&q);

				tm r;
				string yy = tempNode->item.getCheckOut();
				const char* arrayD = yy.c_str();
				sscanf_s(arrayD, "%2d/%2d/%4d",
					&r.tm_mday, &r.tm_mon, &r.tm_year);
				r.tm_hour = 0;
				r.tm_min = 0;
				r.tm_sec = 0;
				r.tm_year -= 1900;
				r.tm_mon -= 1;
				time_t cocompare = mktime(&r);

				if (difftime(cicompare, checkin) < 0 && difftime(cocompare, checkout) > 0) {
					if (room == tempNode->item.getRoomNo()) {
						room = "";
					}
					tempNode = tempNode->next;
					continue;
				}
				else if (difftime(cocompare, checkin) > 0 && difftime(cocompare, checkout) > 0) {
					if (room == tempNode->item.getRoomNo()) {
						room = "";
					}
					tempNode = tempNode->next;
					continue;
				}
				else if (difftime(cicompare, checkin) > 0 && difftime(cicompare, checkout) < 0) {
					if (room == tempNode->item.getRoomNo()) {
						room = "";
					}
					tempNode = tempNode->next;
					continue;
				}
				else {
					if (room == "") {
						room = tempNode->item.getRoomNo();
					}
					tempNode = tempNode->next;
					continue;
				}
			}
			else {
				tempNode = tempNode->next;
				continue;
			}
		}
		if (room != "") {

			return room;
		}
		else {
			return "NIL";
		}
	}
}

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


// Given two sorted lists, merge them into one list
BookingList::Node* BookingList::MergeLists(Node* lst1, Node* lst2) {
	
	Node* result = NULL;

	if (lst1 == NULL)
		return (lst2);
	else if (lst2 == NULL)
		return (lst1);

	// recursively merging two lists
	if (lst1->item.getBookingID() <= lst2->item.getBookingID()) {
		result = lst1;
		result->next = MergeLists(lst1->next, lst2);
	}
	else {
		result = lst2;
		result->next = MergeLists(lst1, lst2->next);
	}
	return result;
}

// Split a list into two
void BookingList::splitList(Node* source, Node** front, Node** back) {
	Node* ptr1;
	Node* ptr2;
	ptr2 = source;
	ptr1 = source->next;

	// ptr1 is incrmented twice and ptr2 is icremented once.
	while (ptr1 != NULL) {
		ptr1 = ptr1->next;
		if (ptr1 != NULL) {
			ptr2 = ptr2->next;
			ptr1 = ptr1->next;
		}
	}

	// ptr2 is at the midpoint.
	*front = source;
	*back = ptr2->next;
	ptr2->next = NULL;
}

// MergeSort sorting function, used to sort all the bookings in order of BookingID in order to export cleanly
void BookingList::MergeSort(Node** thead)
{
	Node* head = *thead;
	Node* ptr1;
	Node* ptr2;

	// Base Case
	if ((head == NULL) || (head->next == NULL)) {
		return;
	}

	// Splitting list
	splitList(head, &ptr1, &ptr2);

	// Recursively sorting two lists.
	MergeSort(&ptr1);
	MergeSort(&ptr2);

	// Sorted List.
	*thead = MergeLists(ptr1, ptr2);
}

