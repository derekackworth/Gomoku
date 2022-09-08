/*
	Author: Derek Ackworth
	Date: April 18th, 2019
	File: PlayersObserver.hpp
	Purpose: PlayersObserver class declaration
*/

#pragma once

#include "GomokuSubject.hpp"

class PlayersObserver : public Observer
{
public:
	PlayersObserver(GomokuSubject& gs_) : gs_(gs_) {}

	void update() const override;

private:
	GomokuSubject& gs_;
};
