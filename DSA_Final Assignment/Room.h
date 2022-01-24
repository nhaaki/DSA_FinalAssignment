#pragma once
#include <iostream>
#include <string>
using namespace std;

class Room
{
private:
	string roomNo;
	string roomType;
	int cost;

public:
	Room();
	Room(string, string, int);

	void setRoomNo(string);
	string getRoomNo();

	void setRoomType(string);
	string getRoomType();

	void setCost(int);
	int getCost();

};
