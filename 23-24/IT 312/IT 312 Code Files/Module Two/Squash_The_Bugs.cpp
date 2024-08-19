// Squash_The_Bugs.cpp : This code contains five errors before it will work as desired.  Find those errors, 
// document a description of the errors and their fix, and fix them.  Try using the debugger to 
// step through the program to find the bugs.  As you step through, take notice of the information
// you can see.  

// This program gets an input of number of gallons of water used from the user.
// It will then calculate a customer's water bill using the following rules:
// A mandatory environmental fee of $15, plus
// $2.35 per 1000 gallons for the first 6000,
// $3.75 per 1000 gallons for over 6000 to 20000,
// $6.00 per 1000 gallons for over 20000.
// The bill is then displayed to the user.

#include <cstdlib>
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	double gallons, charge = 0, total;
	const int fee = 15;
	int costUpTo6K = 2.35,
		costUpTo20K = 3.75,
		costOver20K = 6.00;

	cout << "Enter the total number of gallons used, divided by 1000: ";
	cin >> gallons;

	if (gallons > 20){
		charge = (gallons - 20) * costOver20K;
		charge = charge + (14 * costUpTo20K)
		charge = charge + (6 * costUpTo6K);
	}
	else if (gallons > 6 && gallons <= 20){
		charge == (gallons - 6) * costUpTo20K;
		charge = charge + (6 * costUpTo6K);
	}
	else {
		charge = gallons * costupto6k;
	}


	total = charge + fee;
	cout << "You have used " << gallons << " thousand gallons of water." << endl;
	cout << "Your total water bill is $" << setprecision(2) << fixed << fee;

	return 0;
}