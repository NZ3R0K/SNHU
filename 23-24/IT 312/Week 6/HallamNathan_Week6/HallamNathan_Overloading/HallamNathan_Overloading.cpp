/*
Name		: Nathan Hallam
Course		: IT-132
Date		: 14th April, 2024
Project NO	: 6-2
File Name	: HallamNathan_Overloading.cpp
Description : A program about function overloads: containing five errors that must be located, fixed, and documented.
Fixes		:
		   1: add() double has a higher precision than the float variables c, d, and y. Changed float variables to be double to match precision.
		   2: first use case of add() integers has a and c as parameters. C is a float when cout text illudes to the use of two integers a and b. Changed c to b.
		   3: second use case of add() doubles has a and b as parameters when it is expecting two doubles. Changed to c and d.
		   4: int add() is missing its return.
		   5: add() double missing semicolon after return statement.
Additions	:
		   1: Added loop to allow program to run until user quits.
		   2: Added menu to allow user to select from adding integers, doubles, or closing program.
*/


#include <cstdlib>
#include <iostream>
using namespace std;

void PrintCommands();
int add(int, int);
double add(double, double);

int main()
{
	int a, b, x;
	double c, d, y;
	int input;

	while (true) {
		//Loop prompt for input until proper input is got.
		do
		{
			PrintCommands();
			cin >> input;

			//If input is not good, clear cin and screen - redo loop.
			if (!cin) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				system("cls");
				continue;
			}

			//otherwise break loop
			break;
		} while (input == 0);

		switch (input) {
		//Integers
		case 1:
			//Prompt
			cout << "Enter two integers\n";
			cin >> a >> b;
			//Get Sum
			x = add(a, b);
			//Print Sum
			cout << "Sum of integers: " << x << endl;
			continue;
		//Doubles
		case 2:
			//Prompt
			cout << "Enter two doubles\n";
			cin >> c >> d;
			//Get Sum
			y = add(c, d);
			//Print Sum
			cout << "Sum of doubles: " << y << endl;
			continue;
		//Quit
		case 3:
			break;
		default:
			break;
		}

		break;
	}


	return 0;
}

//Prints the list of commands for the program loop.
void PrintCommands() {
	cout << "Commands:" << endl;
	cout << "1: Add integers" << endl;
	cout << "2: Add doubles" << endl;
	cout << "3: Close Program" << endl;
}

//Gets the sum of two integers and returns them.
int add(int a, int b)
{
	int sum;
	sum = a + b;
	return sum;
}

//Gets the sum of two doubles and returns them.
double add(double a, double b)
{
	double sum;
	sum = a + b;
	return sum;
}