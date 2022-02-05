#include<string>
#include<iostream>
#include "Booking.h"
using namespace std;


class BookingList
{
private:
	struct Node
	{
		Booking item;	// data item
		Node* next;	// pointer pointing to next item
	};

	Node* firstNode;	// point to the first item
	int  size;			// number of items in the list

public:

	// constructor
	BookingList();

	void add(Booking newItem);

	void remove(int index);

	Booking get(int index);

	bool isEmpty();

	int getLength();

	int getGuestDate(const char* inputDate);
};
