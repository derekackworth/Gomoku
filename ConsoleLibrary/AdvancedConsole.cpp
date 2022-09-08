/*
	Author: Derek Ackworth
	Date: April 18th, 2019
	File: AdvancedConsole.cpp
	Purpose: AdvancedConsole class implementation
*/

#include <stdexcept>
#include "AdvancedConsole.hpp"
#include "ConsoleError.hpp"

// ConsoleError exception throw helper macro
#define THROW_IF_CONSOLE_ERROR(result) if(!result) throw ConsoleError(__LINE__,__FILE__)

AdvancedConsole* AdvancedConsole::singletonPtr_ = nullptr;

/*
	Singleton initialization and confirmation
	Throw an exception if multiple instances are created
*/
AdvancedConsole::AdvancedConsole() : currentBufferCoord_(), currentCCI_(), currentCSBI_(), currentHeight_(), currentMode_(), currentWidth_(),
	hInput_(), hOutput_(), originalBufferCoord_(), originalCCI_(), originalCSBI_(), originalMode_()
{
	if (singletonPtr_)
	{
		throw "Error: AdvancedConsole already initialized!";
	}

	singletonPtr_ = this;
}

// Save the title
void AdvancedConsole::saveTitle()
{
	originalTitle_.resize(size_t(GetConsoleTitleA(originalTitle_.data(), (DWORD)originalTitle_.size())) + 1);
	originalTitle_.shrink_to_fit();
}

// Save the screen buffer info
void AdvancedConsole::saveScreenBufferInfo()
{
	THROW_IF_CONSOLE_ERROR(GetConsoleScreenBufferInfo(hOutput_, &originalCSBI_));
}

// Save the cursor info
void AdvancedConsole::saveCursorInfo()
{
	THROW_IF_CONSOLE_ERROR(GetConsoleCursorInfo(hOutput_, &originalCCI_));
}

// Save the desktop
void AdvancedConsole::saveDesktop()
{
	originalBuffer_.resize(size_t(originalCSBI_.dwSize.X) * originalCSBI_.dwSize.Y);
	originalBufferCoord_ = { 0 };
	SMALL_RECT sr = { 0 };
	sr.Right = originalCSBI_.dwSize.X - 1;
	sr.Bottom = originalCSBI_.dwSize.Y - 1;
	THROW_IF_CONSOLE_ERROR(ReadConsoleOutputA(hOutput_, originalBuffer_.data(), originalCSBI_.dwSize, originalBufferCoord_, &sr));
}

// Save the mode
void AdvancedConsole::saveMode()
{
	THROW_IF_CONSOLE_ERROR(GetConsoleMode(hInput_, &originalMode_));
}

// Restore to the saved title
void AdvancedConsole::restoreTitle()
{
	THROW_IF_CONSOLE_ERROR(SetConsoleTitleA(originalTitle_.data()));
}

// Restore to the saved screen buffer info
void AdvancedConsole::restoreScreenBufferInfo()
{
	SMALL_RECT sr = { 0 };
	THROW_IF_CONSOLE_ERROR(SetConsoleWindowInfo(hOutput_, true, &sr));
	THROW_IF_CONSOLE_ERROR(SetConsoleScreenBufferSize(hOutput_, originalCSBI_.dwSize));
	THROW_IF_CONSOLE_ERROR(SetConsoleWindowInfo(hOutput_, true, &originalCSBI_.srWindow));
}

// Restore to the saved cursor info
void AdvancedConsole::restoreCursorInfo()
{
	THROW_IF_CONSOLE_ERROR(SetConsoleCursorInfo(hOutput_, &originalCCI_));
	THROW_IF_CONSOLE_ERROR(SetConsoleCursorPosition(hOutput_, originalCSBI_.dwCursorPosition));
}

// Restore to the saved desktop
void AdvancedConsole::restoreDesktop()
{
	SMALL_RECT sr = { 0 };
	sr.Right = originalCSBI_.dwSize.X - 1;
	sr.Bottom = originalCSBI_.dwSize.Y - 1;
	THROW_IF_CONSOLE_ERROR(WriteConsoleOutputA(hOutput_, originalBuffer_.data(), originalCSBI_.dwSize, originalBufferCoord_, &sr));
}

// Restore to the saved mode
void AdvancedConsole::restoreMode()
{
	THROW_IF_CONSOLE_ERROR(SetConsoleMode(hInput_, originalMode_));
}

// Set the input and output
void AdvancedConsole::setInputOutput()
{
	hInput_ = GetStdHandle(STD_INPUT_HANDLE);
	hOutput_ = GetStdHandle(STD_OUTPUT_HANDLE);
}

