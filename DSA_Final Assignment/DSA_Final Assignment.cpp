#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <time.h>
#include "Booking.h"
#include "Room.h"
#include "Queue.h"
using namespace std;

int main()
{
	void displayMenu();
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

	vector<vector<string>> roomData;
	fstream file2("Rooms.csv", ios::in);
	if (file.is_open())
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
		cout << "No: " << r.getRoomNo() << " Type: " << r.getRoomType() << " Cost: " << r.getCost() << endl;
	}
	

	int option = 1;
    while (option != 0)
	{
		displayMenu();
		cin >> option;

		if (option == 1) // display items
		{
			cout << "Guest Check In" << endl;
		}
		else
		if (option == 2)	// search item
		{
			cout << "Add new booking" << endl; 
		}
		else
		if (option == 3)	// add item
		{
			cout << "Display guests" << endl;
		}
		else
		if (option == 4)	// delete item
		{
			cout << "Display occupied rooms" << endl;
		}
		if (option == 0)
			cout << "Bye! \n";
		else
			cout << "Sorry. You have entered an invalid option. \n";
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
