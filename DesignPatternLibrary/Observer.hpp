/*
	Author: Derek Ackworth
	Date: April 18th, 2019
	File: Observer.hpp
	Purpose: Observer class declaration
*/

#pragma once

class Observer
{
public:
	virtual void update() const = 0;
};
