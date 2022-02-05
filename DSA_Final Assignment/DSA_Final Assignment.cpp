#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <time.h>
#include "Booking.h"
#include "Room.h"
#include "Queue.h"
#include "Dictionary.h"
#include "RoomList.h"
#include "BookingList.h"
using namespace std;

int main()
{
	void displayMenu();
	void stod(const char* date);
	BookingList bookingCheckIn;
	RoomList roomList;
	Dictionary bookingRoom;

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
		displayMenu();
		cin >> option;

		if (option == 1)
		{
			cout << "Guest Check In" << endl;
		}
		else
		if (option == 2)	
		{
			cout << "Add new booking" << endl; 
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
	cout << "0 Exit							 \n";
	cout << "--------------------------------\n";
	cout << "Enter option : ";
}