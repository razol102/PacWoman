#ifndef __BOARD_H
#define __BOARD_H

#include <iostream>
#include <vector>
#include "Position.h"
#include "GameCreatures.h"
#include <conio.h>
#include <windows.h>
#include <fstream>

const int LIVES_POS = 7;
const int POINTS_POS = 18;
const int MAX_GHOSTS = 4;
const int DIRECTIONS = 4;
const char WALL_SIGN = '#';
const char INIT_PAC_POS = '@';
const char INIT_GHOST_POS = '$';
const char EMPTY_POS = '%';
const char INVISIBLEWALL_SIGN = '*';
const char BREADCRUMB_SIGN = '`';

class Board
{
	std::string board;
	int rows;
	int cols;
	int maxBreadCrumbs = 0;
	std::vector<Position> ghostsInitPosVec;
	std::vector<Position> fruitsInitPosVec;
	Position initPacPos;
public:
	Board(const std::string& fileName);

	int getGameRows() const { return rows; }
	int getGameCols() const { return cols; }
	std::string getBoard() const { return board; }
	char getCellFromBoard(const Position& p) const { return board[getPoint(p)]; }
	int getPoint(const Position& p) const { return p.getRow() * cols + p.getCol(); }
	Position& getInitPacPos() { return initPacPos; }
	std::vector<Position>& getGhostsInitPosVec() { return ghostsInitPosVec; }
	std::vector<Position>& getFruitsInitPosVec() { return fruitsInitPosVec; }
	int getMaxBreadCrumbs() { return maxBreadCrumbs; }

	void setInitPacPos(const Position& pacPos) { initPacPos.setPoint(pacPos); }
	void setCell(char value, const Position& p) { board[getPoint(p)] = value; }
	void setCell(char value, int index) { board[index] = value; }

	bool isWall(const Position& pos) const;
	bool isInvisibleWall(const Position& pos) const;
	bool isBreadCrumbs(const Position& pos) const;
	void setCurrentGameBoard();
	void printBoard() const {std::cout << board;}
	static void gotoxy(int x, int y);	
	static void gotoxy(const Position& pos);
	void setFruitOnBoard();
};
#endif