/*
	Set the title
	Input: Title
*/
void AdvancedConsole::setTitle(string title)
{
	currentTitle_ = title;
	THROW_IF_CONSOLE_ERROR(SetConsoleTitleA(currentTitle_.c_str()));
}

/*
	Set the window info
	Input: Width and height
*/
void AdvancedConsole::setWindowInfo(int width, int height)
{
	currentWidth_ = width;
	currentHeight_ = height;
	SMALL_RECT sr = { 0 };
	sr.Top = sr.Left = 0;
	currentWidth_ = min(currentWidth_, currentCSBI_.dwMaximumWindowSize.X);
	currentHeight_ = min(currentHeight_, currentCSBI_.dwMaximumWindowSize.Y);
	sr.Right = currentWidth_ - 1;
	sr.Bottom = currentHeight_ - 1;
	THROW_IF_CONSOLE_ERROR(SetConsoleWindowInfo(hOutput_, TRUE, &sr));
}

// Set the screen buffer info
void AdvancedConsole::setScreenBufferInfo()
{
	THROW_IF_CONSOLE_ERROR(GetConsoleScreenBufferInfo(hOutput_, &currentCSBI_));
}

/*
	Set the screen buffer size
	Input: Width and height
*/
void AdvancedConsole::setScreenBufferSize(int width, int height)
{
	currentBufferCoord_.X = width;
	currentBufferCoord_.Y = height;
	THROW_IF_CONSOLE_ERROR(SetConsoleScreenBufferSize(hOutput_, currentBufferCoord_));
}

/*
	Set the cursor info
	Input: Percentage of the cell filled by the cursor and whether the cursor should be visible
*/
void AdvancedConsole::setCursorInfo(DWORD percentage, bool isVisible)
{
	if (percentage <= 0)
	{
		percentage = 1;
	}
	else if (percentage > 100)
	{
		percentage = 100;
	}

	currentCCI_ = { percentage, isVisible };
	THROW_IF_CONSOLE_ERROR(SetConsoleCursorInfo(hOutput_, &currentCCI_));
}

/*
	Set the cursor position
	Input: Positon of the cursor
*/
void AdvancedConsole::setCursorPosition(COORD position)
{
	THROW_IF_CONSOLE_ERROR(SetConsoleCursorPosition(hOutput_, position));
}

// Set the mode
void AdvancedConsole::setMode()
{
	currentMode_ = ENABLE_WINDOW_INPUT | ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS;
	THROW_IF_CONSOLE_ERROR(SetConsoleMode(hInput_, currentMode_));
}

/*
	Write a string in the console
	Input: String and the first cell to start on
*/
void AdvancedConsole::writeWithString(string str, COORD firstCell)
{
	DWORD charsWritten;
	THROW_IF_CONSOLE_ERROR(WriteConsoleOutputCharacterA(hOutput_, str.c_str(), (DWORD)str.size(), firstCell, &charsWritten));
}

/*
	Write attributes in the console
	Input: attributes and the first cell to start on
*/
void AdvancedConsole::writeWithAttributes(vector<WORD> attributes, COORD firstCell)
{
	DWORD attributesWritten;
	THROW_IF_CONSOLE_ERROR(WriteConsoleOutputAttribute(hOutput_, attributes.data(), (DWORD)attributes.size(), firstCell, &attributesWritten));
}

/*
	Fill the console with a character
	Input: Character, length of the fill and the first cell to start on
*/
void AdvancedConsole::fillWithChar(CHAR ch, DWORD length, COORD firstCell)
{
	DWORD charsWritten;
	THROW_IF_CONSOLE_ERROR(FillConsoleOutputCharacterA(hOutput_, ch, length, firstCell, &charsWritten));
}

/*
	Fill the console with an attribute
	Input: Attribute, length of the fill, and the first cell to start on
*/
void AdvancedConsole::fillWithAttribute(WORD attribute, DWORD length, COORD firstCell)
{
	DWORD attributesWritten;
	THROW_IF_CONSOLE_ERROR(FillConsoleOutputAttribute(hOutput_, attribute, length, firstCell, &attributesWritten));
}

/*
	Install a ctrl handler
	Input: Ctrl handler function pointer
*/
BOOL AdvancedConsole::installCtrlHandler(BOOL(*ctrlHandler)(DWORD))
{
	return SetConsoleCtrlHandler((PHANDLER_ROUTINE)ctrlHandler, TRUE);
}

/*
	Read all input
	Input a input buffer and number of events
*/
BOOL AdvancedConsole::readInput(vector<INPUT_RECORD>& inputBuffer, DWORD& numberOfEvents)
{
	return ReadConsoleInputW(hInput_, inputBuffer.data(), (DWORD)inputBuffer.size(), &numberOfEvents);
}
