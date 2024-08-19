/*
Name		: Nathan Hallam
Course		: IT-132
Date		: 21st April, 2024
Project NO	: 7.1
File Name	: FileReader.cpp
Description : A helper file that takes in a file name and reads all lines in said file, returning a string containing its contents.
Sources		:
				https://cplusplus.com/reference/fstream/fstream/?kw=fstream
				https://www.guru99.com/cpp-file-read-write-open.html
*/

#include "FileReader.h"

//Reads a file of the given file name and returns the contents of said file as a string.
string FileReader::ReadFile(string fileName) {
	string output;
	fstream file;

	//Open file to read
	file.open(fileName, ios::in);

	//If file exists
	if (file) {
		char out;

		while (true) {
			//If end of file is found, break loop
			if (file.eof()) {
				break;
			}

			//Read each line and print to console
			for (string line; getline(file, line);) {
				output.append(line + "\n");
			}
		}

		output.append("\n\n");
	}
	else return "";

	//Close file once done
	file.close();

	return output;
}