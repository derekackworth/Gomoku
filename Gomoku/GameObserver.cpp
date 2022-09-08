/*
	Author: Derek Ackworth
	Date: April 18th, 2019
	File: GameObserver.cpp
	Purpose: GameObserver class implementation
*/

#include "GameObserver.hpp"

// Update observer
void GameObserver::update() const
{
	// Clear board when no moves
	if (gs_.listOfMoves.size() == 0)
	{
		for (SHORT i = gs_.GAME_START.Y; i < gs_.GAME_HEIGHT + gs_.GAME_START.Y; i++)
		{
			gs_.fillWithChar(' ', gs_.GAME_WIDTH, { gs_.GAME_START.X, i });

			if ((i - gs_.GAME_START.Y) % 2 == 0)
			{
				gs_.fillWithChar('-', gs_.GAME_WIDTH - 2, { gs_.GAME_START.X + 1, i });
			}

			gs_.fillWithAttribute(gs_.BACKGROUND_IWHITE, gs_.GAME_WIDTH, { gs_.GAME_START.X, i });

			for (SHORT j = gs_.GAME_START.X + 1; j < gs_.GAME_WIDTH + gs_.GAME_START.X - 1; j += 5)
			{
				gs_.writeWithString("|", { j, i });
			}
		}
	}
	// Paint board tiles
	else
	{
		for (SHORT i = 0; i < 15; i++)
		{
			for (SHORT j = 0; j < 15; j++)
			{
				if (gs_.gameBoardGrid[i][j] == 1)
				{
					gs_.fillWithChar(' ', 2, { gs_.GAME_START.X + (j * 5) + 1, gs_.GAME_START.Y + (i * 2) });
					gs_.fillWithAttribute(gs_.player1Color, 2, { gs_.GAME_START.X + (j * 5) + 1, gs_.GAME_START.Y + (i * 2) });
				}
				else if (gs_.gameBoardGrid[i][j] == 2)
				{
					gs_.fillWithChar(' ', 2, { gs_.GAME_START.X + (j * 5) + 1, gs_.GAME_START.Y + (i * 2) });
					gs_.fillWithAttribute(gs_.player2Color, 2, { gs_.GAME_START.X + (j * 5) + 1, gs_.GAME_START.Y + (i * 2) });
				}
			}
		}
	}
}
