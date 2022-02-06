// Team member names: Lim Jun Keat (s10205540) & Nur Hakimi B Mohd Yasman (s10206177)
// Group: 2 
// Class object Room to hold the data for rooms.

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