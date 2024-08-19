/*
Name		: Nathan Hallam
Course		: IT-132
Data		: 17th March, 2024
Project NO	: 2-1
File Name	: HallamNathan_GPAHonorsCalc.cpp
Description : Using predesigned pseudocode create a program that calculates a students GPA and Honors level given 4 letter grades.
*/

#include <cstdlib>
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	double gpa = 0;

	//Honor levels
	bool summa_cum_laude = false,
		magna_cum_laude	 = false,
		cum_laude		 = false,
		no_honors		 = false;

	char grades[4];
	int numberOfCourses = sizeof(grades) / sizeof(*grades);	//Setup for if a value other than 4 is to be used

	//Get a letter grade for each course
	for (int grade = 0; grade < numberOfCourses; grade++) {

		cout << "What is the letter grade for your " << grade + 1 << "th class? ";
		cin >> grades[grade];

		//Convert letter grades to numerical value
		if (grades[grade] == 'A' || grades[grade] == 'a') {
			grades[grade] = '4';
		}
		else if (grades[grade] == 'B' || grades[grade] == 'b') {
			grades[grade] = '3';
		}
		else if (grades[grade] == 'C' || grades[grade] == 'c') {
			grades[grade] = '2';
		}
		else if (grades[grade] == 'D' || grades[grade] == 'd') {
			grades[grade] = '1';
		}
		else {
			grades[grade] = '0';
		}

		gpa += grades[grade] - '0';	//Subtract the ASCII int value for zero to get real value for grade ie 0 - 4
	}


	gpa = gpa / numberOfCourses; //Calculate average

	//Get honors level from gpa
	if (gpa >= 3.9) {
		summa_cum_laude = true;
	}
	else if (gpa < 3.9 && gpa >= 3.8) {
		magna_cum_laude = true;
	}
	else if (gpa < 3.8 && gpa >= 3.65) {
		cum_laude = true;
	}
	else {
		no_honors = true;
	}

	//Write gpa to screen
	cout << "\nYour GPA is " << gpa << "." << endl;

	//Write to screen honors level based on gpa
	cout << "Graduating summa cum laude is " << (summa_cum_laude ? "true" : "false") << "." << endl;
	cout << "Graduating magna cum laude is " << (magna_cum_laude ? "true" : "false") << "." << endl;
	cout << "Graduating cum laude is " << (cum_laude ? "true" : "false") << "." << endl;
	cout << "Graduating without honors is " << (no_honors ? "true" : "false") << "." << endl;

	return 0;
}