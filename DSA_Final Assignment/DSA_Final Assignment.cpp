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
#include "List.h"
using namespace std;

int main()
{
	void displayMenu();
	void stod(const char* date);
	List bookingCheckIn;
	//List roomList;
	Dictionary bookingRoom;
	Dictionary checkinbookings;

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
	}

	int option;
    while (true)
	{
		displayMenu();
		cin >> option;

		if (option == 1)
		{
			string name;
			string temp;

			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Enter your name: ";
			getline(cin, name);
			temp = name.substr(0, 5);
			int hashed = checkinbookings.hash(temp) + 100;
			checkinbookings.printUserBookings(to_string(hashed), name);
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
			const char* array = date.c_str();
			bookingCheckIn.getGuestDate(array);
		}
		else
		if (option == 4)	
		{
			string date;
			cout << "Enter a date dd/mm/yyyy: ";
			cin >> date;
			const char* array = date.c_str();
			bookingRoom.displayRoomDates(array);
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

void stod(const char* date)
{  
	tm result;
	sscanf_s(date, "%2d/%2d/%4d" ,
		&result.tm_mday, &result.tm_mon, &result.tm_year);
	printf("tm_mday:  %d\n", result.tm_mday);
	printf("tm_mon:  %d\n", result.tm_mon);
	printf("tm_year:  %d\n", result.tm_year);
	result.tm_hour = 0;
	result.tm_min = 0;
	result.tm_sec = 0;
	result.tm_year -= 1900;
	result.tm_mon -= 1;


	tm result1;
	char aString[] = "03/04/2020";
	sscanf_s(aString, "%2d/%2d/%4d",
		&result1.tm_mday, &result1.tm_mon, &result1.tm_year);
	printf("tm_mday:  %d\n", result1.tm_mday);
	printf("tm_mon:  %d\n", result1.tm_mon);
	printf("tm_year:  %d\n", result1.tm_year);
	result1.tm_hour = 0;
	result1.tm_min = 0;
	result1.tm_sec = 0;
	result1.tm_year -= 1900;
	result1.tm_mon -= 1;

	time_t timeBig = mktime(&result);
	time_t timeSmall = mktime(&result1);
	cout << difftime(timeSmall, timeBig) << endl;
}