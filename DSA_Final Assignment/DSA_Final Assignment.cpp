#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <time.h>
#include "Booking.h"
#include "Room.h"
#include "Queue.h"
#include "BookingDictionary.h"
#include "RoomList.h"
#include "BookingList.h"
#include <format>
using namespace std;

int main()
{
	void displayMenu();
	Booking setRoomForBooking(Booking b, RoomList &rl, BookingList bl);
	void stod(const char* date);
	BookingList bookingCheckIn;
	RoomList roomList;
	BookingDictionary bookingRoom;
	BookingDictionary checkinbookings;
	time_t todaysDate;

	tm currentDate;
	currentDate.tm_year = 2021;
	currentDate.tm_mon = 04;
	currentDate.tm_mday = 01;
	currentDate.tm_hour = 0;
	currentDate.tm_min = 0;
	currentDate.tm_sec = 0;



	vector<vector<string>> bookingData;
	vector<string> row;
	string line, word;
	fstream file("Bookings.csv", ios::in);
	if (file.is_open())
	{
		getline(file, line);
		while (getline(file, line))
		{
			row.clear();
			stringstream str(line);

			while (getline(str, word, ','))
				row.push_back(word);
			bookingData.push_back(row);
		}
	}
	else
		cout << "Could not open the file\n";

	for (int i = 0;i < bookingData.size();i++)
	{
		Booking b(stoi(bookingData[i][0]), bookingData[i][1], bookingData[i][2], bookingData[i][3], bookingData[i][4], bookingData[i][5],
			bookingData[i][6], bookingData[i][7], stoi(bookingData[i][8]), "");
		bookingCheckIn.add(b);
		string roomNo = bookingData[i][3];

		string name = bookingData[i][2].substr(0,5);
		int hashNum = checkinbookings.hash(name) + 100;

		if (b.getStatus() == "Booked") {
			checkinbookings.addToFront(to_string(hashNum), b);
		}
		else {
			checkinbookings.add(to_string(hashNum), b);
		}

		roomNo.erase(std::remove(roomNo.begin(), roomNo.end(), ' '), roomNo.end());
		if (roomNo.length() != 0)
		{
			roomNo.erase(0, 4);
			bookingRoom.add(roomNo, b);
		}

	}

	vector<vector<string>> roomData;
	fstream file2("Rooms.csv", ios::in);
	if (file2.is_open())
	{
		getline(file2, line);
		while (getline(file2, line))
		{
			row.clear();
			stringstream str(line);

			while (getline(str, word, ','))
				row.push_back(word);
			roomData.push_back(row);
		}
	}
	else
		cout << "Could not open the file\n";

	for (int i = 0;i < roomData.size();i++)
	{
		Room r(roomData[i][0], roomData[i][1], stoi(roomData[i][2]));
		roomList.add(r);
	}

	int option;
    while (true)
	{

		// Export latest data into csv

		BookingList allBookings;
		checkinbookings.returnAllBookings(allBookings);
		allBookings.MergeSort(&(allBookings.firstNode));
		ofstream file;
		file.open("updatedBookings.csv", fstream::trunc);
		file << "Booking ID,Booking Date,Guest Name,Room #,Room Type,Status,Check In,Check Out,Guests #,Special Requests\n";
		int length = allBookings.getLength();
		for (int x = 1; x <= length; x++) {
			Booking current = allBookings.get(x);
			file << current.getBookingID() << "," << current.getBookingDate() << "," << current.getGuestName() << "," << current.getRoomNo() << "," <<
				current.getRoomType() << "," << current.getStatus() << "," << current.getCheckIn() << "," << current.getCheckOut() << "," << current.getNoOfGuests()
				<< "," << current.getSpecialRequest() << "\n";
		}
		file.close();

		// End of exporting booking data

		cout << "Today's date: " << currentDate.tm_mday << "/" << currentDate.tm_mon << "/" << currentDate.tm_year << endl;
		displayMenu();
		cin >> option;

		if (option == 1)
		{
			string name;
			string temp;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nEnter your name: ";
			getline(cin, name);
			temp = name.substr(0, 5);
		
			tm tempDate = currentDate;
			tempDate.tm_year -= 1900;
			tempDate.tm_mon -= 1;
			int hashed = checkinbookings.hash(temp) + 100;
			Node* booking = checkinbookings.printUserBookings(to_string(hashed), name, &tempDate);
			if (booking != NULL) {
				Booking newB = setRoomForBooking(booking->item, roomList, allBookings);
				if (newB.getBookingID() != NULL) {
					checkinbookings.replace(to_string(hashed), newB);
					cout << "Replaced!\n";
				}
			}
			
		}
		else
		if (option == 2)	
		{
			string name;
			string temp;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nEnter your name: ";
			getline(cin, name);
			temp = name.substr(0, 5);

			string roomtypes[] = {"Deluxe City View", "Standard City View", "Executive Sea View", "President Suite"};
			for (int x = 0; x < 4; x++) {
				cout << x+1 << ": " << roomtypes[x] << endl;
			}
			int choice;
			cout << "\nChoose room type: ";
			cin >> choice;
			string chosenrt = roomtypes[choice - 1];
			int numofguests;
			cout << "\nNumber of guests: ";
			cin >> numofguests;
			string date1;
			cout << "\nEnter check-in dd/mm/yyyy: ";
			cin >> date1;
			if (date1.length() < 8) {
				cout << "Please enter the proper format!\n";
				continue;
			}
			string date2;
			cout << "\nEnter check-out dd/mm/yyyy: ";
			cin >> date2;
			if (date2.length() < 8) {
				cout << "Please enter the proper format!\n";
				continue;
			}
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			string req;
			cout << "Enter any requests: ";
			cin >> req;
			char buffer[40];
			strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M", &currentDate);
			string datestr(buffer);
			
			Booking newb(length+1,datestr, name, "",chosenrt, "Booked", date1, date2, numofguests, req);
			string newname = newb.getGuestName().substr(0,5);
			int hashNumnew = checkinbookings.hash(newname) + 100;
			checkinbookings.addToFront(to_string(hashNumnew), newb);
			
		}
		else
		if (option == 3)	
		{
			string date;
			cout << "Enter a date dd/mm/yyyy: ";
			cin >> date;
			cout << "\n";
			const char* array = date.c_str();
			if (bookingCheckIn.getGuestDate(array) == -1)
				cout << "Please enter a valid date in the stated format" << endl;;
		}
		else
		if (option == 4)	
		{
			string date;
			cout << "Enter month and year mm/yyyy: ";
			cin >> date;
			cout << "\n";
			const char* array = date.c_str();
			if (bookingRoom.displayRoomDates(array) == -1)
				cout << "Please enter a valid date in the stated format" << endl;;
		}
		else if (option == 5) {
			string date;
			cout << "\nEnter new date dd/mm/yyyy: ";
			cin >> date;
			const char* array = date.c_str();
			sscanf_s(array, "%2d/%2d/%4d",
				&currentDate.tm_mday, &currentDate.tm_mon, &currentDate.tm_year);
			cout << "Date successfully changed! \n\n";
		}
		else
		if (option == 0)
		{
			cout << "Bye! \n";
			break;
		}
		else
		{
			cout << "Sorry. You have entered an invalid option. \n";
		}
	}

}

