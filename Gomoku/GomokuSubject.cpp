/*
	Author: Derek Ackworth
	Date: April 18th, 2019
	File: GomokuSubject.cpp
	Purpose: GomokuSubject class implementation
*/

#include "GomokuSubject.hpp"

// Global variables
static bool g_isRunning = true;

// Default constructor
GomokuSubject::GomokuSubject()
{
	// Define variables
	player1Name = "Player 1";
	player2Name = "Player 2";
	player1Color = BACKGROUND_IRED;
	player2Color = BACKGROUND_BLACK;
}

// Application code
int GomokuSubject::execute()
{
	// Setup
	save();
	create("Gomoku");
	setSize(103, 36);
	setCursorInfo(0, false);
	notifyAll();
	currentPlayer = 1;

	// Install ctrl handler
	if (!installCtrlHandler(ctrlHandler))
	{
		return EXIT_FAILURE;
	}

	vector<INPUT_RECORD> inputBuffer(128);

	// Read input buffer
	while (g_isRunning)
	{
		DWORD numEvents;

		if (!readInput(inputBuffer, numEvents))
		{
			return EXIT_FAILURE;
		}

		for (size_t inputEvent = 0; inputEvent < numEvents; ++inputEvent)
		{
			switch (inputBuffer[inputEvent].EventType)
			{
			case MOUSE_EVENT:
				mouseEventProc(inputBuffer[inputEvent].Event.MouseEvent);
				break;
			case KEY_EVENT:
				processKeyEvent(inputBuffer[inputEvent].Event.KeyEvent);
				break;
			}
		}
	}

	return EXIT_SUCCESS;
}

/*
	Change current player's run to its highest run
	Input: Gameboard coords just painted
*/
void GomokuSubject::changeRun(int y, int x)
{
	int counter = 0;

	// Check vertical
	for (int i = max(y - 4, 0); i <= min(y + 4, 15 - 1); i++)
	{
		if (gameBoardGrid[i][x] == currentPlayer)
		{
			counter++;

			if (currentPlayer == 1 && counter > player1RunCount)
			{
				player1RunCount = counter;
			}
			else if (currentPlayer == 2 && counter > player2RunCount)
			{
				player2RunCount = counter;
			}
		}
		else
		{
			counter = 0;
		}
	}

	counter = 0;

	// Check horizontal
	for (int i = max(x - 4, 0); i <= min(x + 4, 15 - 1); i++)
	{
		if (gameBoardGrid[y][i] == currentPlayer)
		{
			counter++;

			if (currentPlayer == 1 && counter > player1RunCount)
			{
				player1RunCount = counter;
			}
			else if (currentPlayer == 2 && counter > player2RunCount)
			{
				player2RunCount = counter;
			}
		}
		else
		{
			counter = 0;
		}
	}

	counter = 0;
	int i = y;
	int j = x;

	// Set y and x to the lowest possible without being negative
	while (i > 0 || i > y - 4 || j > 0 || j > x - 4)
	{
		i--;
		j--;
	}

	// Check first diagonal
	for (; i <= min(y + 4, 15 - 1) || j <= min(x + 4, 15 - 1); i++, j++)
	{
		if (gameBoardGrid[i][j] == currentPlayer)
		{
			counter++;

			if (currentPlayer == 1 && counter > player1RunCount)
			{
				player1RunCount = counter;
			}
			else if (currentPlayer == 2 && counter > player2RunCount)
			{
				player2RunCount = counter;
			}
		}
		else
		{
			counter = 0;
		}
	}

	counter = 0;
	i = y;
	j = x;

	// Set y to the highest possible without being greater than the game board size and set x to the lowest possible without being negative
	while (i < 15 - 1 || i < y + 4 || j > 0 || j > x - 4)
	{
		i++;
		j--;
	}

	// Check second diagonal
	for (; i >= max(x - 4, 0) || j <= min(x + 4, 15 - 1); i--, j++)
	{
		if (gameBoardGrid[i][j] == currentPlayer)
		{
			counter++;

			if (currentPlayer == 1 && counter > player1RunCount)
			{
				player1RunCount = counter;
			}
			else if (currentPlayer == 2 && counter > player2RunCount)
			{
				player2RunCount = counter;
			}
		}
		else
		{
			counter = 0;
		}
	}
}

