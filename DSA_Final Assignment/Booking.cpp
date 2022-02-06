// Team member names: Lim Jun Keat (s10205540) & Nur Hakimi B Mohd Yasman (s10206177)
// Group: 2 
// Object class for Booking


#include <iostream>
#include "Booking.h"

Booking::Booking() {

}

Booking::Booking(int bID, string bd, string gn, string rn, string rt, string s, string cIn, string cOut, int ng, string sr)
	: bookingID(bID), bookingDate(bd), guestName(gn), roomNo(rn), roomType(rt), status(s), checkIn(cIn), checkOut(cOut), noOfGuests(ng), specialRequests(sr) {}

void Booking::setBookingID(int bId)
{
	bookingID = bId;
}

int Booking::getBookingID()
{
	return bookingID;
}

void Booking::setBookingDate(string bd)
{
	bookingDate = bd;
}

string Booking::getBookingDate()
{
	return bookingDate;
}

void Booking::setGuestName(string gn)
{
	guestName = gn;
}

string Booking::getGuestName()
{
	return guestName;
}

void Booking::setRoomNo(string rn)
{
	roomNo = rn;
}

string Booking::getRoomNo()
{
	return roomNo;
}

void Booking::setRoomType(string rt)
{
	roomType = rt;
}

string Booking::getRoomType()
{
	return roomType;
}

void Booking::setStatus(string s)
{
	status = s;
}

string Booking::getStatus()
{
	return status;
}

void Booking::setCheckIn(string cIn)
{
	checkIn = cIn;
}

string Booking::getCheckIn()
{
	return checkIn;
}

void Booking::setCheckOut(string cOut)
{
	checkOut = cOut;
}

string Booking::getCheckOut()
{
	return checkOut;
}

void Booking::setNoOfGuests(int ng)
{
	noOfGuests = ng;
}

int Booking::getNoOfGuests()
{
	return noOfGuests;
}

void Booking::setSpecialRequest(string sr)
{
	specialRequests = sr;
}

string Booking::getSpecialRequest()
{
	return specialRequests;
}

void Booking::displayDetails()
{
	cout << "Booking ID: " << getBookingID() << " Guest Name: " << getGuestName() << " Room No. " << getRoomNo() << " Check In Date: " << getCheckIn() << " Check Out Date: " << getCheckOut() << endl;
}
