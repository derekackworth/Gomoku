/*
	Author: Derek Ackworth
	Date: April 18th, 2019
	File: Gomoku.cpp
	Purpose: Connect the subject to the observers and execute the subject
*/

#include "GomokuSubject.hpp"
#include "PlayersObserver.hpp"
#include "ScoreObserver.hpp"
#include "GameObserver.hpp"
#include "ListOfMovesObserver.hpp"

int main(int argc, char* argv[])
{
	// Connect the subject to the observers and execute the subject
	GomokuSubject gs;
	PlayersObserver po(gs);
	ScoreObserver so(gs);
	GameObserver go(gs);
	ListOfMovesObserver lo(gs);
	gs.attach(&po);
	gs.attach(&so);
	gs.attach(&go);
	gs.attach(&lo);
	gs.execute();
}
