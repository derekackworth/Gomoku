/*
	Author: Derek Ackworth
	Date: April 18th, 2019
	File: Console.hpp
	Purpose: Console class declaration
*/

#pragma once

#include <string>
#include "AdvancedConsole.hpp"

using namespace std;

class Console : public AdvancedConsole
{
public:
	void save();
	void restore();
	void create(string title);
	void setSize(int width, int height);
};
