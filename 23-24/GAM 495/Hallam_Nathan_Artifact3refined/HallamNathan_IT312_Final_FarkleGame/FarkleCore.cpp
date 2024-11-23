/*
Name		: Nathan Hallam
Course		: IT-132
Date		: 21st April, 2024
Project NO	: 7.1
File Name	: FarkleCore.cpp
Description : Main core for the program containing the functional loop.
			  Also contains functions for getting user input for the general menu and printing information
*/

#include <cstdlib>
#include <iostream>
#include <conio.h>	//for getch

#include "Player.h"
#include "FarkleCore.h"
#include "GameInfo.h"
#include "FileReader.h"
#include "Colors.h"

GameInfo Game;

void FarkleCore::CoreLoop() {
	program_start:

	string input = "";

	Game.Initialize();

	system("cls");

	Game.PrintRules();

	WaitForKey();

	do {
		system("cls");

		//Upate scoreboard with new player scores
		Game.UpdateScoreboard();

		if (Game.CheckForWinner()) {
			int endGame = -1;

			//Loop for valid input
			do {
				//Prompt if game should restart
				cout << "Would you like to start over? Y / N?";
				cin >> input;

				//Check input
				endGame = CalculateEndGameInput(input);

				//If game should restart
				if (endGame == 1) {

					Game.Reset();

					goto program_start;
				}
				//If game should end
				else if (endGame == 0) {
					input = "Q";
				}
			} while (endGame == -1);
		}
		//If no winner yet
		else {
			PrintTurnInfo(); //Print player turn, score, and rank
			PrintCommands(); //Print menu commands

			//Prompt for input
			Game.PrintWithColor("What is your command? ", Colors::yellow, Colors::black);
			GetInput(input);

			CalculateInput(input);	//Determine what menu command was selected and continue based on that selection

			WaitForKey();

			//If the game does not have enough players, quit
			if (Game.GetPlayerCount() < 2) {
				input = "Q";
				Game.PrintWithColor("\nGame has less than the minimal amount of players to play (2).\n"
										"Game will now end...\n", Colors::red, Colors::black);
				WaitForKey();
			}
		}
	} while (input != "Q" && input != "q");
}

//Prints game commands to the console
void FarkleCore::PrintCommands() const
{
	Game.PrintWithColor(
		"Commands\n\n"
		"Q - Quit\n"
		"D - Drop Out\n"
		"R - Roll Dice [" + to_string(Game.GetUnrolledDiceCount()) + " dice]\n"
		"C - Cash Dice [" + to_string(Game.GetCurrentScore()) + " points]\n"
		"S - Show Scoreboard\n"
		"H - How to Play\n\n\n",Colors::turquoise, Colors::black);
}

//Prints information on the players current turn and their info
void FarkleCore::PrintTurnInfo() const {
	
	Game.PrintWithColor("It is " + Game.GetCurrentPlayer().GetName() + "'s Turn\n\n", Colors::green, Colors::black);
	Game.PrintWithColor("You have " + to_string(Game.GetCurrentScore()) + " points that can be cashed.\n", Colors::green, Colors::black);

	if (Game.GetCurrentPlayer().OnScoreboard())
		Game.PrintWithColor("You are rank " + to_string(Game.GetCurrentPlayer().GetScoreboardPosition() + 1) +
			" with " + to_string(Game.GetCurrentPlayer().GetScore()) + " points.\n\n", Colors::green, Colors::black);
	else
		Game.PrintWithColor("You are not on the scoreboard: get 500 points to enter the race!\n\n", Colors::brown, Colors::black);
}

//Gets an input from cin and stores it in the given string variable
void FarkleCore::GetInput(string& input) const
{
	cin >> input;
}

//Given a command, process the input and perform its given action
void FarkleCore::CalculateInput(string command) const
{
	//Quit program
	if (command == "Q" || command == "q") {
		return;
	}
	//Roll
	else if (command == "R" || command == "r") {
		Game.RollDice();
	}
	//Cash Dice
	else if (command == "C" || command == "c") {
		CashScore();
	}
	//View Scoreboard
	else if (command == "S" || command == "s") {
		PrintScoreboard();
	}
	//Drop out
	else if (command == "D" || command == "d") {
		Game.RemovePlayer(Game.GetTurn());
	}
	//How to play
	else if (command == "H" || command == "h") {
		system("cls");
		Game.PrintRules();
	}
	//Default
	else {
		Game.PrintWithColor("Command not recognized...\n\n", Colors::red, Colors::black);
	}
}

//Used to determine if the input at the end of a game is a yes to continue a new game or a no to close the program
int FarkleCore::CalculateEndGameInput(string input) const {
	//If continue playing in new game
	if (input == "Y" || input == "y")
		return 1;
	//Stop program
	else if (input == "N" || input == "n")
		return 0;
	//What?
	else
		return -1;
}

//Prints the scoreboard to the console
void FarkleCore::PrintScoreboard() const {
	system("cls");
	
	//Cache information about game for use
	int playerCount = Game.GetPlayerCount();
	int* scoreboard = Game.GetScoreboard();
	Player* players = Game.GetPlayers();

	Game.PrintWithColor("=========== SCOREBOARD ===========\n", Colors::cyan, Colors::black);

	//For every player in the game
	for (int i = 0; i < playerCount; i++) {
		int playerIndex = scoreboard[i];			//Player index based on scoreboard position

		//If the player is on the scoreboard
		if (players[playerIndex].OnScoreboard()) {
			//Print position, name, and score
			cout << "[" << i + 1 << "] " << players[playerIndex].GetName() << " : " << scoreboard[i + playerCount] << endl;
		}
		else {
			//Else print name and lack of position
			cout << "[-] : " << players[playerIndex].GetName() << endl;
		}
	}
}

//Takes the score from the turn and adds it to the players final score
void FarkleCore::CashScore() const {
	system("cls");
	
	if (Game.GetCurrentScore() == 0) {
		Game.PrintWithColor("You have not scored any points to cash in. ROLL THE DICE!\n\n", Colors::red, Colors::black);
		return;
	}

	if (!Game.GetCurrentPlayer().OnScoreboard() && Game.GetCurrentScore() < 500) {
		Game.PrintWithColor("You must have 500 points to get on the scoreboard.\n\n", Colors::red, Colors::black);
		return;
	}

	//Add score to current player
	Game.GetCurrentPlayer().AddScore(Game.GetCurrentScore());

	Game.PrintWithColor("You cashed " + to_string(Game.GetCurrentScore()) + " points!\n", Colors::green, Colors::black);
	Game.PrintWithColor("Your score is now " + to_string(Game.GetCurrentPlayer().GetScore()) + "\n\n", Colors::green, Colors::black);

	Game.NextTurn();
}

//Waits for a key input, prints prompt
void FarkleCore::WaitForKey() const {
	Game.PrintWithColor("Press any key to continue...\n", Colors::yellow, Colors::black);
	_getch();
}