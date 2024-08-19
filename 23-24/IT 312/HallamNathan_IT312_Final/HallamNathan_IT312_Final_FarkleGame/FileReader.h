/*
Name		: Nathan Hallam
Course		: IT-132
Date		: 21st April, 2024
Project NO	: 7.1
File Name	: FileReader.h
Description : Header file containing the function declaration for reading a file
*/

#pragma once
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class FileReader {

public:
	static string ReadFile(string fileName);
};