/*
Name		: Nathan Hallam
Course		: IT-132
Date		: 14th April, 2024
Project NO	: 6-3
File Name	: HallamNathan_FPBB4_ReadFromFile.cpp
Description : Read from a text document the transcribed rules for your chosen game, and display them in the console.
Additions	: Ability to open any txt file given a file name.
Limitations	: 
			: Does not allow file browsing / can not locate files outside project directory.
			: Does not add file extension if missing, must type in .txt after file name.
Sources		: 
				https://cplusplus.com/reference/fstream/fstream/?kw=fstream
				https://www.guru99.com/cpp-file-read-write-open.html
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void main() {
	string fileName;
	fstream file;

	//Prompt for file
	cout << "What is the file name?" << endl;
	cin >> fileName;

	//Open file to read
	file.open(fileName, ios::in);

	//If file does not exist
	if (!file) {
		cout << "File does not exist!";
	}
	//If file exists
	else {
		cout << "\n\nOpening file " << fileName << endl << endl;

		char out;

		while (true) {
			//If end of file is found, break loop
			if (file.eof()) {
				break;
			}

			//Read each line and print to console
			for (string line; getline(file, line);) {
				cout << line << endl;
			}
		}

		cout << endl << endl;
	}

	//Close file once done
	file.close();
}