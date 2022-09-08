/*
	Author: Derek Ackworth
	Date: April 18th, 2019
	File: ScoreObserver.hpp
	Purpose: ScoreObserver class declaration
*/

#pragma once

#include "GomokuSubject.hpp"

class ScoreObserver : public Observer
{
public:
	ScoreObserver(GomokuSubject& gs_) : gs_(gs_) {}

	void update() const override;

private:
	GomokuSubject& gs_;
};
