// Dictionary.h - - Specification of Dictionary ADT
#include<string>
#include<iostream>
#include<vector>
#include "Booking.h"
#include "BookingList.h"
using namespace std;

const int MAX_SIZE = 25;
typedef string KeyType;

struct Node
{
	KeyType  key;   // search key
	Booking item;	// data item
	Node* next;	// pointer pointing to next item
};

class BookingDictionary
{
private:
	Node* items[MAX_SIZE];
	int  size;			// number of items in the Dictionary

public:
	// constructor
	BookingDictionary();

	// destructor
	~BookingDictionary();

	// add a new item with the specified key to the Dictionary
	bool add(KeyType newKey, Booking newItem);

	bool addToFront(KeyType newKey, Booking newItem);

	// remove an item with the specified key in the Dictionary
	void remove(KeyType key);

	void replace(KeyType key, Booking booking);

	// check if the Dictionary is empty
	bool isEmpty();

	// check the size of the Dictionary
	int getLength();

	//------------------- Other useful functions -----------------
	// display the items in the Dictionary
	void print();

	int hash(KeyType key);

	int displayRoomDates(const char* d);

	Node* printUserBookings(KeyType key, string name, tm* d);

	int getLastDate(int month, int year);

	void returnAllBookings(BookingList &allBookings);
};