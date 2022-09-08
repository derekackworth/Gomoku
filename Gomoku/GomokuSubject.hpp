/*
	Author: Derek Ackworth
	Date: April 18th, 2019
	File: GomokuSubject.hpp
	Purpose: GomokuSubject class declaration
*/

#pragma once

#include "Console.hpp"
#include "Subject.hpp"

class GomokuSubject : public Console, public Subject
{
public:
	GomokuSubject();
	~GomokuSubject() { restore(); }

	int execute() override;

	void changeRun(int y, int x);

	static BOOL ctrlHandler(DWORD ctrlType);
	void mouseEventProc(MOUSE_EVENT_RECORD const& mer);
	void processKeyEvent(KEY_EVENT_RECORD const& ker);

	static COORD constexpr PLAYERS_START = { 0, 0 };
	static SHORT constexpr PLAYERS_WIDTH = 73;
	static SHORT constexpr PLAYERS_HEIGHT = 7;

	static COORD constexpr SCORE_START = { 73, 0 };
	static SHORT constexpr SCORE_WIDTH = 30;
	static SHORT constexpr SCORE_HEIGHT = 7;

	static COORD constexpr GAME_START = { 0, 7 };
	static SHORT constexpr GAME_WIDTH = 73;
	static SHORT constexpr GAME_HEIGHT = 29;

	static COORD constexpr LIST_OF_MOVES_START = { 73, 7 };
	static SHORT constexpr LIST_OF_MOVES_WIDTH = 30;
	static SHORT constexpr LIST_OF_MOVES_HEIGHT = 29;

	string player1Name;
	string player2Name;
	WORD player1Color;
	WORD player2Color;
	string player1NameChange;
	string player2NameChange;
	int player1TileCount;
	int player2TileCount;
	int player1RunCount;
	int player2RunCount;
	int currentNameChange;
	SHORT currentNameChangePosition;
	int currentPlayer;
	int gameBoardGrid[15][15];
	vector<string> listOfMoves;
};
