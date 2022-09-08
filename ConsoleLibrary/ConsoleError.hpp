/*
	Author: Derek Ackworth
	Date: April 18th, 2019
	File: ConsoleError.hpp
	Purpose: ConsoleError class declaration
*/

#pragma once

#include <Windows.h>
#include <string>

using namespace std;

class ConsoleError
{
public:
	ConsoleError(int lineNumber_, char const* fileName_) : errorCode_(GetLastError()), lineNumber_(lineNumber_), fileName_(fileName_) {}

	DWORD errorCode() { return errorCode_; }
	int lineNumber() { return lineNumber_; }
	char const* fileName() { return fileName_; }
	string message();
	string description();

private:
	DWORD errorCode_;
	int	lineNumber_;
	char const* fileName_;
};
