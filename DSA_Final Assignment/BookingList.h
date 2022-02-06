#pragma once
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

	
	int  size;			// number of items in the list

public:
	Node* firstNode;	// point to the first item

	// constructor
	BookingList();

	void add(Booking newItem);

	void remove(int index);

	Booking get(int index);

	bool isEmpty();

	int getLength();

	int getGuestDate(const char* inputDate);

	string findEmptyRoom(const char* ci, const char* co, string rn);

	// Functions for mergesort

	Node* MergeLists(Node* lst1, Node* lst2);

	void splitList(Node* source, Node** front, Node** back);

	void MergeSort(Node** thead);	
};
