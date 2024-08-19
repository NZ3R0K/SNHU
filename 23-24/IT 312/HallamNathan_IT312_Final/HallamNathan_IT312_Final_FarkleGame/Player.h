/*
Name		: Nathan Hallam
Course		: IT-132
Date		: 21st April, 2024
Project NO	: 7.1
File Name	: Player.h
Description : Header file containing all the information associated with the player in a game.
			  Name, Rank, Score
*/

#pragma once
#include <string>

using namespace std;

class Player {
	string _name;					//Alias for the player
	int _score = 0;					//The amount of points the player has cashed
	int scoreboardPosition = -1;	//Cached value for what rank the player is on the scoreboard

	
public:
	//Constructor
	Player() {}

	//Returns true if the player can be placed on the scoreboard,
	// otherwise false
	bool OnScoreboard() {
		if (_score >= 500) {
			return true;
		}

		return false;
	}

	//Sets the players rank on the scoreboard
	void SetScoreboardPosition(int pos) {
		scoreboardPosition = pos;
	}

	//Returns the players position on the scoreboard
	int GetScoreboardPosition() {
		return scoreboardPosition;
	}

	//Returns the players current score
	int GetScore() {
		return _score;
	}

	//Adds points to the scoreboard given the sum of points
	void AddScore(int points) {
		_score += points;
	}

	//Sets the players name
	void SetName(string name) {
		_name = name;
	}

	//Returns the players name
	string GetName() {
		return _name;
	}
};