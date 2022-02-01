#include "Dictionary.h"
#include "Booking.h"
#include <iostream>
#include <string>
#include <time.h>
using namespace std;

// constructor
Dictionary::Dictionary() {
	for (int i = 0; i < MAX_SIZE; i++)
		items[i] = NULL;
	size = 0;
}

// destructor
Dictionary::~Dictionary() {
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

int charvalue(char c)
{
	if (isalpha(c))
	{
		if (isupper(c))
			return (int)c - (int)'A';
		else
			return (int)c - (int)'a' + 26;
	}
	else
		return -1;
}


int Dictionary::hash(KeyType key) {
	int total = charvalue(key[0]);
	for (int i = 1; i < key.length();i++)
	{
		if (charvalue(key[i]) == -1)
		{
			continue;
		}
		total = total * 52 + charvalue(key[i]);
		total %= MAX_SIZE;
	}
	return total;
}

// add a new item with the specified key to the Dictionary
bool Dictionary::add(KeyType newKey, ItemType newItem) {
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
void Dictionary::remove(KeyType newKey) {
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

// get an item with the specified key in the Dictionary (retrieve)
ItemType Dictionary::get(KeyType newKey) {
	string key = newKey;
	int index = stoi(key) - 100;
	if (items[index] != NULL)
	{
		Node* temp = items[index];
		while (temp->key != key)
		{
			temp = temp->next;
		}
		return temp->item;
	}
	else
		return Booking();
}

// check if the Dictionary is empty
bool Dictionary::isEmpty() {
	return size == 0;
}

// check the size of the Dictionary
int Dictionary::getLength() {
	return size;
}

//------------------- Other useful functions -----------------
// display the items in the Dictionary
void Dictionary::print() {
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

void Dictionary::displayRoomDates(const char* userDate)
{
	tm inputDate;
	sscanf_s(userDate, "%2d/%2d/%4d",
		&inputDate.tm_mday, &inputDate.tm_mon, &inputDate.tm_year);
	inputDate.tm_hour = 0;
	inputDate.tm_min = 0;
	inputDate.tm_sec = 0;

	for (int i = 0; i < MAX_SIZE; i++)
	{
		string roomNo = to_string(i + 100);
		cout << "\tRoom " << roomNo << " :\n" << endl;
		if (items[i] != NULL)
		{
			Node* temp = items[i];
			while (temp != NULL)
			{
				if (temp->item.getStatus() == "Checked Out")
				{
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
						//will continue here
					}
				}
			}
		}
	}
}