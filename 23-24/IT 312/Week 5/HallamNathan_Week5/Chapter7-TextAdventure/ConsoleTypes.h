/*
Name		: Nathan Hallam
Course		: IT-132
Date		: 7th April, 2024
Project NO	: 5-2
File Name	: ConsoleTypes.h
Description : Header file defining the various options that can be selected determining what kind of console will be used.
*/

#pragma once
#include <stdexcept>    //Used by ConsoleTypesToString()

enum class ConsoleTypes
{
	None,
	Standard,
	Colorized,
	Custom,
	IDE,
	Web,
	Emulated
};

//https://belaycpp.com/2021/08/24/best-ways-to-convert-an-enum-to-a-string/
constexpr const char* ConsoleTypesToString(ConsoleTypes console) throw()
{
    switch (console)
    {
    case ConsoleTypes::None: return "None";
    case ConsoleTypes::Standard: return "Standard";
    case ConsoleTypes::Colorized: return "Colorized";
    case ConsoleTypes::Custom: return "Custom";
    case ConsoleTypes::IDE: return "IDE";
    case ConsoleTypes::Web: return "Web";
    case ConsoleTypes::Emulated: return "Emulated";
    default: throw std::invalid_argument("Unimplemented item");
    }
}