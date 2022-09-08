/*
	Author: Derek Ackworth
	Date: April 18th, 2019
	File: PlayersObserver.cpp
	Purpose: PlayersObserver class implementation
*/

#include "PlayersObserver.hpp"

// Update observer
void PlayersObserver::update() const
{
	// Fill with initial information
	if (gs_.currentPlayer == 0)
	{
		for (SHORT i = gs_.PLAYERS_START.Y; i < gs_.PLAYERS_HEIGHT + gs_.PLAYERS_START.Y; i++)
		{
			gs_.fillWithChar(' ', gs_.PLAYERS_WIDTH, { gs_.PLAYERS_START.X, i });
			gs_.fillWithAttribute(gs_.BACKGROUND_GREY, gs_.PLAYERS_WIDTH, { gs_.PLAYERS_START.X, i });
		}

		gs_.writeWithString("Players:", { gs_.PLAYERS_START.X, gs_.PLAYERS_START.Y });
		gs_.writeWithString(gs_.player1Name, { gs_.PLAYERS_START.X, gs_.PLAYERS_START.Y + 2 });
		gs_.writeWithString(gs_.player2Name, { gs_.PLAYERS_START.X, gs_.PLAYERS_START.Y + 4 });

		gs_.writeWithString("Current Color:", { gs_.PLAYERS_START.X + 13, gs_.PLAYERS_START.Y });
		gs_.fillWithAttribute(gs_.player1Color, 2, { gs_.PLAYERS_START.X + 13, gs_.PLAYERS_START.Y + 2 });
		gs_.fillWithAttribute(gs_.player2Color, 2, { gs_.PLAYERS_START.X + 13, gs_.PLAYERS_START.Y + 4 });

		gs_.writeWithString("Change Color:", { gs_.PLAYERS_START.X + 32, gs_.PLAYERS_START.Y });
		gs_.fillWithAttribute(gs_.BACKGROUND_BLACK, 2, { gs_.PLAYERS_START.X + 32, gs_.PLAYERS_START.Y + 2 });
		gs_.fillWithAttribute(gs_.BACKGROUND_IRED, 2, { gs_.PLAYERS_START.X + 36, gs_.PLAYERS_START.Y + 2 });
		gs_.fillWithAttribute(gs_.BACKGROUND_IGREEN, 2, { gs_.PLAYERS_START.X + 40, gs_.PLAYERS_START.Y + 2 });
		gs_.fillWithAttribute(gs_.BACKGROUND_IBLUE, 2, { gs_.PLAYERS_START.X + 44, gs_.PLAYERS_START.Y + 2 });
		gs_.fillWithAttribute(gs_.BACKGROUND_ICYAN, 2, { gs_.PLAYERS_START.X + 48, gs_.PLAYERS_START.Y + 2 });
		gs_.fillWithAttribute(gs_.BACKGROUND_IMAGENTA, 2, { gs_.PLAYERS_START.X + 52, gs_.PLAYERS_START.Y + 2 });
		gs_.fillWithAttribute(gs_.BACKGROUND_IYELLOW, 2, { gs_.PLAYERS_START.X + 56, gs_.PLAYERS_START.Y + 2 });
		gs_.fillWithAttribute(gs_.BACKGROUND_BLACK, 2, { gs_.PLAYERS_START.X + 32, gs_.PLAYERS_START.Y + 4 });
		gs_.fillWithAttribute(gs_.BACKGROUND_IRED, 2, { gs_.PLAYERS_START.X + 36, gs_.PLAYERS_START.Y + 4 });
		gs_.fillWithAttribute(gs_.BACKGROUND_IGREEN, 2, { gs_.PLAYERS_START.X + 40, gs_.PLAYERS_START.Y + 4 });
		gs_.fillWithAttribute(gs_.BACKGROUND_IBLUE, 2, { gs_.PLAYERS_START.X + 44, gs_.PLAYERS_START.Y + 4 });
		gs_.fillWithAttribute(gs_.BACKGROUND_ICYAN, 2, { gs_.PLAYERS_START.X + 48, gs_.PLAYERS_START.Y + 4 });
		gs_.fillWithAttribute(gs_.BACKGROUND_IMAGENTA, 2, { gs_.PLAYERS_START.X + 52, gs_.PLAYERS_START.Y + 4 });
		gs_.fillWithAttribute(gs_.BACKGROUND_IYELLOW, 2, { gs_.PLAYERS_START.X + 56, gs_.PLAYERS_START.Y + 4 });

		gs_.writeWithString("Change Name:", { gs_.PLAYERS_START.X + 61, gs_.PLAYERS_START.Y });
		gs_.fillWithAttribute(gs_.BACKGROUND_IWHITE, 12, { gs_.PLAYERS_START.X + 61, gs_.PLAYERS_START.Y + 2 });
		gs_.fillWithAttribute(gs_.BACKGROUND_IWHITE, 12, { gs_.PLAYERS_START.X + 61, gs_.PLAYERS_START.Y + 4 });
	}

	/*
		Paint player1 and player2's name, color, and name change text
		Paint winner message if there's a winner
	*/
	else
	{
		gs_.fillWithChar(' ', 11, { gs_.PLAYERS_START.X, gs_.PLAYERS_START.Y + 2 });
		gs_.writeWithString(gs_.player1Name, { gs_.PLAYERS_START.X, gs_.PLAYERS_START.Y + 2 });
		gs_.fillWithChar(' ', 11, { gs_.PLAYERS_START.X, gs_.PLAYERS_START.Y + 4 });
		gs_.writeWithString(gs_.player2Name, { gs_.PLAYERS_START.X, gs_.PLAYERS_START.Y + 4 });

		gs_.fillWithAttribute(gs_.player1Color, 2, { gs_.PLAYERS_START.X + 13, gs_.PLAYERS_START.Y + 2 });
		gs_.fillWithAttribute(gs_.player2Color, 2, { gs_.PLAYERS_START.X + 13, gs_.PLAYERS_START.Y + 4 });

		gs_.fillWithChar(' ', 11, { gs_.PLAYERS_START.X + 61, gs_.PLAYERS_START.Y + 2 });
		gs_.writeWithString(gs_.player1NameChange, { gs_.PLAYERS_START.X + 61, gs_.PLAYERS_START.Y + 2 });
		gs_.fillWithChar(' ', 11, { gs_.PLAYERS_START.X + 61, gs_.PLAYERS_START.Y + 4 });
		gs_.writeWithString(gs_.player2NameChange, { gs_.PLAYERS_START.X + 61, gs_.PLAYERS_START.Y + 4 });

		if (gs_.currentNameChange == 1)
		{
			gs_.setCursorInfo(10, true);
			gs_.setCursorPosition({ gs_.PLAYERS_START.X + 61 + gs_.currentNameChangePosition, gs_.PLAYERS_START.Y + 2 });
		}
		else if (gs_.currentNameChange == 2)
		{
			gs_.setCursorInfo(10, true);
			gs_.setCursorPosition({ gs_.PLAYERS_START.X + 61 + gs_.currentNameChangePosition, gs_.PLAYERS_START.Y + 4 });
		}
		else
		{
			gs_.setCursorInfo(0, false);
		}

		if (gs_.player1RunCount >= 5)
		{
			if (gs_.player1Color == gs_.BACKGROUND_BLACK)
			{
				gs_.fillWithAttribute(gs_.BACKGROUND_GREY, 17, { gs_.PLAYERS_START.X, gs_.PLAYERS_START.Y + 6 });
			}
			else if (gs_.player1Color == gs_.BACKGROUND_IRED)
			{
				gs_.fillWithAttribute(gs_.BACKGROUND_GREY + gs_.FOREGROUND_IRED, 17, { gs_.PLAYERS_START.X, gs_.PLAYERS_START.Y + 6 });
			}
			else if (gs_.player1Color == gs_.BACKGROUND_IGREEN)
			{
				gs_.fillWithAttribute(gs_.BACKGROUND_GREY + gs_.FOREGROUND_IGREEN, 17, { gs_.PLAYERS_START.X, gs_.PLAYERS_START.Y + 6 });
			}
			else if (gs_.player1Color == gs_.BACKGROUND_IBLUE)
			{
				gs_.fillWithAttribute(gs_.BACKGROUND_GREY + gs_.FOREGROUND_IBLUE, 17, { gs_.PLAYERS_START.X, gs_.PLAYERS_START.Y + 6 });
			}
			else if (gs_.player1Color == gs_.BACKGROUND_ICYAN)
			{
				gs_.fillWithAttribute(gs_.BACKGROUND_GREY + gs_.FOREGROUND_ICYAN, 17, { gs_.PLAYERS_START.X, gs_.PLAYERS_START.Y + 6 });
			}
			else if (gs_.player1Color == gs_.BACKGROUND_IMAGENTA)
			{
				gs_.fillWithAttribute(gs_.BACKGROUND_GREY + gs_.FOREGROUND_IMAGENTA, 17, { gs_.PLAYERS_START.X, gs_.PLAYERS_START.Y + 6 });
			}
			else if (gs_.player1Color == gs_.BACKGROUND_IYELLOW)
			{
				gs_.fillWithAttribute(gs_.BACKGROUND_GREY + gs_.FOREGROUND_IYELLOW, 17, { gs_.PLAYERS_START.X, gs_.PLAYERS_START.Y + 6 });
			}

			gs_.writeWithString(gs_.player1Name + " Wins!", { gs_.PLAYERS_START.X, gs_.PLAYERS_START.Y + 6 });
		}
		else if (gs_.player2RunCount >= 5)
		{
			if (gs_.player2Color == gs_.BACKGROUND_BLACK)
			{
				gs_.fillWithAttribute(gs_.BACKGROUND_GREY, 17, { gs_.PLAYERS_START.X, gs_.PLAYERS_START.Y + 6 });
			}
			else if (gs_.player2Color == gs_.BACKGROUND_IRED)
			{
				gs_.fillWithAttribute(gs_.BACKGROUND_GREY + gs_.FOREGROUND_IRED, 17, { gs_.PLAYERS_START.X, gs_.PLAYERS_START.Y + 6 });
			}
			else if (gs_.player2Color == gs_.BACKGROUND_IGREEN)
			{
				gs_.fillWithAttribute(gs_.BACKGROUND_GREY + gs_.FOREGROUND_IGREEN, 17, { gs_.PLAYERS_START.X, gs_.PLAYERS_START.Y + 6 });
			}
			else if (gs_.player2Color == gs_.BACKGROUND_IBLUE)
			{
				gs_.fillWithAttribute(gs_.BACKGROUND_GREY + gs_.FOREGROUND_IBLUE, 17, { gs_.PLAYERS_START.X, gs_.PLAYERS_START.Y + 6 });
			}
			else if (gs_.player2Color == gs_.BACKGROUND_ICYAN)
			{
				gs_.fillWithAttribute(gs_.BACKGROUND_GREY + gs_.FOREGROUND_ICYAN, 17, { gs_.PLAYERS_START.X, gs_.PLAYERS_START.Y + 6 });
			}
			else if (gs_.player2Color == gs_.BACKGROUND_IMAGENTA)
			{
				gs_.fillWithAttribute(gs_.BACKGROUND_GREY + gs_.FOREGROUND_IMAGENTA, 17, { gs_.PLAYERS_START.X, gs_.PLAYERS_START.Y + 6 });
			}
			else if (gs_.player2Color == gs_.BACKGROUND_IYELLOW)
			{
				gs_.fillWithAttribute(gs_.BACKGROUND_GREY + gs_.FOREGROUND_IYELLOW, 17, { gs_.PLAYERS_START.X, gs_.PLAYERS_START.Y + 6 });
			}

			gs_.writeWithString(gs_.player2Name + " Wins!", { gs_.PLAYERS_START.X, gs_.PLAYERS_START.Y + 6 });
		}
		else
		{
			gs_.fillWithChar(' ', 17, { gs_.PLAYERS_START.X, gs_.PLAYERS_START.Y + 6 });
		}
	}
}