/*
	Ctrl event handler
	Input: Ctrl type
*/
BOOL GomokuSubject::ctrlHandler(DWORD ctrlType)
{
	// Ctrl close event closes application
	if (ctrlType <= CTRL_CLOSE_EVENT)
	{
		g_isRunning = false;
		return TRUE;
	}

	return FALSE;
}

/*
	Mouse event handler
	Input: Mouse event record
*/
void GomokuSubject::mouseEventProc(MOUSE_EVENT_RECORD const& mer)
{
	auto mask = mer.dwButtonState;
	auto bufferLoc = mer.dwMousePosition;

	switch (mer.dwEventFlags)
	{
	case 0:
		// Left button press on PlayersObserver
		if (mask & FROM_LEFT_1ST_BUTTON_PRESSED && bufferLoc.X >= PLAYERS_START.X && bufferLoc.X < PLAYERS_START.X + PLAYERS_WIDTH &&
			bufferLoc.Y >= PLAYERS_START.Y && bufferLoc.Y < PLAYERS_START.Y + PLAYERS_HEIGHT)
		{
			// Change player color if a color is pressed that the other player isn't
			if (bufferLoc.X >= PLAYERS_START.X + 32 && bufferLoc.X <= PLAYERS_START.X + 33 &&
				bufferLoc.Y == PLAYERS_START.Y + 2 && player2Color != BACKGROUND_BLACK)
			{
				player1Color = BACKGROUND_BLACK;

				if (listOfMoves.size() != 0)
				{
					notify("class GameObserver");
					notify("class ListOfMovesObserver");
				}
			}
			else if (bufferLoc.X >= PLAYERS_START.X + 36 && bufferLoc.X <= PLAYERS_START.X + 37 &&
				bufferLoc.Y == PLAYERS_START.Y + 2 && player2Color != BACKGROUND_IRED)
			{
				player1Color = BACKGROUND_IRED;

				if (listOfMoves.size() != 0)
				{
					notify("class GameObserver");
					notify("class ListOfMovesObserver");
				}
			}
			else if (bufferLoc.X >= PLAYERS_START.X + 40 && bufferLoc.X <= PLAYERS_START.X + 41 &&
				bufferLoc.Y == PLAYERS_START.Y + 2 && player2Color != BACKGROUND_IGREEN)
			{
				player1Color = BACKGROUND_IGREEN;

				if (listOfMoves.size() != 0)
				{
					notify("class GameObserver");
					notify("class ListOfMovesObserver");
				}
			}
			else if (bufferLoc.X >= PLAYERS_START.X + 44 && bufferLoc.X <= PLAYERS_START.X + 45 &&
				bufferLoc.Y == PLAYERS_START.Y + 2 && player2Color != BACKGROUND_IBLUE)
			{
				player1Color = BACKGROUND_IBLUE;

				if (listOfMoves.size() != 0)
				{
					notify("class GameObserver");
					notify("class ListOfMovesObserver");
				}
			}
			else if (bufferLoc.X >= PLAYERS_START.X + 48 && bufferLoc.X <= PLAYERS_START.X + 49 &&
				bufferLoc.Y == PLAYERS_START.Y + 2 && player2Color != BACKGROUND_ICYAN)
			{
				player1Color = BACKGROUND_ICYAN;

				if (listOfMoves.size() != 0)
				{
					notify("class GameObserver");
					notify("class ListOfMovesObserver");
				}
			}
			else if (bufferLoc.X >= PLAYERS_START.X + 52 && bufferLoc.X <= PLAYERS_START.X + 53 &&
				bufferLoc.Y == PLAYERS_START.Y + 2 && player2Color != BACKGROUND_IMAGENTA)
			{
				player1Color = BACKGROUND_IMAGENTA;

				if (listOfMoves.size() != 0)
				{
					notify("class GameObserver");
					notify("class ListOfMovesObserver");
				}
			}
			else if (bufferLoc.X >= PLAYERS_START.X + 56 && bufferLoc.X <= PLAYERS_START.X + 57 &&
				bufferLoc.Y == PLAYERS_START.Y + 2 && player2Color != BACKGROUND_IYELLOW)
			{
				player1Color = BACKGROUND_IYELLOW;

				if (listOfMoves.size() != 0)
				{
					notify("class GameObserver");
					notify("class ListOfMovesObserver");
				}
			}
			else if (bufferLoc.X >= PLAYERS_START.X + 32 && bufferLoc.X <= PLAYERS_START.X + 33 &&
				bufferLoc.Y == PLAYERS_START.Y + 4 && player1Color != BACKGROUND_BLACK)
			{
				player2Color = BACKGROUND_BLACK;

				if (listOfMoves.size() != 0)
				{
					notify("class GameObserver");
					notify("class ListOfMovesObserver");
				}
			}
			else if (bufferLoc.X >= PLAYERS_START.X + 36 && bufferLoc.X <= PLAYERS_START.X + 37 &&
				bufferLoc.Y == PLAYERS_START.Y + 4 && player1Color != BACKGROUND_IRED)
			{
				player2Color = BACKGROUND_IRED;

				if (listOfMoves.size() != 0)
				{
					notify("class GameObserver");
					notify("class ListOfMovesObserver");
				}
			}
			else if (bufferLoc.X >= PLAYERS_START.X + 40 && bufferLoc.X <= PLAYERS_START.X + 41 &&
				bufferLoc.Y == PLAYERS_START.Y + 4 && player1Color != BACKGROUND_IGREEN)
			{
				player2Color = BACKGROUND_IGREEN;

				if (listOfMoves.size() != 0)
				{
					notify("class GameObserver");
					notify("class ListOfMovesObserver");
				}
			}
			else if (bufferLoc.X >= PLAYERS_START.X + 44 && bufferLoc.X <= PLAYERS_START.X + 45 &&
				bufferLoc.Y == PLAYERS_START.Y + 4 && player1Color != BACKGROUND_IBLUE)
			{
				player2Color = BACKGROUND_IBLUE;

				if (listOfMoves.size() != 0)
				{
					notify("class GameObserver");
					notify("class ListOfMovesObserver");
				}
			}
			else if (bufferLoc.X >= PLAYERS_START.X + 48 && bufferLoc.X <= PLAYERS_START.X + 49 &&
				bufferLoc.Y == PLAYERS_START.Y + 4 && player1Color != BACKGROUND_ICYAN)
			{
				player2Color = BACKGROUND_ICYAN;

				if (listOfMoves.size() != 0)
				{
					notify("class GameObserver");
					notify("class ListOfMovesObserver");
				}
			}
			else if (bufferLoc.X >= PLAYERS_START.X + 52 && bufferLoc.X <= PLAYERS_START.X + 53 &&
				bufferLoc.Y == PLAYERS_START.Y + 4 && player1Color != BACKGROUND_IMAGENTA)
			{
				player2Color = BACKGROUND_IMAGENTA;

				if (listOfMoves.size() != 0)
				{
					notify("class GameObserver");
					notify("class ListOfMovesObserver");
				}
			}
			else if (bufferLoc.X >= PLAYERS_START.X + 56 && bufferLoc.X <= PLAYERS_START.X + 57 &&
				bufferLoc.Y == PLAYERS_START.Y + 4 && player1Color != BACKGROUND_IYELLOW)
			{
				player2Color = BACKGROUND_IYELLOW;

				if (listOfMoves.size() != 0)
				{
					notify("class GameObserver");
					notify("class ListOfMovesObserver");
				}
			}

			// Enable cursor and set cursor positon if pressed on the name change textbox, else disable cursor
			if (bufferLoc.X >= PLAYERS_START.X + 61 && bufferLoc.X <= PLAYERS_START.X + 73 &&
				bufferLoc.Y == PLAYERS_START.Y + 2)
			{
				if (bufferLoc.X - PLAYERS_START.X - 61 > (int)player1NameChange.size())
				{
					currentNameChangePosition = (SHORT)player1NameChange.size();
				}
				else
				{
					currentNameChangePosition = bufferLoc.X - PLAYERS_START.X - 61;
				}

				currentNameChange = 1;
			}
			else if (bufferLoc.X >= PLAYERS_START.X + 61 && bufferLoc.X <= PLAYERS_START.X + 73 &&
				bufferLoc.Y == PLAYERS_START.Y + 4)
			{
				if (bufferLoc.X - PLAYERS_START.X - 61 > (int)player2NameChange.size())
				{
					currentNameChangePosition = (SHORT)player2NameChange.size();
				}
				else
				{
					currentNameChangePosition = bufferLoc.X - PLAYERS_START.X - 61;
				}

				currentNameChange = 2;
			}
			else
			{
				currentNameChangePosition = 0;
				currentNameChange = 0;
			}
		}

		// Left button press on ScoreObserver
		if (mask & FROM_LEFT_1ST_BUTTON_PRESSED && bufferLoc.X >= SCORE_START.X && bufferLoc.X < SCORE_START.X + SCORE_WIDTH &&
			bufferLoc.Y >= SCORE_START.Y && bufferLoc.Y < SCORE_START.Y + SCORE_HEIGHT)
		{
			currentNameChange = 0;
		}

		// Left button press on GameObserver
		if (mask & FROM_LEFT_1ST_BUTTON_PRESSED && bufferLoc.X >= GAME_START.X && bufferLoc.X < GAME_START.X + GAME_WIDTH &&
			bufferLoc.Y >= GAME_START.Y && bufferLoc.Y < GAME_START.Y + GAME_HEIGHT)
		{
			currentNameChange = 0;

			// Add a piece to the game board if pressed on a currently empty part of the game board and add it to the listOfMoves
			if (gameBoardGrid[(bufferLoc.Y - GAME_START.Y) / 2][(bufferLoc.X - GAME_START.X + 1) / 5] == 0)
			{
				switch ((bufferLoc.X - GAME_START.X + 1) / 5)
				{
				case 0:
					listOfMoves.push_back("A:" + to_string((bufferLoc.Y - GAME_START.Y) / 2 + 1));
					break;
				case 1:
					listOfMoves.push_back("B:" + to_string((bufferLoc.Y - GAME_START.Y) / 2 + 1));
					break;
				case 2:
					listOfMoves.push_back("C:" + to_string((bufferLoc.Y - GAME_START.Y) / 2 + 1));
					break;
				case 3:
					listOfMoves.push_back("D:" + to_string((bufferLoc.Y - GAME_START.Y) / 2 + 1));
					break;
				case 4:
					listOfMoves.push_back("E:" + to_string((bufferLoc.Y - GAME_START.Y) / 2 + 1));
					break;
				case 5:
					listOfMoves.push_back("F:" + to_string((bufferLoc.Y - GAME_START.Y) / 2 + 1));
					break;
				case 6:
					listOfMoves.push_back("G:" + to_string((bufferLoc.Y - GAME_START.Y) / 2 + 1));
					break;
				case 7:
					listOfMoves.push_back("H:" + to_string((bufferLoc.Y - GAME_START.Y) / 2 + 1));
					break;
				case 8:
					listOfMoves.push_back("I:" + to_string((bufferLoc.Y - GAME_START.Y) / 2 + 1));
					break;
				case 9:
					listOfMoves.push_back("J:" + to_string((bufferLoc.Y - GAME_START.Y) / 2 + 1));
					break;
				case 10:
					listOfMoves.push_back("K:" + to_string((bufferLoc.Y - GAME_START.Y) / 2 + 1));
					break;
				case 11:
					listOfMoves.push_back("L:" + to_string((bufferLoc.Y - GAME_START.Y) / 2 + 1));
					break;
				case 12:
					listOfMoves.push_back("M:" + to_string((bufferLoc.Y - GAME_START.Y) / 2 + 1));
					break;
				case 13:
					listOfMoves.push_back("N:" + to_string((bufferLoc.Y - GAME_START.Y) / 2 + 1));
					break;
				case 14:
					listOfMoves.push_back("O:" + to_string((bufferLoc.Y - GAME_START.Y) / 2 + 1));
					break;
				}

				gameBoardGrid[(bufferLoc.Y - GAME_START.Y) / 2][(bufferLoc.X - GAME_START.X + 1) / 5] = currentPlayer;
				notify("class GameObserver");

				if (currentPlayer == 1)
				{
					player1TileCount++;
					changeRun((bufferLoc.Y - GAME_START.Y) / 2, (bufferLoc.X - GAME_START.X + 1) / 5);

					if (player1RunCount >= 5)
					{
						notify("class PlayersObserver");
						notify("class ScoreObserver");
						notify("class ListOfMovesObserver");
						Sleep(3000);
						listOfMoves.clear();
						player1TileCount = 0;
						player2TileCount = 0;
						player1RunCount = 0;
						player2RunCount = 0;

						for (SHORT i = 0; i < 15; i++)
						{
							for (SHORT j = 0; j < 15; j++)
							{
								gameBoardGrid[i][j] = 0;
							}
						}

						notify("class ScoreObserver");
						notify("class GameObserver");
						notify("class ListOfMovesObserver");
					}
					else
					{
						notify("class ScoreObserver");
						notify("class ListOfMovesObserver");
						currentPlayer = 2;
					}
				}
				else if (currentPlayer == 2)
				{
					player2TileCount++;
					changeRun((bufferLoc.Y - GAME_START.Y) / 2, (bufferLoc.X - GAME_START.X + 1) / 5);

					if (player2RunCount >= 5)
					{
						notify("class PlayersObserver");
						notify("class ScoreObserver");
						notify("class ListOfMovesObserver");
						Sleep(3000);
						currentPlayer = 1;
						listOfMoves.clear();
						player1TileCount = 0;
						player2TileCount = 0;
						player1RunCount = 0;
						player2RunCount = 0;

						for (SHORT i = 0; i < 15; i++)
						{
							for (SHORT j = 0; j < 15; j++)
							{
								gameBoardGrid[i][j] = 0;
							}
						}

						notify("class ScoreObserver");
						notify("class GameObserver");
						notify("class ListOfMovesObserver");
					}
					else
					{
						notify("class ScoreObserver");
						notify("class ListOfMovesObserver");
						currentPlayer = 1;
					}
				}
			}
		}

		// Left button press on ListOfMovesObserver
		if (mask & FROM_LEFT_1ST_BUTTON_PRESSED && bufferLoc.X >= LIST_OF_MOVES_START.X &&
			bufferLoc.X < LIST_OF_MOVES_START.X + LIST_OF_MOVES_WIDTH && bufferLoc.Y >= LIST_OF_MOVES_START.Y &&
			bufferLoc.Y < LIST_OF_MOVES_START.Y + LIST_OF_MOVES_HEIGHT)
		{
			currentNameChange = 0;
		}

		notify("class PlayersObserver");
		break;
	}
}

