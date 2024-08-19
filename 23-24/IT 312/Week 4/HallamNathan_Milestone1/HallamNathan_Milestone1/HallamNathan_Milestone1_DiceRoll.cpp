/*
Name		: Nathan Hallam
Course		: IT-132
Data		: 31st March, 2024
Project NO	: 4-3
File Name	: HallamNathan_Milestone1_DiceRoll.cpp
Description : Design a program that rolls 2 dice and allows the user to guess the sum of the dices faces.
			  Roll the dice again if the sum of the dice faces does not equal the guess.
			  The output of each roll is printed to the console.
*/


#include <iostream>
#include <cstdlib>
#include <stdlib.h>     // srand
#include <time.h>       // time

using namespace std;

int* RollDice(int[2], int&);
int SumOfRoll(int[2]);

void main() {
	int input = -1, 
		rolls = 0, 
		diceRoll[2] = { 0 };

	do {
		srand(time(NULL)); // initialize random seed:

		//Get user guess until valid
		do {
			//Get user guess
			cout << "Take a guess for the sum of 2d6 (2 - 12)" << endl;
			cin >> input;

			//Check if input is an integer
			if (!cin.good()) {
				cout << "\nGuess must be an integer 2 - 12" << endl;	//Prompt for proper input
				cin.clear();											//Clear cin for new guess
				cin.ignore(numeric_limits<streamsize>::max(), '\n');	//Ignore last cin
				continue;
			}

			//Check if input is a valid integer 2 - 12
			if (input < 2 || input > 12) {
				cout << "\nGuess must be 2 - 12" << endl;				//Prompt for proper input
				continue;
			}
		} while (input < 2 || input > 12);

		//Roll the dice until the guess is achieved
		do {
			RollDice(diceRoll, rolls);
		} while (SumOfRoll(diceRoll) != input);

		cout << "\nIt took " << rolls << " rolls  to achieve your guess of " << input << endl;

		//Ask user to run program again
		do {			
			//Get user input
			cout << "\nDo you want to guess again?" << endl;
			cout << "[0] NO?\n[1] YES?" << endl;

			cin >> input;

			//Check if input is an integer
			if (!cin.good()) {
				cout << "\nInput must be an integer 0 - 1" << endl;		//Prompt for proper input
				cin.clear();											//Clear cin for new input
				cin.ignore(numeric_limits<streamsize>::max(), '\n');	//Ignore last cin
				input = -1;												//Set input to invalid value to allow loop
				continue;
			}

			//Check if input is a valid integer 0 - 1
			if (input < 0 || input > 1) {
				cout << "\nInput must be 0 - 1" << endl;				//Prompt for proper input
				continue;
			}
		} while (input < 0 || input > 1);

		rolls = 0;
	} while (input == 1);
}

//Rolls the dice and returns them. 
//Counts the amount of rolls given the tally.
int* RollDice(int diceRoll[2], int & rolls) {

	diceRoll[0] = rand() % 6 + 1;
	diceRoll[1] = rand() % 6 + 1;

	rolls++;

	//Print outcome
	cout << "[" << rolls << "]" << "\t" << diceRoll[0] << " + " << diceRoll[1] << " = " << SumOfRoll(diceRoll) << endl;

	return diceRoll;
}

//Adds together the faces of two dice and returns the sum.
int SumOfRoll(int diceRoll[2]) {
	return diceRoll[0] + diceRoll[1];
}