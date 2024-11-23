/*
Name		: Nathan Hallam
Course		: IT-132
Date		: 21st April, 2024
Project NO	: 7.1
File Name	: DiceFaces.h
Description : File containing ASCII art for the faces of a d6
*/

#pragma once

#include <string>
using namespace std;

class DiceFaces {
public:
	string faces[6] = {

		" -------\n"
		"|       |\n"
		"|   O   |\n"
		"|       |\n"
		" -------",

		" -------\n"
		"| O     |\n"
		"|       |\n"
		"|     O |\n"
		" -------",

		" -------\n"
		"| O     |\n"
		"|   O   |\n"
		"|     O |\n"
		" -------",

		" -------\n"
		"| O   O |\n"
		"|       |\n"
		"| O   O |\n"
		" -------",

		" -------\n"
		"| O   O |\n"
		"|   O   |\n"
		"| O   O |\n"
		" -------",

		" ------- \n"
		"| O   O |\n"
		"| O   O |\n"
		"| O   O |\n"
		" -------"
	};
};
