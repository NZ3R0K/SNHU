/*
Name		: Nathan Hallam
Course		: IT-132
Date		: 21st April, 2024
Project NO	: 7.1
File Name	: FarkleCore.h
Description : Header file containing the declarations for the functions in FarkleCore.cpp
*/

#pragma once

#include "Player.h";

using namespace std;


class FarkleCore
{
private:
	void PrintCommands() const;
	void PrintTurnInfo() const;
	void GetInput(string& input) const;
	void CalculateInput(string command) const;
	int CalculateEndGameInput(string input) const;
	void PrintScoreboard() const;
	void CashScore() const;
	void WaitForKey() const;
public:
	void CoreLoop();
};