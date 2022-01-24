#include <iostream>
#include "Room.h"

Room::Room() {}

Room::Room(string rn, string rt, int c) : roomNo(rn), roomType(rt), cost(c) {}

void Room::setRoomNo(string rn)
{
	roomNo = rn;
}

string Room::getRoomNo()
{
	return roomNo;
}

void Room::setRoomType(string rt)
{
	roomType = rt;
}

string Room::getRoomType()
{
	return roomType;
}

void Room::setCost(int c)
{
	cost = c;
}

int Room::getCost()
{
	return cost;
}