/*
Name		: Nathan Hallam
Course		: IT-132
Date		: 7th April, 2024
Project NO	: 5-2
File Name	: Player.h
Description : Header file defining attributes for the player that can be set and accessed for the game.
Additions	:
		   1: Added m_console private variable
		   2: Added public constant setter function for variable m_console
		   3: Added public constant getter function for variable m_console
*/

#pragma once

#include <string>
#include "ConsoleTypes.h"

class Player
{
private:
	std::string m_name;
	ConsoleTypes m_console = ConsoleTypes::None;

public:
	Player()
	{
	}

	void SetName(const std::string& name)
	{
		m_name = name;
	}

	const std::string& GetName() const
	{
		return m_name;
	}

	void SetPreferredConsole(const ConsoleTypes console) {
		m_console = console;
	}

	const ConsoleTypes GetPreferredConsole() const {
		return m_console;
	}

	const std::string GetPreferredConsoleAsString() const {
		return ConsoleTypesToString(m_console);
	}
};