/*
Name		: Nathan Hallam
Course		: IT-132
Date		: 21st April, 2024
Project NO	: 7.1
File Name	: Game.cpp
Description : File containing functions related to the game. 
			  Includes the player, dice roll, current turn and turn state, scoreboard tracking
Sources		:
	Console Color : https://www.codespeedy.com/color-text-output-in-console-in-cpp/#:~:text=In%20this%20article%2C%20we%20will%20discuss%20how%20we,output%20console.%20Handle%20var_name%20%3D%20GetStdHandle%28STD_OUTPUT_HANDLE%29%3B%20SetConsoleTextAttribute%28var_name%2C%20color_code%29%3B
	Resize Array : https://stackoverflow.com/questions/8056746/copying-from-one-dynamically-allocated-array-to-another-c
*/

#include <iostream>
#include <algorithm>				//for sort
#include <conio.h>					//for getch
#include <windows.h>				//for handle to print console colors

#include "GameInfo.h"				//Contains game function declarations
#include "Player.h"					//Contains player data
#include "FileReader.h"				//Helper file to read text documents (used to read rules)
#include "DiceCombinationCodes.h"	//Contains enum for assigning each combination to an integer
#include "Colors.h"					//Contains an enum containing different colors used to change console text color
#include "DiceFaces.h"				//Contains array of ASCII art for dice faces

DiceFaces diceFaces;				//ASCII art for dice faces

Player* players = new Player[1];	//Array of players in the game
Player winner;						//Player with the highest winning score

const int MAX_DICE = 6;				//Max number of dice that can be rolled
int* scoreboard = new int[2];		//Array of player positions and their scores on the scoreboard
int numOfPlayers = 0,				//Number of players in the game
	currentTurn = -1,				//What player currently has control
	savedRoll[MAX_DICE] = { 0 },	//The scoring sides of the current dice roll saved by the player
	currentRoll[MAX_DICE] = { 0 },	//Array of dice faces for the current roll
	currentScore = 0,				//Keeps track of the current score earned this turn
	diceScored = 0;					//Increments up when score dice are put aside. Used to know how many dice to roll when rerolling

#pragma region Scoreboard
	int GameInfo::GetCurrentScore() const {
		return currentScore;
	}

	//Update the ranks of all players on the scoreboard
	void GameInfo::UpdateScoreboard() const {
		//Create temp array to sort players by score while keeping play order
		Player* temp = new Player[numOfPlayers];
		scoreboard = new int[numOfPlayers * 2];

		//Copy each object to the new array without copying address
		for (int i = 0; i < numOfPlayers; i++)
			temp[i] = players[i];

		//Sort the array
		sort(temp, temp + numOfPlayers, ScoreComparer);

		//For every player in the game
		for (int pIndex = 0; pIndex < numOfPlayers; pIndex++) {
			//For every rank on the scoreboard
			for (int rank = 0; rank < numOfPlayers; rank++) {
				//If the current players name is the same as a rank on the scoreboard
				if (players[pIndex].GetName() == temp[rank].GetName()) {
					players[pIndex].SetScoreboardPosition(rank);				//Save the players rank to the player object
					scoreboard[rank + numOfPlayers] = temp[rank].GetScore();	//Save the players score to the scoreboard
					scoreboard[rank] = pIndex;									//Save the players index to the scoreboard
				}
			}
		}

		delete[] temp;	//free memory
	}

	//Return the array of player ranks, and score associations
	int* GameInfo::GetScoreboard() const {
		return scoreboard;
	}
#pragma endregion