void displayMenu()
{
	cout << endl;
	cout << "Hotel App \n";
	cout << "--------------------------------\n";
	cout << "1 Guest Check In\n";
	cout << "2 Add New Booking            \n";
	cout << "3 Display Guests               \n";
	cout << "4 Display Occupied Rooms               \n";
	cout << "5 Change current date               \n";
	cout << "0 Exit							 \n";
	cout << "--------------------------------\n";
	cout << "Enter option : ";
}

Booking setRoomForBooking(Booking b, RoomList &rl, BookingList bl) {
	RoomList::Node* start = rl.firstNode->next;
	RoomList::Node* prev = rl.firstNode;

	// Keep rooms with same booking room type
	while (start != NULL) {
		if (rl.firstNode == prev && prev->item.getRoomType() != b.getRoomType()) {
			RoomList::Node* temp = prev;
			rl.firstNode = start;
			prev = start;
			start = start->next;
			temp->next = NULL;
			delete temp;
		}
		else if (start->item.getRoomType() != b.getRoomType()) {
			prev->next = start->next;
			RoomList::Node* temp = start;
			temp->next = NULL;
			delete temp;
			start = prev->next;
		}
		else {
			prev = prev->next;
			start = start->next;
		}
	}

	RoomList::Node* iterator = rl.firstNode;
	string test;
	while (iterator != NULL) {

		Room room = iterator->item;
		string ci = b.getCheckIn();
		string co = b.getCheckOut();
		const char* arrayA = ci.c_str();
		const char* arrayB = co.c_str();

		test = bl.findEmptyRoom(arrayA, arrayB, room.getRoomNo());
		if (test != "NIL") {
			cout << "Room assigned: " << test << endl;
			break;
		}
		else {
			iterator = iterator->next;
		}
	}
	if (test != "") {
		b.setRoomNo(test);
		return b;
		cout << "\nRoom successfully assigned!\n";
	}
	else {
		Booking c;
		return c;
		cout << "Error... No rooms available...\n";
	}
}