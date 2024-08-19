/*
Name		: Nathan Hallam
Course		: IT-132
Data		: 31st March, 2024
Project NO	: 4-2
File Name	: HallamNathan_LoopArrays.cpp
Description : This program loops through to create an array based on user input 
			  and then sorts the array in order of smallest integer to largest.
			  Format the code following the code styling document.
*/


#include <iostream>
#include <cstdlib>
using namespace std;

void main()
{
	int array[10], 
		t;

	//Fill in array with integer values
	for (int x = 0; x < 10; x++) {
		cout << "Enter Integer No. " << x + 1 << " : " << endl;
		cin >> array[x];
	}

	//Sort array of values in ascending order
	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 9; y++) {
			//If the current index's value is larger than the next index's value
			if (array[y] > array[y + 1]) {
				//Swap the values
				t = array[y];
				array[y] = array[y + 1];
				array[y + 1] = t;
			}
		}
	}

	//Print each value in the array
	cout << "Array in ascending order is : ";
	for (int x = 0; x < 10; x++)
		cout << endl << array[x];
	return;
}