#pragma region Players
	//Returns the number of players participating in the game
	int GameInfo::GetPlayerCount() const {
		return numOfPlayers;
	}

	//Returns the array of players
	Player* GameInfo::GetPlayers() {
		return players;
	}

	//Returns the player from the array given the position in the array
	Player& GameInfo::GetPlayer(int arrayPosition) {
		return players[arrayPosition];
	}

	//Returns the current player whose turn it is
	Player& GameInfo::GetCurrentPlayer() {
		return players[currentTurn];
	}

	//Adds a player to the array of players
	void GameInfo::AddPlayer(string playerName) {
		numOfPlayers++;	//Increment number of players up

		//Resize array to fit new player
		ResizePlayerArray(players, numOfPlayers);

		players[numOfPlayers - 1].SetName(playerName);					//Set name
		players[numOfPlayers - 1].SetScoreboardPosition(numOfPlayers);	//Set initial scoreboard position
	}

	//Removes a player from the array give the players position in the array
	void GameInfo::RemovePlayer(int arrayPosition) const {
		//Decrement number of players
		numOfPlayers--;

		//if no players, end early, should not be called as program quits when under 2 players
		if (numOfPlayers == 0) {
			ClearPlayers();
			return;
		}

		int p = 0;										//placeholder
		Player* temp = new Player[numOfPlayers];		//Temp dynamic array

		//loop through the array and copy the elements
		for (int i = 0; i < numOfPlayers; i++) {
			//If on the player that wants to drop out, increment placeholder (skip that player)
			if (i == arrayPosition) p++;

			temp[i] = players[p];	//Copy player data
			p++;					//Increment placeholder
		}

		delete[] players;	//free memory
		players = temp;		//copy back to original array

		//Prevent error for reading players array outside of bounds
		// /\Happened when droping out as last player in array
		if (currentTurn >= numOfPlayers) {
			currentTurn = 0;
		}
	}

	//Clears all players from the array
	void GameInfo::ClearPlayers() const {
		delete[] players;			//free memory
		players = new Player[1];	//Have at least one slot to start
	}
#pragma endregion

#pragma region Game
	//Get number of players in game and set aliases. Start first turn
	void GameInfo::Initialize() {
		int playerCount = 0;

		//Resets game state to initial (mainly used for when game restarts)
		Reset();

		srand(time(NULL)); // initialize random seed:

		do
		{
			//Prompt for player count
			PrintWithColor("How many players will be playing today? : ", Colors::yellow, Colors::black);
			cin >> playerCount;

			//If input is not an integer
			if (!cin) {
				PrintWithColor("Invalid Input!\n", Colors::red, Colors::black);

				cin.clear();	//Clear input
				cin.ignore();	//Ignore last input
				continue;
			}

			//Not enough players
			if (playerCount < 2) {
				PrintWithColor("Farkle requires at least 2 players to start...\n", Colors::red, Colors::black);
				continue;
			}

			break;
		} while (playerCount < 2);

		//Prompt for player aliases
		for (int i = 0; i < playerCount; i++)
		{
			string input;

			//prompt for name
			PrintWithColor("What is Player " + to_string(i + 1) + "'s alias?  ", Colors::yellow, Colors::black);

			cin >> input;			//get name

			AddPlayer(input);		//Add player to array with given name
		}

		//Set turn to first player in array
		currentTurn = 0;
	}

	//Resets all global values used for the game to their initial values
	void GameInfo::Reset() const {
		numOfPlayers = 0;
		players = new Player[1];
		currentTurn = -1;
		winner = Player();
		ResetDice();
	}

	//Checks for the player with the highest score
	bool GameInfo::CheckForWinner() {
		int winnerPos = -1,
			winnerScore = 0;

		for (int i = 0; i < numOfPlayers; i++) {
			//Get current players score
			int score = players[i].GetScore();

			//If that score is a winning score and it is the highest score thus far
			if (score >= 10000 && score >= winnerScore) {
				//set the new winning score
				winnerScore = score;
				//set the winning player
				winnerPos = i;
			}
		}

		//If there is a possible winner (has score over 10,000)
		if (winnerPos != -1) {
			//If the winner has been set and every other player has rolled again
			if (winner.GetName() == GetCurrentPlayer().GetName()) {
				PrintWithColor(players[winnerPos].GetName() + " wins the game with " + to_string(players[winnerPos].GetScore()) + " points!\n\n", Colors::cyan, Colors::black);
				winner = players[winnerPos];
				return true;	//End Game
			}
			else {
				PrintWithColor(players[winnerPos].GetName() + " is about to win with " + to_string(players[winnerPos].GetScore()) + " points!\n\n" ,Colors::cyan, Colors::black);
				winner = players[winnerPos];
			}
		}

		return false;
	}

	//Reads the associated text file for the game rules and returns its contents as a string
	void GameInfo::PrintRules() {
		cout << FileReader::ReadFile("farkle_rules.txt") << endl;
	}
#pragma endregion

