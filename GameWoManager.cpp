#include "Position.h"
#include "Board.h"
#include "Ghost.h"
#include "GameWoManager.h"
#include "Fruit.h"
#include "Game.h"

using namespace std;

GameWoManager::GameWoManager():mainMenu(*this)
//Constructor
{
	stats = "Lives: " + to_string(lives) + ", Points: " + to_string(points);
	stats.reserve(stats.size() + 4); //adds 4 digits to points (4 digits potential number)
}

GameWoManager::GameWoManager(const GameWoManager& other):mainMenu(*this)
//copy c'tor
{
	this->theGame = new Game(other.currMap, other.theGame->getIsSpecificMapGame());
	this->theGame = other.theGame;
	this->lives = other.lives;
	this->points = other.points;
	this->fruitsPoints = other.fruitsPoints;
	this->stats = other.stats;
	this->currMap = other.currMap;
	this->level = other.level;
}

void GameWoManager::initStats(int currLives)
//This function inits game stats
{
	lives = currLives, points = 0, fruitsPoints = 0;
	stats = "Lives: " + to_string(lives) + ", Points: " + to_string(points);
}

void GameWoManager::manageGame(int& choice)
//This function manages the running game until the user losing/wining it
{
	bool endTheGame = false;
	vector<char> behindGhosts, ghostsDir, behindFruits;
	int ghostsAmount = theGame->getGhostsAmount(), ghostStepsCounter = 1, fruitStepsCounter = 1, flag = 1;
	char pacDir = STAY_KEY, levelChoice = setGhostsLevel();

	initVectors(behindGhosts, ghostsDir, behindFruits, ghostsAmount);
	theGame->getGameBoard().printBoard();
	cout << stats << endl;
	hideCursor();

	while (!endTheGame)
	{
		theGame->runGame(flag, points, pacDir, behindGhosts, behindFruits, ghostsDir, ghostStepsCounter, fruitStepsCounter, levelChoice);
		setPoints(points);
		flag *= -1;

		ghostAndPacMeeting(ghostsAmount, behindGhosts);
		fruitsAndOtherCreaturesMeeting(fruitStepsCounter, ghostsAmount, behindFruits);

		if (!isBreadCrumbsLeft(behindGhosts, behindFruits) || lives == 0)
		{
			if (mainMenu.gameEnded(endTheGame, choice))
			{
				mainMenu.getMenuChoice(choice);
				if (choice == EXIT)
					endTheGame = true;
			}
			else
				goToNextLevel(choice);
		}	
	}
}

bool GameWoManager::isBreadCrumbsLeft(vector<char>& behindGhosts, vector<char>& behindFruits)
//This function checks if there are breadcrumbs left in the board
{
	int boardSize = theGame->getGameBoard().getBoard().size();
	int behindGhostsSize = behindGhosts.size();
	int behindFruitsSize = behindFruits.size();
	bool res = false;

	for (int i = 0; i < boardSize; i++)
		if (theGame->getGameBoard().getBoard()[i] == BREADCRUMB_SIGN)
			res = true;

	for (int i = 0; i < behindGhostsSize; i++)
		if (behindGhosts[i] == BREADCRUMB_SIGN)
			res = true;

	for (int i = 0; i < behindFruitsSize; i++)
		if (behindFruits[i] == BREADCRUMB_SIGN)
			res = true;

	return res;
}

void GameWoManager::initVectors(vector<char>& behindGhosts, vector<char>& ghostsDir, vector<char>& behindFruit, int ghostsAmount)
//This function inits the help vector that we made in manageGame function
{
	for (int i = 0; i < ghostsAmount; i++)
	{
		behindGhosts.push_back(BREADCRUMB_SIGN);
		ghostsDir.push_back(RIGHT_DIR_KEY);
	}

	for (int i = 0; i < theGame->getFruitsAmount(); i++)
		behindFruit.push_back(BREADCRUMB_SIGN);
}

void GameWoManager::ghostAndPacMeeting(int ghostsAmount, vector<char>& behindGhosts)
//This function handles the pacWoman and ghost meetings
{
	for (int i = 0; i < ghostsAmount; i++)
		if (samePosition(theGame->getPac().getPos(), theGame->getGhostsVec()[i].getPos()))
		{
			lives--;
			if (lives == 0)
				break;
			setLives(lives + '0');
			if (lives > 0)
				initBoardAfterLosingLife(behindGhosts);
		}
}

void GameWoManager::fruitsAndOtherCreaturesMeeting(int& fruitStepsCounter, int ghostsAmount, vector<char>& behindFruit)
//This function handles the fruits and ghost/pacWoman meetings
{
	for (int i = theGame->getFruitsAmount() - 1; i >= 0; i--)
	{
		if (theGame->getFruitsVec()[i].getAppear() == true)
		{
			if (samePosition(theGame->getPac().getPos(), theGame->getFruitsVec()[i].getPos())) //Pac & Fruit
			{
				fruitsPoints += theGame->getFruitsVec()[i].getValue();
				points += theGame->getFruitsVec()[i].getValue();
				setPoints(points);
				theGame->getFruitsVec()[i].setValue(0);
				theGame->getFruitsVec()[i].setAppear(false);
				behindFruit[i] = ' ';
				Board::gotoxy(theGame->getFruitsVec()[i].getPos().getCol(), theGame->getFruitsVec()[i].getPos().getRow());
				theGame->getGameBoard().setCell(behindFruit[i], theGame->getFruitsVec()[i].getPos());
				cout << theGame->getGameBoard().getCellFromBoard(theGame->getFruitsVec()[i].getPos());
			}
			else //Ghost & Fruit
			{
				for (int j = 0; j < ghostsAmount; j++)
					if (samePosition(theGame->getGhostsVec()[j].getPos(), theGame->getFruitsVec()[i].getPos()))
					{
						theGame->getFruitsVec()[i].setValue(0);
						theGame->getFruitsVec()[i].setAppear(false);
						Board::gotoxy(theGame->getFruitsVec()[i].getPos().getCol(), theGame->getFruitsVec()[i].getPos().getRow());
						theGame->getGameBoard().setCell(behindFruit[i], theGame->getFruitsVec()[i].getPos());
						cout << theGame->getGameBoard().getCellFromBoard(theGame->getFruitsVec()[i].getPos());
					}
			}
		}
	}
}

