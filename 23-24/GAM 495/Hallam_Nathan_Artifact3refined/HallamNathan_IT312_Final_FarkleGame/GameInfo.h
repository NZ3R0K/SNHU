/*
Name		: Nathan Hallam
Course		: IT-132
Date		: 21st April, 2024
Project NO	: 7.1
File Name	: GameInfo.h
Description : Header file containing the declarations for the functions in Game.cpp
*/

#pragma once

#include "Player.h"

class GameInfo {
public:
#pragma region Functions
#pragma region Scoreboard
	void UpdateScoreboard() const;
	int* GetScoreboard() const;
	int GetCurrentScore() const;
#pragma endregion

#pragma region Players
	int GetPlayerCount() const;

	Player* GetPlayers();
	Player& GetPlayer(int arrayPosition);
	Player& GetCurrentPlayer();

	void AddPlayer(string playerName, int score, int scoreboardPos);
	void RemovePlayer(int arrayPosition) const;
	void ClearPlayers() const;
#pragma endregion
	
#pragma region Game
	void Initialize();
	void Reset() const;
	void PrintRules();
	bool SaveGame();
	void LoadSave();
	bool CheckForWinner();
#pragma endregion

#pragma region Turn
	void NextTurn() const;
	int GetTurn() const;
#pragma endregion

#pragma region Dice
	int GetUnrolledDiceCount() const;
	void ResetDice() const;
	void RollDice();
	void ScoreDice(int* roll, int diceToScore);
#pragma endregion

#pragma region Helper
	static bool ScoreComparer(Player& playerOne, Player& playerTwo);

	void ResizePlayerArray(Player*& orig, int size);
	void ResizeIntArray(int*& orig, int size);
	void PrintWithColor(string text, int foregroundColor, int backgroundColor) const;
#pragma endregion
#pragma endregion
};