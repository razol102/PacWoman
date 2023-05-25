#ifndef __GAMECREATURES_H
#define __GAMECREATURES_H

#include "Position.h"
#include <cstdlib> 
const char UP_DIR_KEY = 'w';
const char DOWN_DIR_KEY = 'x';
const char RIGHT_DIR_KEY = 'd';
const char LEFT_DIR_KEY = 'a';
const char STAY_KEY = 's';
const char PACWOMAN_SIGN = 'W';
const char GHOST_SIGN = 'O';

class Board;

class GameCreatures
{
protected:
	Position creaturePos;
	Board& gameBoard;
	char direction, sign;
public:
	GameCreatures(Board& board, char dir = RIGHT_DIR_KEY) : direction(dir), gameBoard(board) {}

	char getDirection() const { return direction; }
	Position& getPos() { return creaturePos; }
	char getSign() const { return sign; }

	void setDirection(const char dir) { direction = dir; }
	void setPos(const Position& newPos) { creaturePos.setPoint(newPos); }
	char randNewDirection();
	void operator=(const GameCreatures& other);
};
#endif

