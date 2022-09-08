/*
	Author: Derek Ackworth
	Date: April 18th, 2019
	File: ConsoleError.cpp
	Purpose: ConsoleError class implementation
*/

#include <sstream>
#include "ConsoleError.hpp"

/*
	Get an error message
	Output: Error message
*/
string ConsoleError::message()
{
	ostringstream oss;
	oss << "Error code: " << errorCode() << "\n";
	oss << "Error description" << description() << "\n";
	oss << "In file: " << fileName() << "\n";
	oss << "On line: " << lineNumber() << "\n";
	return oss.str();
}

/*
	Get an error description
	Input: Error code
	Output: Error description
*/
string ConsoleError::description()
{
	string description;
	DWORD count = FormatMessageA(
		/* flags */			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS |
							FORMAT_MESSAGE_MAX_WIDTH_MASK,
		/* source*/			NULL,
		/* message ID */	errorCode_,
		/* language */		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		/* buffer */		(LPSTR)&description,
		/* size */			0,
		/* args */			NULL
	);
	description = (count == 0) ? "Unknown" : description;
	return description;
}
