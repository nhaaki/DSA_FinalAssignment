#pragma once
#include <iostream>
#include <string>
using namespace std;

class Booking
{
private:
	int bookingID;
	string bookingDate;
	string guestName;
	string roomNo;
	string roomType;
	string status;
	string checkIn;
	string checkOut;
	int noOfGuests;
	string specialRequests;

public:
	Booking();
	Booking(int, string, string, string, string, string, string, string, int, string);

	void setBookingID(int);
	int getBookingID();

	void setBookingDate(string);
	string getBookingDate();

	void setGuestName(string);
	string getGuestName();

	void setRoomNo(string);
	string getRoomNo();

	void setRoomType(string);
	string getRoomType();

	void setStatus(string);
	string getStatus();

	void setCheckIn(string);
	string getCheckIn();

	void setCheckOut(string);
	string getCheckOut();

	void setNoOfGuests(int);
	int getNoOfGuests();

	void setSpecialRequest(string);
	string getSpecialRequest();

	void displayDetails();
};
