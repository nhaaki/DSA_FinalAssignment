#include<string>
#include<iostream>
#include "Room.h"
using namespace std;


class RoomList
{
private:
	int  size;			// number of items in the list

public:
	struct Node
	{
		Room item;	// data item
		Node* next;	// pointer pointing to next item
	};
	Node* firstNode;	// point to the first item

	// constructor
	RoomList();

	// add a new item to the back of the list (append)
	// pre : size < MAX_SIZE
	// post: new item is added to the back of the list
	//       size of list is increased by 1
	void add(Room newItem);

	// add a new item at a specified position in the list (insert)
	// pre : 1 <= index <= size+1
	// post: new item is added to the specified position in the list
	//       items after the position are shifted back by 1 position
	//       size of list is increased by 1
	bool add(int index, Room newItem);

	// remove an item at a specified position in the list
	// pre : 1 <= index <= size
	// post: item is removed the specified position in the list
	//       items after the position are shifted forward by 1 position
	//       size of list is decreased by 1
	void remove(int index);

	// get an item at a specified position of the list (retrieve)
	// pre : 1 <= index <= size
	// post: none
	// return the item in the specified index of the list
	Room get(int index);

	// check if the list is empty
	// pre : none
	// post: none
	// return true if the list is empty; otherwise returns false
	bool isEmpty();

	// check the size of the list
	// pre : none
	// post: none
	// return the number of items in the list
	int getLength();
};