#pragma region Dice
	//Returns the amount of dice that can be rolled subtracting the number of dice that have been scored
	int GameInfo::GetUnrolledDiceCount() const {
		//subtract the amount of dice that have been scored by the total number of dice
		return MAX_DICE - diceScored;
	}
	
	//Resets all dice rolled to 0 face value, resets the turn score to 0, and the count for how many dice were scored by the player
	void GameInfo::ResetDice() const
	{
		//For the total number of dice
		for (int i = 0; i < MAX_DICE; i++) {
			savedRoll[i] = 0;
		}

		currentScore = 0;
		diceScored = 0;
	}

	//Rolls up to 6 d6
	void GameInfo::RollDice() {	
		//Sort dice so that if dice are saved the proper elements in the array are updated
		sort(currentRoll, currentRoll + MAX_DICE);

		//Roll dice
		for (int i = diceScored; i < MAX_DICE; i++)
			currentRoll[i] = rand() % MAX_DICE + 1;

		//find all possible combinations of points in given roll
		ScoreDice(currentRoll, MAX_DICE - diceScored);
	}

	//Determines what combinations of score facing dice are available given a dice roll.
	void GameInfo::ScoreDice(int* roll, int diceToScore) {
		int pointsScored = 0,
			input = -1,
			combinations = 0;
		string output;			//used to append information and print in correct order

		// Selection multidimensional array indicies
		// (0i)Row: Input binding - (1i)Type of Cash - (2i) Start Index in array
		do {
			system("cls");
			output = "";

			//Sort dice in order of smallest to largest
			sort(roll, roll + MAX_DICE);

			//If all dice are scored - it is HOT DICE
			if (diceScored == MAX_DICE) {
				cout << "All dice have been scored - HOT DICE!" << endl;

				for (int i = 0; i < MAX_DICE; i++) {
					savedRoll[i] = 0;
				}

				//Reset scored dice count for current turn
				diceScored = 0;

				break;
			}

			//Dynamic array storing what score dice can be selected
			int* selection = new int[3]; 
			combinations = 0;		//How many selections are available

			//Print stats
			PrintWithColor("You scored " + to_string(currentScore) + " points this turn.\n" +
							"You scored " + to_string(pointsScored) + " points this roll.\n\n", Colors::green, Colors::black);

			//Print roll
			output.append("Your roll:\n");
			for (int i = 5; i >= 0; i--) {
				//If dice has been saved for points, skip
				if (roll[i] == 0)
					continue;
				
				//append dice face to output string
				output.append(diceFaces.faces[roll[i] - 1] + "\n");
			}

			PrintWithColor(output, Colors::cyan, Colors::black);
			output = "";	//clear output for later use

			//Oh boy, here it is - time to check for the points
			switch (diceToScore) {
#pragma region 6 dice rolled
			case 6:
#pragma region 6 of a kind
				//Check for 6 of a kind
				if (roll[0] == roll[1] &&
					roll[0] == roll[2] &&
					roll[0] == roll[3] &&
					roll[0] == roll[4] &&
					roll[0] == roll[5]) {
					output.append("[" + to_string(combinations) + "] Six of a kind (" +
										to_string(roll[0]) + "'s): 3000 points\n");

					//Resize array to add new combination
					ResizeIntArray(selection, (combinations + 1) * 3);
					selection[combinations * 3] = combinations;					//Binding
					selection[combinations * 3 + 1] = DiceComboCodes::SixofKind;//Code
					selection[combinations * 3 + 2] = 0;						//Index

					combinations++;
				}
#pragma endregion

#pragma region 2 sets of triplets
				//Check for 2 sets of triplets
				if (roll[0] == roll[1] &&
					roll[0] == roll[2] &&
					roll[3] == roll[4] &&
					roll[3] == roll[5]) {
					output.append("[" + to_string(combinations) + "] Two sets of triplets (" + 
										to_string(roll[3]) + "'s) & (" + 
										to_string(roll[0]) + "'s): 2500 points\n");

					//Resize array to add new combination
					ResizeIntArray(selection, (combinations + 1) * 3);
					selection[combinations * 3] = combinations;						//Binding
					selection[combinations * 3 + 1] = DiceComboCodes::TwosetsThree;	//Code
					selection[combinations * 3 + 2] = 0;							//Index

					combinations++;
				}
#pragma endregion

#pragma region 4 of a kind + set of 2
				//Check for 4 of a kind + set of 2 (type 1) - first 4 and last 2
				if (roll[0] == roll[1] &&
					roll[0] == roll[2] &&
					roll[0] == roll[3] &&
					roll[4] == roll[5]) {
					output.append("[" + to_string(combinations) + "] Four of a kind + a pair (" + 
										to_string(roll[0]) + "'s) & (" + 
										to_string(roll[4]) + "'s): 1500 points\n");

					//Resize array to add new combination
					ResizeIntArray(selection, (combinations + 1) * 3);
					selection[combinations * 3] = combinations;						//Binding
					selection[combinations * 3 + 1] = DiceComboCodes::FoursetsTwoT1;//Code
					selection[combinations * 3 + 2] = 0;							//Index

					combinations++;
				}
				//Check for 4 of a kind + set of 2 (type 2) - first 2 and last 4
				else if (roll[0] == roll[1] &&
					roll[2] == roll[3] &&
					roll[2] == roll[4] &&
					roll[2] == roll[5]) {
					output.append("[" + to_string(combinations) + "] Four of a kind + a pair (" +
						to_string(roll[0]) + "'s) & (" +
						to_string(roll[2]) + "'s): 1500 points\n");

					//Resize array to add new combination
					ResizeIntArray(selection, (combinations + 1) * 3);
					selection[combinations * 3] = combinations;						//Binding
					selection[combinations * 3 + 1] = DiceComboCodes::FoursetsTwoT2;//Code
					selection[combinations * 3 + 2] = 0;							//Index

					combinations++;
				}
#pragma endregion

#pragma region 3 pairs of 2
				//Check for 3 pairs of 2
				if (roll[0] == roll[1] &&
					roll[2] == roll[3] &&
					roll[4] == roll[5]) {
					output.append("[" + to_string(combinations) + "] Three pairs of 2 (" + 
										to_string(roll[0]) + "'s) & (" + 
										to_string(roll[2]) + "'s) & (" + 
										to_string(roll[4]) + "'s): 1500 points\n");

					//Resize array to add new combination
					ResizeIntArray(selection, (combinations + 1) * 3);
					selection[combinations * 3] = combinations;						//Binding
					selection[combinations * 3 + 1] = DiceComboCodes::ThreesetsTwo;	//Code
					selection[combinations * 3 + 2] = 0;							//Index

					combinations++;
				}
#pragma endregion

#pragma region Straight
				//Check for straight
				if (roll[0] == 1 &&
					roll[1] == 2 &&
					roll[2] == 3 &&
					roll[3] == 4 &&
					roll[4] == 5 &&
					roll[5] == 6) {
					output.append("[" + to_string(combinations) + "] Straight 1-6 : 1500 points\n");

					//Resize array to add new combination
					ResizeIntArray(selection, (combinations + 1) * 3);
					selection[combinations * 3] = combinations;					//Binding
					selection[combinations * 3 + 1] = DiceComboCodes::Straight;	//Code
					selection[combinations * 3 + 2] = 0;						//Index

					combinations++;
				}
#pragma endregion

#pragma endregion

#pragma region 5 dice rolled
				case 5:
#pragma region 5 of a kind
					//check for five of a kind (type 1) - first 5 array(0 - 4)
					if (roll[0] == roll[1] &&
						roll[0] == roll[2] &&
						roll[0] == roll[3] &&
						roll[0] == roll[4]) {
						output.append("[" + to_string(combinations) + "] Five of a kind (" + to_string(roll[0]) + "'s) : 2000 points\n");

						//Resize array to add new combination
						ResizeIntArray(selection, (combinations + 1) * 3);
						selection[combinations * 3] = combinations;						//Binding
						selection[combinations * 3 + 1] = DiceComboCodes::FiveofKindT1;	//Code
						selection[combinations * 3 + 2] = 0;							//Index

						combinations++;
					}
					//check for five of a kind (type 2) - last 5 array(1 - 5)
					else if (roll[1] == roll[2] &&
						roll[1] == roll[3] &&
						roll[1] == roll[4] &&
						roll[1] == roll[5]) {
						output.append("[" + to_string(combinations) + "] Five of a kind (" + to_string(roll[1]) + "'s) : 2000 points\n");

						//Resize array to add new combination
						ResizeIntArray(selection, (combinations + 1) * 3);
						selection[combinations * 3] = combinations;						//Binding
						selection[combinations * 3 + 1] = DiceComboCodes::FiveofKindT2;	//Code
						selection[combinations * 3 + 2] = 1;							//Index

						combinations++;
					}
#pragma endregion

#pragma endregion

#pragma region 4 dice rolled
				case 4:
#pragma region 4 of a kind
					//Check for four of a kind (type 1) - first 4 array(0 - 3)
					if (roll[0] == roll[1] &&
						roll[0] == roll[2] &&
						roll[0] == roll[3]) {
						output.append("[" + to_string(combinations) + "] Four of a kind (" + to_string(roll[0]) + "'s) : 1000 points\n");

						//Resize array to add new combination
						ResizeIntArray(selection, (combinations + 1) * 3);
						selection[combinations * 3] = combinations;						//Binding
						selection[combinations * 3 + 1] = DiceComboCodes::FourofKindT1;	//Code
						selection[combinations * 3 + 2] = 0;							//Index

						combinations++;
					}
					//Check for four of a kind (type 2) - last 4 array(2 - 5)
					else if (roll[2] == roll[3] &&
						roll[2] == roll[4] &&
						roll[2] == roll[5]) {
						output.append("[" + to_string(combinations) + "] Four of a kind (" + to_string(roll[2]) + "'s) : 1000 points\n");

						//Resize array to add new combination
						ResizeIntArray(selection, (combinations + 1) * 3);
						selection[combinations * 3] = combinations;						//Binding
						selection[combinations * 3 + 1] = DiceComboCodes::FourofKindT2;	//Code
						selection[combinations * 3 + 2] = 2;							//Index

						combinations++;
					}
					//Check for four of a kind (type 3) - middle 4 array(1 - 4)
					else if (roll[1] == roll[2] &&
						roll[1] == roll[3] &&
						roll[1] == roll[4]) {
						output.append("[" + to_string(combinations) + "] Four of a kind (" + to_string(roll[1]) + "'s) : 1000 points\n");

						//Resize array to add new combination
						ResizeIntArray(selection, (combinations + 1) * 3);
						selection[combinations * 3] = combinations;						//Binding
						selection[combinations * 3 + 1] = DiceComboCodes::FourofKindT3;	//Code
						selection[combinations * 3 + 2] = 1;							//Index

						combinations++;
					}
#pragma endregion

#pragma endregion

#pragma region 3 dice rolled
				case 3:
#pragma region 3 of a kind
					//Check for three of a kind
					for (int i = 5; i >= diceScored; i--) {
						if (roll[i] == 0) continue;

						if (roll[i] == roll[i - 1] && roll[i] == roll[i - 2]) {
							i -= 2;

							//If dice face is a 1
							if (roll[i] == 1) {
								output.append("[" + to_string(combinations) + "] Three of a kind (" + to_string(roll[i]) + "'s) : 300 points\n");
							}
							//Any other face
							else {
								output.append("[" + to_string(combinations) + "] Three of a kind (" + to_string(roll[i]) + "'s) : " + to_string(roll[i] * 100) + " points\n");
							}

							//Resize array to add new combination
							ResizeIntArray(selection, (combinations + 1) * 3);
							selection[combinations * 3] = combinations;						//Binding
							selection[combinations * 3 + 1] = DiceComboCodes::ThreeofKind;	//Code
							selection[combinations * 3 + 2] = i;							//Index

							combinations++;
						}
					}
#pragma endregion

#pragma endregion

#pragma region 2 dice rolled
			case 2:
#pragma endregion

#pragma region 1 dice rolled
			case 1:
#pragma region Singles
				//Check for single 1's and 5's
				for (int i = diceScored; i < MAX_DICE; i++) {
					//Skip if dice is stored
					if (roll[i] == 0) continue;

					//If dice face is a 1
					if (roll[i] == 1) {
						for (int combo = combinations; combo >= 0 ; combo--) {
							//If code is already in selection, skip
							if (selection[combinations * 3 - 2] == DiceComboCodes::SingleOne) {
								break;
							}

							output.append("[" + to_string(combinations) + "] One of a kind (" + to_string(roll[i]) + ") : 100 points\n");

							//Resize array to add new combination
							ResizeIntArray(selection, (combinations + 1) * 3);
							selection[combinations * 3] = combinations;					//Binding
							selection[combinations * 3 + 1] = DiceComboCodes::SingleOne;//Code
							selection[combinations * 3 + 2] = i;						//Index

							combinations++;
						}
					}
					//If dice face is a 5
					else if (roll[i] == 5) {
						for (int combo = combinations; combo >= 0; combo--) {
							//If code is already in selection, skip
							if (selection[combinations * 3 - 2] == DiceComboCodes::SingleFive) {
								break;
							}

							output.append("[" + to_string(combinations) + "] One of a kind (" + to_string(roll[i]) + ") : 50 points\n");

							//Resize array to add new combination
							ResizeIntArray(selection, (combinations + 1) * 3);
							selection[combinations * 3] = combinations;					//Binding
							selection[combinations * 3 + 1] = DiceComboCodes::SingleFive;//Code
							selection[combinations * 3 + 2] = i;						//Index

							combinations++;
						}
					}
				}
#pragma endregion

#pragma endregion

			case 0:
			default:
				break;
			}

			//If no points and point dice, FARKLE
			if (combinations == 0 && pointsScored == 0) {
				PrintWithColor("\nThere are no point dice... you have FARKLED!\n", Colors::red, Colors::black);
				break;
			}



			PrintWithColor("Here are the combinations of point dice:\n\n", Colors::cyan, Colors::black);
			PrintWithColor(output, Colors::turquoise, Colors::black);

			//If points have been scored
			if (pointsScored > 0) {
				//add option to reroll dice
				PrintWithColor("[" + to_string(combinations) + "] Reroll Dice\n", Colors::brown, Colors::black);

				ResizeIntArray(selection, (combinations + 1) * 3);
				selection[combinations * 3] = combinations;					//Binding
				selection[combinations * 3 + 1] = DiceComboCodes::Reroll;	//Code
				selection[combinations * 3 + 2] = -1;						//Index

				combinations++;

				//add option to stop scoring
				PrintWithColor("[" + to_string(combinations) + "] Stop Scoring\n", Colors::brown, Colors::black);

				ResizeIntArray(selection, (combinations + 1) * 3);
				selection[combinations * 3] = combinations;				//Binding
				selection[combinations * 3 + 1] = DiceComboCodes::Stop;	//Code
				selection[combinations * 3 + 2] = -1;					//Index

				combinations++;
			}

			//Get valid input
			do {
				//Get choice for what dice combination to select
				PrintWithColor("\nType the number between the brackets to score the dice : ", Colors::yellow, Colors::black);
				cin >> input;

				//If input is not an integer
				if (!cin) {
					PrintWithColor("Invalid Input!\n", Colors::red, Colors::black);

					cin.clear();	//Clear input
					cin.ignore();	//Ignore last input
					
					input = -1;
					continue;
				}
			} while (input == -1);

			int index = selection[input * 3 + 2];
			
			switch (selection[input * 3 + 1]) {
			//Roll dice again
			case DiceComboCodes::Reroll:
				currentScore += pointsScored;

				PrintWithColor("You got " + to_string(pointsScored) + " points this roll.\n" +
					"You now have " + to_string(currentScore) + " points to cash.\n\n", Colors::green, Colors::black);

				RollDice();
				return;
			// stop scoring
			case DiceComboCodes::Stop:
				input = -2;
				break;
			// singles
			case DiceComboCodes::SingleFive:
			case DiceComboCodes::SingleOne:
				savedRoll[diceScored] = roll[index];

				if (roll[index] == 1)
					pointsScored += 100;
				else if (roll[index] == 5)
					pointsScored += 50;
				
				roll[index] = 0;
				diceScored++;
				diceToScore--;
				break;
			// 3 of a kind
			case DiceComboCodes::ThreeofKind:
				for (int i = index; i < index + 3; i++)
				{
					if (roll[index] == 1) {
						pointsScored += 300;
					}
					else {
						pointsScored += roll[index] * 100;
					}
					
					savedRoll[diceScored] = roll[i];
					diceScored++;
					diceToScore--;
					roll[i] = 0;
				}

				break;
			// 4 of a kind (2)
			// 4 of a kind (2)
			// 4 of a kind (3)
			case DiceComboCodes::FourofKindT1:
			case DiceComboCodes::FourofKindT2:
			case DiceComboCodes::FourofKindT3:
				for (int i = index; i <= index + 3; i++) {	
					savedRoll[diceScored] = roll[i];
					diceScored++;
					diceToScore--;
					roll[i] = 0;
				}

				pointsScored += 1000;

				break;
			// 5 of a kind (2)
			// 5 of a kind (1)
			case DiceComboCodes::FiveofKindT1:
			case DiceComboCodes::FiveofKindT2:

				for (int i = index; i <= index + 4; i++) {
					savedRoll[diceScored] = roll[i];
					diceScored++;
					diceToScore--;
					roll[i] = 0;
				}

				pointsScored += 2000;
				break;
			// 1-6 straight
			// 3 sets of 2
			// 4 sets + 2 (2)
			// 4 sets + 2 (1)
			case DiceComboCodes::Straight:
			case DiceComboCodes::ThreesetsTwo:
			case DiceComboCodes::FoursetsTwoT1:
			case DiceComboCodes::FoursetsTwoT2:
				
				for (int i = 0; i < MAX_DICE; i++) {
					savedRoll[diceScored] = roll[i];
					diceScored++;
					diceToScore--;
					roll[i] = 0;
				}

				pointsScored += 1500;
				break;

			// 2 sets of 3
			case DiceComboCodes::TwosetsThree:

				for (int i = 0; i < MAX_DICE; i++) {
					savedRoll[diceScored] = roll[i];
					diceScored++;
					diceToScore--;
					roll[i] = 0;
				}

				pointsScored += 2500;
				break;

			// 6 of kind
			case DiceComboCodes::SixofKind:

				for (int i = 0; i < MAX_DICE; i++) {
					savedRoll[diceScored] = roll[i];
					diceScored++;
					diceToScore--;
					roll[i] = 0;
				}

				pointsScored += 3000;
				break;

			default:
				continue;
			}

		} while (combinations > 0 && input != -2);

		currentScore += pointsScored;

		//If the player scored points this roll
		if (pointsScored > 0) {
			PrintWithColor("You got " + to_string(pointsScored) + " points this roll.\n" + 
							"You now have " + to_string(currentScore) + " points to cash.\n\n", Colors::green, Colors::black);
		}
		else {
			PrintWithColor(to_string(currentScore) + " points lost...\n" + 
							"Your turn ends here...\n\n", Colors::red, Colors::black);
			NextTurn();
		}
	}
