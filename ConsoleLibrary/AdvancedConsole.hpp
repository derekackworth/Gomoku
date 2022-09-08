/*
	Author: Derek Ackworth
	Date: April 18th, 2019
	File: AdvancedConsole.hpp
	Purpose: AdvancedConsole class declaration
*/

#pragma once

#include <Windows.h>
#include <string>
#include <vector>

using namespace std;

class AdvancedConsole
{
public:
	AdvancedConsole();

	virtual int execute() = 0;

	void saveTitle();
	void saveScreenBufferInfo();
	void saveCursorInfo();
	void saveDesktop();
	void saveMode();

	void restoreTitle();
	void restoreScreenBufferInfo();
	void restoreCursorInfo();
	void restoreDesktop();
	void restoreMode();

	void setInputOutput();
	void setTitle(string title);
	void setWindowInfo(int width, int height);
	void setScreenBufferInfo();
	void setScreenBufferSize(int width, int height);
	void setCursorInfo(DWORD percentage, bool isVisible);
	void setCursorPosition(COORD position);
	void setMode();

	void writeWithString(string str, COORD firstCell);
	void writeWithAttributes(vector<WORD> attr, COORD firstCell);
	void fillWithChar(CHAR ch, DWORD length, COORD firstCell);
	void fillWithAttribute(WORD attr, DWORD length, COORD firstCell);

	BOOL installCtrlHandler(BOOL(*ctrlHandler)(DWORD));
	BOOL readInput(vector<INPUT_RECORD>& inputBuffer, DWORD& numberOfEvents);

	static WORD constexpr BACKGROUND_BLACK = 0;
	static WORD constexpr BACKGROUND_GREY = 128;
	static WORD constexpr BACKGROUND_IWHITE = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
	static WORD constexpr BACKGROUND_IRED = BACKGROUND_RED | BACKGROUND_INTENSITY;
	static WORD constexpr BACKGROUND_IGREEN = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
	static WORD constexpr BACKGROUND_IBLUE = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
	static WORD constexpr BACKGROUND_ICYAN = BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
	static WORD constexpr BACKGROUND_IMAGENTA = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
	static WORD constexpr BACKGROUND_IYELLOW = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
	static WORD constexpr FOREGROUND_IRED = FOREGROUND_RED | FOREGROUND_INTENSITY;
	static WORD constexpr FOREGROUND_IGREEN = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	static WORD constexpr FOREGROUND_IBLUE = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	static WORD constexpr FOREGROUND_ICYAN = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	static WORD constexpr FOREGROUND_IMAGENTA = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	static WORD constexpr FOREGROUND_IYELLOW = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;

private:
	vector<char> originalTitle_;
	CONSOLE_SCREEN_BUFFER_INFO originalCSBI_;
	CONSOLE_CURSOR_INFO originalCCI_;
	vector<CHAR_INFO> originalBuffer_;
	COORD originalBufferCoord_;
	DWORD originalMode_;

	HANDLE hInput_;
	HANDLE hOutput_;

	string currentTitle_;
	CONSOLE_SCREEN_BUFFER_INFO currentCSBI_;
	CONSOLE_CURSOR_INFO currentCCI_;
	COORD currentBufferCoord_;
	DWORD currentMode_;
	SHORT currentWidth_;
	SHORT currentHeight_;

	static AdvancedConsole* singletonPtr_;
};
