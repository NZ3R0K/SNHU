// UserMenu_Solution.cpp : This code contains five errors before it will work as desired.  Find those errors, 
// document a description of the errors and their fix, and fix them.  Try using the debugger to 
// step through the program to find the bugs.  As you step through, take notice of the information
// you can see.  

//This program builds a menu based on switchcase statements to determine where a user wants to go in the program.
// Program options are then to solve the Tower of Hanoi problem, view the user profile, or exit the program.


#include <cstdlib>
#include <iostream>

void Tower(int, char, char, char);

int main()
{
	int choice;
	cout << "1. Solve the Tower of Hanoi" << endl;
	cout << "2. View Your Profile" << endl;
	cout << "3. Exit" << endl;
	cout << "Enter your choice : " << endl;
	cin >> choice;
	switch (Choice)
	{
		case 1:
			system("cls");
			int numDiscs;

			cout << "**Tower of Hanoi**\n";
			cout << Enter the number of discs : ;
			cin >> numDiscs;
			cout << "\n\n";
			Tower(numDiscs, 'A', 'B', 'C');
			break;
		case :
			cout << "Username:\t\tPlayer 1" << endl;
			cout << "Gamertag:\t\tImTheBest" << endl;
			cout << "No. Hours Played:\t173" << endl;
			break;
		case 3:
			cout << "Now Exiting." << endl;
			break;
		default:
			cout << "You did not choose anything...so exit this program." << endl;
	}

	return 0;
}


void Tower(int numDiscs, char from, char aux, char to){
	if (numDiscs == 1){
		cout << "\tMove disc 1 from " << from << " to " << to << "\n";
		return;
	}
	else{
		tower(numDiscs - 1, from, to, aux);
		cout << "\tMove disc " << numDiscs << " from " << from << " to " << to << "\n";
		Tower(numDiscs - 1, aux, from, to);
	}
}
 