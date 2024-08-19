/*
Name		: Nathan Hallam
Course		: IT-132
Data		: 10th March, 2024
Project NO: 1-2
*/

#include <cstdlib>
#include <iostream>
using namespace std;

int main()
{
	float classAverage = 90.7; //Decimal number
	char letterScore = 'A'; //Single letter
	int testScore = 95; //Whole number value
	float classTestAverage = 88.4f; //Decimal number, notice the 'f' at the end
	enum colorCode {
		Green = 1,
		Yellow = 5,
		Red = 10
	} gradebookColor; //Stores list of values
	gradebookColor = Green; //This line does not need a declaration, it was declared in the line above
	bool isStudentPassing = true; //Could be true or false

	//Check for success
	cout << "The class average is currently "
		<< classAverage
		<< endl;
	cout << "The class test average was "
		<< classTestAverage
		<< endl;
	cout << "Your test score was "
		<< testScore
		<< endl;
	cout << "Your current letter score is "
		<< letterScore
		<< endl;
	cout << "The color of your gradebook entry is "
		<< gradebookColor
		<< endl;
	cout << "Are you passing? "
		<< boolalpha		//This line allows the word 'true' or 'false' to be printed instead of '0' or '1'
		<< isStudentPassing
		<< endl;
	return 0;
}