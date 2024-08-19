/*
Name		: Nathan Hallam
Course		: IT-132
Date		: 7th April, 2024
Project NO	: 5-2
File Name	: GameLoop.cpp
Description : Core of the program defining all functions. 
Additions	:
		   1: Added prompt for prefered console type choice in GivePlayerChoices
		   2: Added evauluation code to handle setting console type
		   3: Added implementation of EvaluatePlayerChoice() function defined in GameLoop.h
		   4: Added local variable in RunGame() that holds the players choice to be used by EvaluatePlayerChoice()
		   5: Added functions to print console types, and evaluate said types
*/

#include "GameLoop.h"
#include <iostream>

using namespace std;

void Game::Welcome()
{
	cout << "Welcome to Text Game!" << endl << endl;
	cout << "What is your name?" << endl << endl;

	string name;
	cin >> name;
	m_player.SetName(name);

	cout << endl << "Hello " << m_player.GetName() << endl;
}

//Prints what main console options the player can choose from
void Game::GivePlayerChoices() const
{
	cout << "Enter a number" << endl << endl;
	cout << "1: Quit" << endl;
	cout << "2: Set Preferred Console Type" << endl << endl;	//Prompt for prefered console type
}

//Given the playerinput address, set the address via cin
void Game::GetPlayerInput(string& playerInput) const
{
	cin >> playerInput;
}

//Given the playeroptions, evaluate based on choice
void Game::EvaluatePlayerChoice(PlayerOptions choice)
{
	GiveConsoleTypeChoices();

	if (choice == PlayerOptions::None)
	{
		cout << "Somehow you did the impossible... Choosing nothing..." << endl << endl;
		return;
	}
	else if (choice == PlayerOptions::Quit)
	{
		cout << "You should have quit by now, yet here you are?" << endl << endl;
		return;
	}
	else if (choice == PlayerOptions::SetConsole)
	{
		cout << "What is your preferred console type?" << endl << endl;

		string playerInput;
		GetPlayerInput(playerInput);

		//Set the players console type based on the input evaluation, failed or incorrect values return None console type
		m_player.SetPreferredConsole(EvaluateConsoleType(playerInput));

		//if the preferred console type was not set, do no print chosen outcome
		if (m_player.GetPreferredConsole() != ConsoleTypes::None)
			cout << "You have chosen to use the " << m_player.GetPreferredConsoleAsString() << " type!" << endl << endl;
	}
}

//Prints choices for what console types are available
void Game::GiveConsoleTypeChoices() const
{
	cout << "Enter a number" << endl << endl;
	cout << "0: Back" << endl;
	cout << "1: Standard" << endl;
	cout << "2: Colorized" << endl;
	cout << "3: Custom" << endl;
	cout << "4: IDE" << endl;
	cout << "5: Web" << endl;
	cout << "6: Emulated" << endl;
}

//Given the playerinput, evaluate what console type to return
ConsoleTypes Game::EvaluateConsoleType(string& playerInput) const
{
	ConsoleTypes type = ConsoleTypes::None;
	
	if (playerInput.compare("0") == 0)
	{
		type = ConsoleTypes::None;
	}
	if (playerInput.compare("1") == 0)
	{
		type = ConsoleTypes::Standard;
	}
	else if (playerInput.compare("2") == 0)
	{
		type = ConsoleTypes::Colorized;
	}
	else if (playerInput.compare("3") == 0)
	{
		type = ConsoleTypes::Custom;
	}
	else if (playerInput.compare("4") == 0)
	{
		type = ConsoleTypes::IDE;
	}
	else if (playerInput.compare("5") == 0)
	{
		type = ConsoleTypes::Web;
	}
	else if (playerInput.compare("6") == 0)
	{
		type = ConsoleTypes::Emulated;
	}
	else
	{
		//Fallback
		return ConsoleTypes::None;
	}



	return type;
}

//Given the playerinput, evaluate the main console options
PlayerOptions Game::EvaluateInput(string& playerInput) const
{
	PlayerOptions chosenOption = PlayerOptions::None;

	//Quit
	if (playerInput.compare("1") == 0)
	{
		cout << "You have chosen to Quit!" << endl << endl;
		chosenOption = PlayerOptions::Quit;
	}
	//Set prefered console type
	else if (playerInput.compare("2") == 0)
	{
		cout << "You have chosen to set your preferred console type!" << endl << endl;
		chosenOption = PlayerOptions::SetConsole;
	}
	else
	{
		cout << "Try again!" << endl << endl;
	}

	return chosenOption;
}

void Game::RunGame()
{
	Welcome();

	bool shouldEnd = false;
	PlayerOptions choice;
	while (shouldEnd == false)
	{
		GivePlayerChoices();

		string playerInput;
		GetPlayerInput(playerInput);

		choice = EvaluateInput(playerInput);
		shouldEnd = choice == PlayerOptions::Quit;

		if (shouldEnd)	//Guard Clause: break loop early
			continue;

		EvaluatePlayerChoice(choice);	//Evaluate options other than QUIT
	}
}