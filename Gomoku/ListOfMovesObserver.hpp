/*
	Author: Derek Ackworth
	Date: April 18th, 2019
	File: ListOfMovesObserver.hpp
	Purpose: ListOfMovesObserver class declaration
*/

#pragma once

#include "GomokuSubject.hpp"

class ListOfMovesObserver : public Observer
{
public:
	ListOfMovesObserver(GomokuSubject& gs_) : gs_(gs_) {}

	void update() const override;

private:
	GomokuSubject& gs_;
};
