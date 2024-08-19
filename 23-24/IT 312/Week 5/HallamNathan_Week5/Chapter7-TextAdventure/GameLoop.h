/*
Name		: Nathan Hallam
Course		: IT-132
Date		: 7th April, 2024
Project NO	: 5-2
File Name	: GameLoop.h
Description : Header file defining public and constant functions for the GameLoop.cpp file
Additions	:
		   1: Added declaration for evaluating the choice the player made
		   2: Added declaration for printing types of consoles to choose from
		   3: Added declaration for evaluating the console type selected by the player
*/

#pragma once

#include "Player.h"
#include "PlayerChoices.h"
#include "ConsoleTypes.h"

class Game
{
private:
	Player m_player;

	void Welcome();
	void GivePlayerChoices() const;
	void GetPlayerInput(std::string& playerInput) const;
	void EvaluatePlayerChoice(PlayerOptions choice);
	void GiveConsoleTypeChoices() const;
	ConsoleTypes EvaluateConsoleType(std::string& playerInput) const;
	PlayerOptions EvaluateInput(std::string& playerInput) const;
	

public:

	void RunGame();
};