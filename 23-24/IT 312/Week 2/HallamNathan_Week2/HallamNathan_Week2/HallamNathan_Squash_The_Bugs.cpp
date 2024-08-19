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

/*
Name		: Nathan Hallam
Course		: IT-132
Data		: 17th March, 2024
Project NO	: 2-2
File Name	: HallamNathan_Squash_The_Bugs.cpp
Description : Code contains 5 errors to be fixed and documented
			1: line 37 is storing values as doubles but is initialized as an int. Found by looking for math errors when stepping through the code.
			2: line 46 was missing a semicolon. Flagged by IDE
			3: line 50 has two equals signs when it should be one. Found by reading through the code to learn how it works and what each line is doing / was not getting desired output.
			4: line 51 costUpTo6K was spelled incorrectly as costupto6k. Flagged by IDE
			5: line 60 output was fee and not the total cost. Was not getting the desired output.
*/

#include <cstdlib>
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	double gallons, charge = 0, total;
	const int fee = 15;
	double costUpTo6K = 2.35,
		costUpTo20K = 3.75,
		costOver20K = 6.00;

	//Get gallon input
	cout << "Enter the total number of gallons used, divided by 1000: ";
	cin >> gallons;

	//Over 20k gallons
	if (gallons > 20) {
		charge = (gallons - 20) * costOver20K;	//Only use gallons over 20k to determine extra cost
		charge = charge + (14 * costUpTo20K);	
		charge = charge + (6 * costUpTo6K);
	}
	//Between 6k and 20k gallons
	else if (gallons > 6 && gallons <= 20) {
		charge = (gallons - 6) * costUpTo20K;	//Only use gallons over 6k to determine extra cost
		charge = charge + (6 * costUpTo6K);
	}
	//Under 6k gallons
	else {
		charge = gallons * costUpTo6K;
	}


	total = charge + fee;						//Add fee to get total cost

	//Output gallons used and cost
	cout << "You have used " << gallons << " thousand gallons of water." << endl;
	cout << "Your total water bill is $" << setprecision(2) << fixed << total;

	return 0;
}