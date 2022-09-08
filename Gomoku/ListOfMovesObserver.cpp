/*
	Author: Derek Ackworth
	Date: April 18th, 2019
	File: ListOfMovesObserver.cpp
	Purpose: ListOfMovesObserver class implementation
*/

#include "ListOfMovesObserver.hpp"

// Update observer
void ListOfMovesObserver::update() const
{
	// Fill with initial information
	if (gs_.currentPlayer == 0)
	{
		for (SHORT i = gs_.LIST_OF_MOVES_START.Y; i < gs_.LIST_OF_MOVES_HEIGHT + gs_.LIST_OF_MOVES_START.Y; i++)
		{
			gs_.fillWithChar(' ', gs_.LIST_OF_MOVES_WIDTH, { gs_.LIST_OF_MOVES_START.X, i });
			gs_.fillWithAttribute(gs_.BACKGROUND_GREY, gs_.LIST_OF_MOVES_WIDTH, { gs_.LIST_OF_MOVES_START.X, i });
		}

		gs_.writeWithString("List of Moves:", { gs_.LIST_OF_MOVES_START.X + (gs_.LIST_OF_MOVES_WIDTH / 2) - 7, gs_.LIST_OF_MOVES_START.Y });
	}
	// Paint the list of moves
	else
	{
		for (SHORT i = 2; i < 28; i++)
		{
			gs_.fillWithChar(' ', 4,
				{ gs_.LIST_OF_MOVES_START.X + (gs_.LIST_OF_MOVES_WIDTH / 2) - 2, gs_.LIST_OF_MOVES_START.Y + i });
		}

		for (SHORT i = max(0, (SHORT)gs_.listOfMoves.size() - 26); i < (int)gs_.listOfMoves.size(); i++)
		{
			if (i % 2 == 0)
			{
				if (gs_.player1Color == gs_.BACKGROUND_BLACK)
				{
					gs_.fillWithAttribute(gs_.BACKGROUND_GREY, 4,
						{ gs_.LIST_OF_MOVES_START.X + (gs_.LIST_OF_MOVES_WIDTH / 2) - 2,
						gs_.LIST_OF_MOVES_START.Y + 2 + i - max(0, (SHORT)gs_.listOfMoves.size() - 26) });
				}
				else if (gs_.player1Color == gs_.BACKGROUND_IRED)
				{
					gs_.fillWithAttribute(gs_.BACKGROUND_GREY + gs_.FOREGROUND_IRED, 4,
						{ gs_.LIST_OF_MOVES_START.X + (gs_.LIST_OF_MOVES_WIDTH / 2) - 2,
						gs_.LIST_OF_MOVES_START.Y + 2 + i - max(0, (SHORT)gs_.listOfMoves.size() - 26) });
				}
				else if (gs_.player1Color == gs_.BACKGROUND_IGREEN)
				{
					gs_.fillWithAttribute(gs_.BACKGROUND_GREY + gs_.FOREGROUND_IGREEN, 4,
						{ gs_.LIST_OF_MOVES_START.X + (gs_.LIST_OF_MOVES_WIDTH / 2) - 2,
						gs_.LIST_OF_MOVES_START.Y + 2 + i - max(0, (SHORT)gs_.listOfMoves.size() - 26) });
				}
				else if (gs_.player1Color == gs_.BACKGROUND_IBLUE)
				{
					gs_.fillWithAttribute(gs_.BACKGROUND_GREY + gs_.FOREGROUND_IBLUE, 4,
						{ gs_.LIST_OF_MOVES_START.X + (gs_.LIST_OF_MOVES_WIDTH / 2) - 2,
						gs_.LIST_OF_MOVES_START.Y + 2 + i - max(0, (SHORT)gs_.listOfMoves.size() - 26) });
				}
				else if (gs_.player1Color == gs_.BACKGROUND_ICYAN)
				{
					gs_.fillWithAttribute(gs_.BACKGROUND_GREY + gs_.FOREGROUND_ICYAN, 4,
						{ gs_.LIST_OF_MOVES_START.X + (gs_.LIST_OF_MOVES_WIDTH / 2) - 2,
						gs_.LIST_OF_MOVES_START.Y + 2 + i - max(0, (SHORT)gs_.listOfMoves.size() - 26) });
				}
				else if (gs_.player1Color == gs_.BACKGROUND_IMAGENTA)
				{
					gs_.fillWithAttribute(gs_.BACKGROUND_GREY + gs_.FOREGROUND_IMAGENTA, 4,
						{ gs_.LIST_OF_MOVES_START.X + (gs_.LIST_OF_MOVES_WIDTH / 2) - 2,
						gs_.LIST_OF_MOVES_START.Y + 2 + i - max(0, (SHORT)gs_.listOfMoves.size() - 26) });
				}
				else if (gs_.player1Color == gs_.BACKGROUND_IYELLOW)
				{
					gs_.fillWithAttribute(gs_.BACKGROUND_GREY + gs_.FOREGROUND_IYELLOW, 4,
						{ gs_.LIST_OF_MOVES_START.X + (gs_.LIST_OF_MOVES_WIDTH / 2) - 2,
						gs_.LIST_OF_MOVES_START.Y + 2 + i - max(0, (SHORT)gs_.listOfMoves.size() - 26) });
				}
			}
			else
			{
				if (gs_.player2Color == gs_.BACKGROUND_BLACK)
				{
					gs_.fillWithAttribute(gs_.BACKGROUND_GREY, 4,
						{ gs_.LIST_OF_MOVES_START.X + (gs_.LIST_OF_MOVES_WIDTH / 2) - 2,
						gs_.LIST_OF_MOVES_START.Y + 2 + i - max(0, (SHORT)gs_.listOfMoves.size() - 26) });
				}
				else if (gs_.player2Color == gs_.BACKGROUND_IRED)
				{
					gs_.fillWithAttribute(gs_.BACKGROUND_GREY + gs_.FOREGROUND_IRED, 4,
						{ gs_.LIST_OF_MOVES_START.X + (gs_.LIST_OF_MOVES_WIDTH / 2) - 2,
						gs_.LIST_OF_MOVES_START.Y + 2 + i - max(0, (SHORT)gs_.listOfMoves.size() - 26) });
				}
				else if (gs_.player2Color == gs_.BACKGROUND_IGREEN)
				{
					gs_.fillWithAttribute(gs_.BACKGROUND_GREY + gs_.FOREGROUND_IGREEN, 4,
						{ gs_.LIST_OF_MOVES_START.X + (gs_.LIST_OF_MOVES_WIDTH / 2) - 2,
						gs_.LIST_OF_MOVES_START.Y + 2 + i - max(0, (SHORT)gs_.listOfMoves.size() - 26) });
				}
				else if (gs_.player2Color == gs_.BACKGROUND_IBLUE)
				{
					gs_.fillWithAttribute(gs_.BACKGROUND_GREY + gs_.FOREGROUND_IBLUE, 4,
						{ gs_.LIST_OF_MOVES_START.X + (gs_.LIST_OF_MOVES_WIDTH / 2) - 2,
						gs_.LIST_OF_MOVES_START.Y + 2 + i - max(0, (SHORT)gs_.listOfMoves.size() - 26) });
				}
				else if (gs_.player2Color == gs_.BACKGROUND_ICYAN)
				{
					gs_.fillWithAttribute(gs_.BACKGROUND_GREY + gs_.FOREGROUND_ICYAN, 4,
						{ gs_.LIST_OF_MOVES_START.X + (gs_.LIST_OF_MOVES_WIDTH / 2) - 2,
						gs_.LIST_OF_MOVES_START.Y + 2 + i - max(0, (SHORT)gs_.listOfMoves.size() - 26) });
				}
				else if (gs_.player2Color == gs_.BACKGROUND_IMAGENTA)
				{
					gs_.fillWithAttribute(gs_.BACKGROUND_GREY + gs_.FOREGROUND_IMAGENTA, 4,
						{ gs_.LIST_OF_MOVES_START.X + (gs_.LIST_OF_MOVES_WIDTH / 2) - 2,
						gs_.LIST_OF_MOVES_START.Y + 2 + i - max(0, (SHORT)gs_.listOfMoves.size() - 26) });
				}
				else if (gs_.player2Color == gs_.BACKGROUND_IYELLOW)
				{
					gs_.fillWithAttribute(gs_.BACKGROUND_GREY + gs_.FOREGROUND_IYELLOW, 4,
						{ gs_.LIST_OF_MOVES_START.X + (gs_.LIST_OF_MOVES_WIDTH / 2) - 2,
						gs_.LIST_OF_MOVES_START.Y + 2 + i - max(0, (SHORT)gs_.listOfMoves.size() - 26) });
				}
			}

			gs_.writeWithString(gs_.listOfMoves[i],
				{ gs_.LIST_OF_MOVES_START.X + (gs_.LIST_OF_MOVES_WIDTH / 2) - 2,
				gs_.LIST_OF_MOVES_START.Y + 2 + i - max(0, (SHORT)gs_.listOfMoves.size() - 26) });
		}
	}
}
