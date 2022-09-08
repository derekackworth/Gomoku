/*
	Author: Derek Ackworth
	Date: April 18th, 2019
	File: GameObserver.hpp
	Purpose: GameObserver class declaration
*/

#pragma once

#include "GomokuSubject.hpp"

class GameObserver : public Observer
{
public:
	GameObserver(GomokuSubject& gs_) : gs_(gs_) {}

	void update() const override;

private:
	GomokuSubject& gs_;
};
