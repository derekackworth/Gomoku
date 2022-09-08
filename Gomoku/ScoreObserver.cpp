/*
	Author: Derek Ackworth
	Date: April 18th, 2019
	File: ScoreObserver.cpp
	Purpose: ScoreObserver class implementation
*/

#include "ScoreObserver.hpp"

// Update observer
void ScoreObserver::update() const
{
	// Fill with initial information
	if (gs_.currentPlayer == 0)
	{
		for (SHORT i = gs_.SCORE_START.Y; i < gs_.SCORE_HEIGHT + gs_.SCORE_START.Y; i++)
		{
			gs_.fillWithChar(' ', gs_.SCORE_WIDTH, { gs_.SCORE_START.X, i });
			gs_.fillWithAttribute(gs_.BACKGROUND_GREY, gs_.SCORE_WIDTH, { gs_.SCORE_START.X, i });
		}

		gs_.writeWithString("# of Tiles:", { gs_.SCORE_START.X + 3, gs_.SCORE_START.Y });
		gs_.writeWithString(to_string(gs_.player1TileCount), { gs_.SCORE_START.X + 3, gs_.SCORE_START.Y + 2 });
		gs_.writeWithString(to_string(gs_.player2TileCount), { gs_.SCORE_START.X + 3, gs_.SCORE_START.Y + 4 });

		gs_.writeWithString("Longest Run:", { gs_.SCORE_START.X + 18, gs_.SCORE_START.Y });
		gs_.writeWithString(to_string(gs_.player1RunCount), { gs_.SCORE_START.X + 18, gs_.SCORE_START.Y + 2 });
		gs_.writeWithString(to_string(gs_.player2RunCount), { gs_.SCORE_START.X + 18, gs_.SCORE_START.Y + 4 });
	}
	// Paint player1 and player2's tile count, and run count
	else
	{
		gs_.fillWithChar(' ', 3, { gs_.SCORE_START.X + 3, gs_.SCORE_START.Y + 2 });
		gs_.writeWithString(to_string(gs_.player1TileCount), { gs_.SCORE_START.X + 3, gs_.SCORE_START.Y + 2 });
		gs_.fillWithChar(' ', 3, { gs_.SCORE_START.X + 3, gs_.SCORE_START.Y + 4 });
		gs_.writeWithString(to_string(gs_.player2TileCount), { gs_.SCORE_START.X + 3, gs_.SCORE_START.Y + 4 });

		gs_.fillWithChar(' ', 3, { gs_.SCORE_START.X + 18, gs_.SCORE_START.Y + 2 });
		gs_.writeWithString(to_string(gs_.player1RunCount), { gs_.SCORE_START.X + 18, gs_.SCORE_START.Y + 2 });
		gs_.fillWithChar(' ', 3, { gs_.SCORE_START.X + 18, gs_.SCORE_START.Y + 4 });
		gs_.writeWithString(to_string(gs_.player2RunCount), { gs_.SCORE_START.X + 18, gs_.SCORE_START.Y + 4 });
	}
}
