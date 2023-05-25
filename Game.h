#ifndef __GAME_H
#define __GAME_H
#include "stdbool.h"
#include "stdlib.h"
#include <vector>
#include "Board.h"
#include "Ghost.h"
#include "Position.h"
#include "Fruit.h"
#include "PacWoman.h"

const int KEYSIZE = 5;
const int ESC = 27;

class Game
{
	char arrowKeys[KEYSIZE];
	Board gameBoard;
	PacWoman pac;
	std::vector<Ghost> ghostsVec;
	int ghostsAmount, fruitsAmount;
	std::vector<Fruit> fruitsVec;
	bool isSpecificMapGame;
public:
	Game(const std::string& fileName, bool isSpecificMap);

	Board& getGameBoard() { return gameBoard; }
	PacWoman& getPac() { return pac; }
	std::vector<Ghost>& getGhostsVec() { return ghostsVec; }
	int getGhostsAmount() const { return ghostsAmount; }
	std::vector<Fruit>& getFruitsVec() { return fruitsVec; }
	bool getIsSpecificMapGame() { return isSpecificMapGame; }
	int getFruitsAmount() const { return fruitsAmount; }

	void setGhostsVec(const Ghost& newGhost) { ghostsVec.push_back(newGhost); }
	void setArrowKeys(const char* keys);

	bool isValidDirection(char direction) const;
	void runGame(int flag, int& countPoints, char& pacDir, std::vector<char>& behindGhosts, std::vector<char>& behindFruits, std::vector<char>& ghostsDir, int& ghostStepsCounter, int& fruitStepsCounter, const char gameLevel);
};
#endif