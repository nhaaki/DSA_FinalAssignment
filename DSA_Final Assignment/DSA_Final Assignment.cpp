#include <iostream>
using namespace std;


int main()
{
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
