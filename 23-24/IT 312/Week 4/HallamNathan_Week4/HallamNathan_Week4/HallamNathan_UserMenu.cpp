/*
Name		: Nathan Hallam
Course		: IT-132
Data		: 31st March, 2024
Project NO	: 4-1
File Name	: HallamNathan_UserMenu.cpp
Description : Find and resolve five errors in the code and document them.
			  Resolutions:
			  1: Missing using namespace std for cout and cin								- line 23
			  2: switch argument should be choice not Choice								- line 50
			  3: second cout of first switch case should be in quotes						- line 58
			  4: second switch case missing its argument (2)								- line 66
			  5: else statement in Tower function is lowercase when it should be uppercase	- line 94
			  Additions:
			  - do-while loop to allow program to run until user closes it
			  - check for proper input to prevent program from looping endlessly
*/


#include <cstdlib>
#include <iostream>

using namespace std;

void Tower(int, char, char, char);

int main()
{
	int choice;

	do {
		//Print menu
		cout << "1. Solve the Tower of Hanoi" << endl;
		cout << "2. View Your Profile" << endl;
		cout << "3. Exit" << endl;

		//Prompt for input
		cout << "Enter your choice : " << endl;
		cin >> choice;

		//If input fails, IE not integer
		if (!cin) {
			cin.clear();													//Clear input
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	//Ignore last input

			cout << "Choice must be an integer 1-3" << endl;				//Prompt for proper input
			continue;
		}

		switch (choice) {
			//Play Tower of Hanoi
		case 1:
			system("cls");
			int numDiscs;

			//Print selection and get disc count
			cout << "**Tower of Hanoi**\n";
			cout << "Enter the number of discs : ";
			cin >> numDiscs;

			cout << "\n\n";
			Tower(numDiscs, 'A', 'B', 'C');
			cout << "\n\n";
			break;
			//Display user stats
		case 2:
			cout << "Username:\t\tPlayer 1" << endl;
			cout << "Gamertag:\t\tImTheBest" << endl;
			cout << "No. Hours Played:\t173" << endl;
			cout << "\n\n";
			break;
			//Exit
		case 3:
			cout << "Now Exiting." << endl;
			break;
			//Invalid command
		default:
			cout << "You did not choose anything..." << endl;
		}
	} while (choice != 3);

	return 0;
}


void Tower(int numDiscs, char from, char aux, char to) {
	//If only one disc
	if (numDiscs == 1) {
		cout << "\tMove disc 1 from " << from << " to " << to << "\n";
		return;
	}
	//If more than one disc
	else {
		Tower(numDiscs - 1, from, to, aux);	//Recursive, find top of stack and move it
		cout << "\tMove disc " << numDiscs << " from " << from << " to " << to << "\n";
		Tower(numDiscs - 1, aux, from, to);
	}
}
