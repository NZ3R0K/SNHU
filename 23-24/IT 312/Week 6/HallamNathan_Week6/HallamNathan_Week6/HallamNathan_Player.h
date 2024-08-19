/*
Name		: Nathan Hallam
Course		: IT-132
Date		: 14th April, 2024
Project NO	: 6-1
File Name	: HallamNathan_Player.h
Description : Header file containing the name and score of a player and the accompanying functions to get and set them.
*/

#pragma once

#include <string>

using namespace std;

class Player {
	string name;
	int score;


public:
	void SetScore(int score) {
		this->score = score;
	}

	int GetScore() {
		return score;
	}

	void SetName(string name) {
		this->name = name;
	}

	string GetName() {
		return name;
	}
};