/*
	Key event handler
	Input: Key Event Record
*/
void GomokuSubject::processKeyEvent(KEY_EVENT_RECORD const& ker)
{
	if (ker.bKeyDown)
	{
		if (currentNameChange != 0)
		{
			switch (ker.wVirtualKeyCode)
			{
			// Backspace to pop_back current textbox string
			case VK_BACK:
				if (currentNameChange == 1 && currentNameChangePosition != 0)
				{
					player1NameChange.erase(currentNameChangePosition - 1, 1);
					currentNameChangePosition--;
					notify("class PlayersObserver");
				}
				else if (currentNameChange == 2 && currentNameChangePosition != 0)
				{
					player2NameChange.erase(currentNameChangePosition - 1, 1);
					currentNameChangePosition--;
					notify("class PlayersObserver");
				}

				break;

			// Delete to clear current textbox string
			case VK_DELETE:
				if (currentNameChange == 1 && player1NameChange.size() != 0)
				{
					currentNameChangePosition = 0;
					player1NameChange.clear();
					notify("class PlayersObserver");
				}
				else if (currentNameChange == 2 && player2NameChange.size() != 0)
				{
					currentNameChangePosition = 0;
					player2NameChange.clear();
					notify("class PlayersObserver");
				}

				break;

			// Left to move currentNameChangePosition left
			case VK_LEFT:
				if (currentNameChangePosition > 0)
				{
					currentNameChangePosition--;
					notify("class PlayersObserver");
				}
				break;

			// Right to move currentNameChangePosition right
			case VK_RIGHT:
				if ((currentNameChange == 1 && currentNameChangePosition < (SHORT)player1NameChange.size()) ||
					(currentNameChange == 2 && currentNameChangePosition < (SHORT)player2NameChange.size()))
				{
					currentNameChangePosition++;
					notify("class PlayersObserver");
				}

				break;

			// End to move currentNameChangePosition to the end of the string
			case VK_END:
				if (currentNameChange == 1)
				{
					currentNameChangePosition = (SHORT)player1NameChange.size();
					notify("class PlayersObserver");
				}
				else if (currentNameChange == 2)
				{
					currentNameChangePosition = (SHORT)player2NameChange.size();
					notify("class PlayersObserver");
				}

				break;

			// Home to move currentNameChangePosition to 0
			case VK_HOME:
				currentNameChangePosition = 0;
				notify("class PlayersObserver");
				break;

			// Enter to change players name and clear the textbox
			case VK_RETURN:
				if (currentNameChange == 1 && player1NameChange != player2Name && player1NameChange.size() != 0)
				{
					player1Name = player1NameChange;
					currentNameChangePosition = 0;
					player1NameChange.clear();
					notify("class PlayersObserver");
				}
				else if (currentNameChange == 2 && player2NameChange != player1Name && player2NameChange.size() != 0)
				{
					player2Name = player2NameChange;
					currentNameChangePosition = 0;
					player2NameChange.clear();
					notify("class PlayersObserver");
				}

				break;

			// Add character to player name change
			default:
				if (currentNameChange == 1 && player1NameChange.size() < 11 && isprint(ker.uChar.AsciiChar))
				{
					player1NameChange += ker.uChar.AsciiChar;
					currentNameChangePosition++;
					notify("class PlayersObserver");
				}
				else if (currentNameChange == 2 && player2NameChange.size() < 11 && isprint(ker.uChar.AsciiChar))
				{
					player2NameChange += ker.uChar.AsciiChar;
					currentNameChangePosition++;
					notify("class PlayersObserver");
				}
			}
		}

		// 'r' press resets game if not in a textbox
		else if (ker.uChar.AsciiChar == 'r')
		{
			currentPlayer = 1;
			listOfMoves.clear();
			player1TileCount = 0;
			player2TileCount = 0;
			player1RunCount = 0;
			player2RunCount = 0;

			for (SHORT i = 0; i < 15; i++)
			{
				for (SHORT j = 0; j < 15; j++)
				{
					gameBoardGrid[i][j] = 0;
				}
			}

			notify("class ScoreObserver");
			notify("class GameObserver");
			notify("class ListOfMovesObserver");
		}
	}
}