const char GameWoManager::setGhostsLevel() const
//This function gets the game level from the user and returns it
{
	char levelChoice;
	cout << "Choose game level:" << endl
	<<"(a) BEST (b) GOOD (c) NOVICE:" << endl;

	cin >> levelChoice;

	while (levelChoice != BEST && levelChoice != GOOD && levelChoice != NOVICE)
	{
		cout << endl << "Invalid choice. Please try again:" << endl;
		cin >> levelChoice;
	}
	clearScreen();
	return levelChoice;
}

void GameWoManager::operator=(const GameWoManager& other)
//operator=
{
	this->theGame = other.theGame;
	this->mainMenu = other.mainMenu;
	this->lives = other.lives;
	this->points = other.points;
	this->fruitsPoints = other.fruitsPoints;
	this->stats = other.stats;
	this->currMap = other.currMap;
	this->level = other.level;
}

void GameWoManager::initBoardAfterLosingLife(vector<char>& behindGhosts)
//This function inits the pacWoman and ghosts places after losing life
{
	Position currPacWomanPos = theGame->getPac().getPos();
	theGame->getPac().setDirection(STAY_KEY);

	Board::gotoxy(currPacWomanPos.getCol(), currPacWomanPos.getRow());
	theGame->getGameBoard().setCell(' ', currPacWomanPos);
	cout << theGame->getGameBoard().getCellFromBoard(currPacWomanPos); //prints ' ' on the previos pacWoamn place on screen
	theGame->getPac().setPos(Position(theGame->getGameBoard().getInitPacPos()));
	currPacWomanPos.draw(theGame->getPac().getSign());

	int ghostsAmount = theGame->getGhostsAmount();
	for (int i = 0; i < ghostsAmount; i++)
		initGhostPos(theGame->getGhostsVec()[i], behindGhosts[i], theGame->getGameBoard().getGhostsInitPosVec()[i].getCol(), theGame->getGameBoard().getGhostsInitPosVec()[i].getRow());
}

int GameWoManager::countDigits(int num)
//counts num's amount of digits
{
	int count = 0;

	while (num != 0) 
	{
		num /= 10;
		count++;
	}
	return count;
}

void GameWoManager::setLives(char currLives)
//This function sets the new lives amount on the screen
{
	Position livesPos(LIVES_POS, theGame->getGameBoard().getGameRows());
	Board::gotoxy(LIVES_POS, theGame->getGameBoard().getGameRows());
	stats[LIVES_POS] = currLives;
	cout << stats[LIVES_POS];
}

void GameWoManager::setPoints(int currPoints)
//This function sets the new points amount on the screen
{
	Position pointsPos(POINTS_POS, theGame->getGameBoard().getGameRows());
	int digitsAmount = countDigits(currPoints);

	for (int i = digitsAmount - 1; i >= 0; i--)
	{
		Board::gotoxy(POINTS_POS + i, theGame->getGameBoard().getGameRows());
		stats[stats.size() - digitsAmount + i] = (currPoints % 10) + '0';
		cout << stats[stats.size() - digitsAmount + i];
		currPoints /= 10;
	}
}

void GameWoManager::setTheGame(std::string fileName, bool isSpecificMap)
//This function allocates new game
{
	theGame = new Game(fileName, isSpecificMap);
	currMap = fileName;
}

void GameWoManager::hideCursor()
//This function hides cursor on the screen
{
	HANDLE myconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CURSOR;
	CURSOR.dwSize = 1;
	CURSOR.bVisible = FALSE;
	SetConsoleCursorInfo(myconsole, &CURSOR);//second argument need pointer
}

bool GameWoManager::samePosition(const Position& creature1Pos, const Position& creature2Pos) const
//This function returns true if the 2 creatures' position is the same
{
	if (creature1Pos == creature2Pos)
			return true;
	return false;
}

void GameWoManager::initGhostPos(Ghost& ghost, char& behindGhost, int initCol, int initRow)
//This function inits the ghost place on the screen
{
	Position currGhostPos = ghost.getPos();
	Position initCell(initCol, initRow);

	Board::gotoxy(currGhostPos.getCol(), currGhostPos.getRow());
	theGame->getGameBoard().setCell(behindGhost, currGhostPos);
	cout << theGame->getGameBoard().getCellFromBoard(currGhostPos);
	behindGhost = theGame->getGameBoard().getCellFromBoard(initCell);
	Board::gotoxy(initCell);
	ghost.setPos(initCell);
	ghost.getPos().draw(ghost.getSign());
}

const string GameWoManager::getNextScreenName() const
//This function returns the name of the right file
{
	if (level == 1)
		return "pacWoman_01.screen";
	else if (level == 2)
		return "pacWoman_02.screen";
	else
		return "pacWoman_03.screen";
}

void GameWoManager::goToNextLevel(int& choice)
//This function starts a new game with the next level
{
	int prevLives = lives;

	if (theGame != nullptr)
		delete theGame;

	currMap = getNextScreenName();
	theGame = new Game(currMap, false); //initial game or restart
	lives = prevLives;
	initStats(lives);
	clearScreen();
	manageGame(choice);
}