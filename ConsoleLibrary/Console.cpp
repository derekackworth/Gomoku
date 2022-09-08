/*
	Author: Derek Ackworth
	Date: April 18th, 2019
	File: Console.cpp
	Purpose: Console class implementation
*/

#include "Console.hpp"

// Save the console
void Console::save()
{
	saveTitle();
	setInputOutput();
	saveScreenBufferInfo();
	saveCursorInfo();
	saveDesktop();
	saveMode();
}

// Restore to the saved console
void Console::restore()
{
	restoreTitle();
	restoreScreenBufferInfo();
	restoreCursorInfo();
	restoreDesktop();
	restoreMode();
}

/*
	Create a console
	Input: Title
*/
void Console::create(string title)
{
	setTitle(title);
	setScreenBufferInfo();
}

/*
	Set the console size
	Input: Width and height
*/
void Console::setSize(int width, int height)
{
	setWindowInfo(1, 1);
	setScreenBufferSize(width, height);
	setWindowInfo(width, height);
	setMode();
}
