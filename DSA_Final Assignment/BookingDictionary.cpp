#include "BookingDictionary.h"
#include "Booking.h"
#include <iostream>
#include <string>
#include <time.h>
#include <vector>
using namespace std;

// constructor
BookingDictionary::BookingDictionary() {
	for (int i = 0; i < MAX_SIZE; i++)
		items[i] = NULL;
	size = 0;
}

// destructor
BookingDictionary::~BookingDictionary() {
	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (items[i] != NULL)
		{
			Node* current = items[i];
			Node* previous = current;
			while (current != NULL)
			{
				previous = current;
				current = current->next;
				previous->next = NULL;
				delete previous;
			}
		}
	}
}


// add a new item with the specified key to the Dictionary
bool BookingDictionary::add(KeyType newKey, Booking newItem) {
	string key = newKey;
	int index = stoi(key) - 100;
	if (items[index] == NULL)
	{
		items[index] = new Node;
		items[index]->key = newKey;
		items[index]->item = newItem;
		items[index]->next = NULL;
	}
	else
	{
		//cout << "Collision at " << index << " - " << newKey << " and " << items[index]->key << endl;
		Node* temp = items[index];
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		Node* newNode = new Node;
		newNode->key = newKey;
		newNode->item = newItem;
		newNode->next = NULL;
		temp->next = newNode;
	}
	size++;
	return true;

}

// remove an item with the specified key in the Dictionary
void BookingDictionary::remove(KeyType newKey) {
	string key = newKey;
	int index = stoi(key) - 100;
	if (items[index] != NULL)
	{
		if (items[index]->key == key)
		{
			Node* temp = items[index];
			items[index] = items[index]->next;
			temp->next = NULL;
			delete temp;
			size--;
		}
		else
		{
			Node* current = items[index];
			Node* previous = items[index];
			while ((current->key != key) && (current->next != NULL))
			{
				previous = current;
				current = current->next;
			}
			previous->next = current->next;
			current->next = NULL;
			delete current;
			size--;
		}

	}
	else
		cout << "No record found" << endl;
}

// check if the Dictionary is empty
bool BookingDictionary::isEmpty() {
	return size == 0;
}

// check the size of the Dictionary
int BookingDictionary::getLength() {
	return size;
}

//------------------- Other useful functions -----------------
// display the items in the Dictionary
void BookingDictionary::print() {
	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (items[i] != NULL)
		{
			Node* temp = items[i];
			while (temp != NULL)
			{
				cout << "Booking ID: " << temp->item.getBookingID() << "   Name: " << temp->item.getGuestName() 
					<< "   Check In Date: " << temp->item.getCheckIn() << "   Check In Status: " << temp->item.getStatus() << endl;
				temp = temp->next;
			}
		}
	}
}

int BookingDictionary::displayRoomDates(const char* userDate)
{
	vector<int> dates;
	tm inputDate;
	sscanf_s(userDate, "%2d/%4d",
		&inputDate.tm_mon, &inputDate.tm_year);
	int count = 0;
	int test = inputDate.tm_year;
	while (test != 0)
	{
		test = test / 10;
		++count;
	}
	if (inputDate.tm_mon < 0 || inputDate.tm_year < 0 || count < 4)
		return -1;
	else
	{
		inputDate.tm_hour = 0;
		inputDate.tm_min = 0;
		inputDate.tm_sec = 0;
		inputDate.tm_mday = 1;

		for (int i = 1; i < MAX_SIZE; i++)
		{
			string roomNo = to_string(i + 100);
			cout << "\nRoom " << roomNo << " :" << endl;
			if (items[i] != NULL)
			{
				Node* temp = items[i];
				while (temp != NULL)
				{
					if (temp->item.getStatus() == "Checked Out")
					{
						//temp->item.displayDetails();
						tm checkInDate;
						string x = temp->item.getCheckIn();
						const char* array1 = x.c_str();
						sscanf_s(array1, "%2d/%2d/%4d",
							&checkInDate.tm_mday, &checkInDate.tm_mon, &checkInDate.tm_year);
						checkInDate.tm_hour = 0;
						checkInDate.tm_min = 0;
						checkInDate.tm_sec = 0;

						tm checkOutDate;
						x = temp->item.getCheckOut();
						const char* array2 = x.c_str();
						sscanf_s(array2, "%2d/%2d/%4d",
							&checkOutDate.tm_mday, &checkOutDate.tm_mon, &checkOutDate.tm_year);
						checkOutDate.tm_hour = 0;
						checkOutDate.tm_min = 0;
						checkOutDate.tm_sec = 0;

						if (checkInDate.tm_year == inputDate.tm_year || checkOutDate.tm_year == inputDate.tm_year)
						{
							if (checkInDate.tm_mon == inputDate.tm_mon && checkOutDate.tm_mon == inputDate.tm_mon)
							{
								for (int start = checkInDate.tm_mday; start < checkOutDate.tm_mday; start++)
								{
									dates.push_back(start);
								}
							}
							else if (checkInDate.tm_mon == inputDate.tm_mon && checkOutDate.tm_mon != inputDate.tm_mon)
							{
								int end = getLastDate(checkInDate.tm_mon, checkInDate.tm_year);
								for (int start = checkInDate.tm_mday; start <= end; start++)
								{
									dates.push_back(start);
								}
							}
							else if (checkInDate.tm_mon != inputDate.tm_mon && checkOutDate.tm_mon == inputDate.tm_mon)
							{
								for (int start = 1; start < checkOutDate.tm_mday; start++)
								{
									dates.push_back(start);
								}
							}
						}
					}
					temp = temp->next;
				}
			}
			int arrSize = dates.size();
			for (int last = arrSize - 1;last >= 1; last--)
			{
				int largestIndex = 0;
				for (int i = 1; i < last + 1; i++)
				{
					if (dates[i] > dates[largestIndex])
						largestIndex = i;
				}
				int temp = dates[largestIndex];
				dates[largestIndex] = dates[last];
				dates[last] = temp;
			}
			if (dates.size() != 0)
			{
				for (int date : dates)
					cout << date << "/" << inputDate.tm_mon << "/" << inputDate.tm_year << "   ";
				dates.clear();
				cout << "\n";
			}
			else
				cout << "Room is not occupied this month" << endl;
		}
		return 1;
	}
	
}

int BookingDictionary::getLastDate(int month, int year)
{
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
		return 31;
	else if (month == 4 || month == 6 || month == 9 || month == 11)
		return 30;
	else {
		if (year % 4 == 0) {
			if (year % 100 == 0) {
				if (year % 400 == 0)
					return 29;
				return 28;
			}
			return 29;
		}
		return 28;
	}
}

