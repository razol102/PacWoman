#ifndef __GAME_WOMANAGER_H
#define __GAME_WOMANAGER_H

#include "stdbool.h"
#include <string>
#include <vector>
#include "Game.h"
#include "Menu.h"
class Ghost;

const int NEW_GAME = 1;
const int MAP_CHOICE = 2;
const int MAX_LIVES = 3;
const int MAX_SCREENS = 3;
const int INSTRUCTION = 8;
const int EXIT = 9;

class GameWoManager
{
	Game* theGame = nullptr;
	Menu mainMenu;
	int lives = MAX_LIVES, points = 0, fruitsPoints = 0;
	std::string stats, currMap;
	int level = 1;
public:
	GameWoManager();
	GameWoManager(const GameWoManager& other);

	Game* getTheGame() const { return theGame; }
	int getLives() const { return lives; }
	int getPoints() const { return points; }
	std::string getStats() const { return stats; }
	int getLevel() const { return level; }
	Menu& getMainMenu() { return mainMenu; }

	void setLives(char currLives);
	void setPoints(int currPoints);
	void setLevel(int newLevel) { level = newLevel; }
	void setTheGame(std::string fileName, bool isSpecificMap);

	bool isBreadCrumbsLeft(std::vector<char>& behindGhosts, std::vector<char>& behindFruits);
	void initStats(int currLives);
	bool samePosition(const Position& creature1Pos, const Position& creature2Pos) const;
	void manageGame(int& choice);
	void initVectors(std::vector<char>& behindGhosts, std::vector<char>& ghostsDir, std::vector<char>& behindFruit, int ghostsAmount);
	void ghostAndPacMeeting(int ghostsAmount, std::vector<char>& behindGhosts);
	void fruitsAndOtherCreaturesMeeting(int& fruitStepsCounter, int ghostsAmount, std::vector<char>& behindFruit);
	int countDigits(int num);
	void clearScreen() const { system("cls"); }
	void hideCursor();
	void initBoardAfterLosingLife(std::vector<char>& behindGhosts);
	void initGhostPos(Ghost& ghost, char& behindGhost, int initCol, int initRow);
	const std::string getNextScreenName() const;
	void goToNextLevel(int& choice);
	const char setGhostsLevel() const;

	void operator=(const GameWoManager& other);
	~GameWoManager() { delete theGame; }
};
#endif