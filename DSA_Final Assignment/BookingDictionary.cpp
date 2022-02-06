// Team member names: Lim Jun Keat (s10205540) & Nur Hakimi B Mohd Yasman (s10206177)
// Group: 2 
// Dictionary, with keys in the form of room number and guest name


#include "BookingDictionary.h"
#include "Booking.h"
#include "BookingList.h"
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

// Mainly used for dictionary with guest name as key
int BookingDictionary::hash(KeyType key) {
	
	// DJB Hash Function
	unsigned long hash = 5381;
	unsigned int size = key.length();
	unsigned int i = 0;

	for (i = 0;i < size;i++) {
		hash = ((hash << 5) + hash) + (key[i]); /* hash * 33 + c */
		hash %= MAX_SIZE;
	}
	return hash;
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

// Mainly used to add/arrange bookings with status "Booked".
// Arranges these bookings at the front, sorted by earliest check-in date at the front
bool BookingDictionary::addToFront(KeyType newKey, Booking newItem) {
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
		Node* newNode = new Node;
		newNode->key = newKey;
		newNode->item = newItem;
		if (temp->item.getStatus() != "Booked") {
			newNode->next = temp;

			items[index] = newNode;
		}
		else {
			tm checkInDate;
			string x = temp->item.getCheckIn();
			const char* array1 = x.c_str();
			sscanf_s(array1, "%2d/%2d/%4d",
				&checkInDate.tm_mday, &checkInDate.tm_mon, &checkInDate.tm_year);
			checkInDate.tm_hour = 0;
			checkInDate.tm_min = 0;
			checkInDate.tm_sec = 0;
			time_t first = mktime(&checkInDate);

			tm checkInDate2;
			string y = newNode->item.getCheckIn();
			const char* array2 = y.c_str();
			sscanf_s(array2, "%2d/%2d/%4d",
				&checkInDate2.tm_mday, &checkInDate2.tm_mon, &checkInDate2.tm_year);
			checkInDate2.tm_hour = 0;
			checkInDate2.tm_min = 0;
			checkInDate2.tm_sec = 0;
			time_t second = mktime(&checkInDate2);

			// If new node is later than the top node, shift
			if (difftime(first, second) == 0) {
				newNode->next = temp->next;
				temp->next = newNode;
				items[index] = temp;
			}
			else {
				newNode->next = temp;

				items[index] = newNode;
			}
		}
	}
	size++;
	return true;

}

// Given a name as key, replace existing booking with modified booking. Works in tandem with setRoomForBooking() in the main application.
void BookingDictionary::replace(KeyType key, Booking b) {
	int index = stoi(key) - 100;
	if (items[index] != NULL) {
		Node* temp = items[index];
		Node* next = temp->next;
		while (next != NULL || temp!=NULL) {
			if (items[index] == temp && temp->item.getBookingID() == b.getBookingID()) {
				Node* del = items[index];
				Node* newnode = new Node;
				newnode->key = key;
				newnode->item = b;
				newnode->next = del->next;
				del->next = NULL;
				delete del;
				items[index] = newnode;
			}
			else if (next->item.getBookingID() == b.getBookingID()) {
				Node* del = next;
				Node* newnode = new Node;
				newnode->key = key;
				newnode->item = b;
				newnode->next = del->next;
				temp->next = newnode;
				del->next = NULL;
				delete del;
				break;
			}
			else {
				temp = temp->next;
				next = next->next;
			}
		}
	}
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

// Given the guest name as key, print out all the user bookings on the current day that can be checked in.
Node* BookingDictionary::printUserBookings(KeyType key, string name, tm* d) {

	int index = stoi(key) - 100;
	bool hasBooking = false;
	time_t currentDate = mktime(d);

	if (items[index] == NULL)
	{
		cout << "No bookings made!" << endl;
	}
	else
	{
		int counter = 1;
		//cout << "Collision at " << index << " - " << newKey << " and " << items[index]->key << endl;
		Node* temp = items[index];
		cout << endl << "Bookings ready for check-in:\n";
		while (temp != NULL) {
			string checkinDate = temp->item.getCheckIn();
			tm itemdate;
			const char* array = checkinDate.c_str();
			sscanf_s(array, "%2d/%2d/%4d",
				&itemdate.tm_mday, &itemdate.tm_mon, &itemdate.tm_year);
			itemdate.tm_year -= 1900;
			itemdate.tm_mon -= 1;
			itemdate.tm_hour = 0;
			itemdate.tm_min = 0;
			itemdate.tm_sec = 0;
			time_t testing = mktime(&itemdate);
			double timediff = difftime(currentDate, testing);

			if (temp->item.getGuestName() == name && temp->item.getStatus() == "Booked" && timediff==0.0) {
				hasBooking = true;
				cout << counter << ": Booking ID: " << temp->item.getBookingID() << "   Name: " << temp->item.getGuestName()
					<< "   Check In Date: " << temp->item.getCheckIn() << "   Check In Status: " << temp->item.getStatus() << endl;
				temp = temp->next;
				counter++;
			}
			else if (temp->item.getStatus() != "Booked") {
				temp = NULL;
			}
			else {
				temp = temp->next;
			}
		}
		if (hasBooking) {
			while (true)
			{
				cout << "\nChoose the booking to check into: ";
				int choice;
				
				cin >> choice;
				

				if (cin.fail() || choice<1 || choice >=counter) {
					cout << "Enter a valid number!\n";
				}
				else
				{
					Node* currentItem = items[index];
					int iterator = 1;
					while (currentItem!=NULL)
					{
						if (currentItem->item.getStatus() != "Booked" || currentItem->item.getGuestName() != name) {
							currentItem = currentItem->next;
							continue;
						}
						else if (iterator == choice) {
							currentItem->item.setStatus("Checked In");

							return currentItem;

							cout << "\nSuccessfully checked in!\n";
							break;
						}
						else {
							iterator++;
							currentItem = currentItem->next;
						}
					}
					break;
				}
			}
		}
		else {
			cout << "\nNo upcoming bookings!\n" << endl;
			return NULL;
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

// Using a method similar to deconstructing, populate a bookinglist (unarranged) with all the bookings
void BookingDictionary::returnAllBookings(BookingList &allBookings) {

	for (int i = 0; i < MAX_SIZE; i++) {
		if (items[i] != NULL) {
			Node* temp = items[i];
			while (temp != NULL) {
				allBookings.add(temp->item);
				temp = temp->next;
			}
		}
	}
}

