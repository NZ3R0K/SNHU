/*
Name		: Nathan Hallam
Course		: IT-132
Date		: 14th April, 2024
Project NO	: 6-1
File Name	: HallamNathan_WriteToFile.cpp
Description : A program that reads and writes to a file after prompting the user for information on the number of players, their names, and their scores.
Sources		:
				https://cplusplus.com/reference/fstream/fstream/?kw=fstream
				https://www.guru99.com/cpp-file-read-write-open.html
Notes		: Did not use C++/CLI I/O as I did not have libraries and felt fstream was easier to implement for this assignment.
*/

#include <iostream>
#include <fstream>
#include "HallamNathan_Player.h"
using namespace std;

//Definitions
bool ReadFromFile(string fileName, string& input);
void WriteToFile(string fileName, string& input, int numOfPlayers, Player* players);
void GetPlayerInput(string& playerInput);


void main() {
	static string fileName = "my_file.txt";	//Static string var for file name
	int numOfPlayers = 0;					//Number of players in game
	string input;							//Input variable for user input
	Player* players = new Player[0];		//Array of players

	//Get integer for number of players input and repeat if input is not valid
	//https://stackoverflow.com/questions/10349857/how-to-handle-wrong-data-type-input
	while (cout << "How many players are there today? " &&
		!(cin >> numOfPlayers) &&
		numOfPlayers <= 0)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	players = new Player[numOfPlayers];

	//Populate each player in array
	for (int i = 0; i < numOfPlayers; i++) {
		//Prompt for name
		cout << "What is player " << i + 1 << "'s name ? ";
		GetPlayerInput(input);

		//Set name
		players[i].SetName(input);

		//Prompt for score
		cout << "What is " << players[i].GetName() << "'s score? ";
		GetPlayerInput(input);

		//Set score
		players[i].SetScore(stoi(input));

		//Clear console
		system("cls");
	}

	//Read from file, if already exists and user wants to overwrite then write to file
	if (ReadFromFile(fileName, input)) {
		WriteToFile(fileName, input, numOfPlayers, players);
	}
}	


//Reads from a file if it exists, otherwise creates a new file.
//If the file already exists it will be read then prompts the user if it should be overwritten 
// - returning true if it should be overwritten otherwise false
bool ReadFromFile(string fileName, string& input) {
	fstream file;
	bool returnType = false;

	file.open(fileName, ios::in);

	//File does not exist
	if (!file) {
		cout << "File does not exist..." << endl;
		cout << "Creating new file!" << endl;
	}
	//File does exist
	else {
		cout << "File found... Reading..." << endl;

		char out;

		while (true) {
			if (file.eof()) {
				break;
			}

			for (string line; getline(file, line);) {
				cout << line << endl;
			}
		}

		cout << endl << endl;

		while (true) {
			cout << "Do you wish to overwrite the file?" << endl;
			cout << "0: YES\n1: NO" << endl;

			GetPlayerInput(input);

			//if Yes
			if (input.compare("0") == 0) {
				returnType = true;
				break;
			}
			//if No
			else if (input.compare("1") == 0) {
				returnType = false;
				break;
			}
			//if Invalid
			else {
				continue;
			}
		}

		file.close();
		return returnType;
	}
}


//Writes to file
void WriteToFile(string fileName, string& input, int numOfPlayers, Player* players) {
	fstream file;
	
	file.open(fileName, ios::out);


	//file failed to create
	if (!file) {
		cout << "File not created!";
	}
	else {
		cout << "File created successfully!";

		for (int i = 0; i < numOfPlayers; i++)
		{
			file << players[i].GetName() << ": " << players[i].GetScore() << "\n";
		}

		file.close();
	}
}


//Gets player input and stores it at given variable address
void GetPlayerInput(string& playerInput) {
	cin >> playerInput;
}