#pragma endregion

#pragma region Turn
	//Set the turn to the next player in the list
	void GameInfo::NextTurn() const {
		currentTurn++;

		if (currentTurn >= numOfPlayers)
			currentTurn = 0;

		ResetDice();
	}

	//Returns the current turn
	int GameInfo::GetTurn() const {
		return currentTurn;
	}

#pragma endregion

#pragma region Helper
	//Used by the scoreboard to determine who has the higher score
	bool GameInfo::ScoreComparer(Player& playerOne, Player& playerTwo) {
		return playerOne.GetScore() > playerTwo.GetScore();
	}

	//Resize the player array for when players are added or removed from the game
	void GameInfo::ResizePlayerArray(Player*& orig, int size) {
		Player* resized = new Player[size * 2];	//make new temp dynamic array

		for (int i = 0; i < size; i++)
			resized[i] = orig[i];				//copy element from original to new
		delete[] orig;							//free memory from original array
		orig = resized;							//set original array to new array
	}

	//https://stackoverflow.com/questions/8056746/copying-from-one-dynamically-allocated-array-to-another-c
	void GameInfo::ResizeIntArray(int*& orig, int size) {
		int* resized = new int[size];	//make new temp dynamic array

		copy(orig, orig + size, resized); //copy element from original to new
			
		delete[] orig;							//free memory from original array
		orig = resized;							//set original array to new array
	}

	//https://www.codespeedy.com/color-text-output-in-console-in-cpp/#:~:text=In%20this%20article%2C%20we%20will%20discuss%20how%20we,output%20console.%20Handle%20var_name%20%3D%20GetStdHandle%28STD_OUTPUT_HANDLE%29%3B%20SetConsoleTextAttribute%28var_name%2C%20color_code%29%3B
	//Takes in a string and a foreground and background color to print to the console
	void GameInfo::PrintWithColor(string text, int foregroundColor, int backgroundColor) const {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
		//set to custom color
		SetConsoleTextAttribute(hConsole, foregroundColor + backgroundColor * 16);
		cout << text;

		//Reset to white
		SetConsoleTextAttribute(hConsole, 15);
	}

#pragma endregion