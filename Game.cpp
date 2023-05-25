#include "Game.h"
#include "Position.h"
#include "Board.h"
#include "Ghost.h"

using namespace std;

Game::Game(const string& fileName, bool isSpecificMap) : gameBoard(fileName), pac(gameBoard)
//Constructor
{
	int boardSize = gameBoard.getBoard().size();
	pac.getPos() = gameBoard.getInitPacPos();

	ghostsAmount = gameBoard.getGhostsInitPosVec().size();
	for (int i = 0; i < ghostsAmount; i++)
	{
		ghostsVec.push_back(Ghost(gameBoard));
		ghostsVec[i].setPos(gameBoard.getGhostsInitPosVec()[i]);
	}

	for (int i = 0; i < INIT_FRUIT_AMOUNT; i++)
	{
		fruitsVec.push_back(Fruit(gameBoard));
		fruitsVec[i].setPos(gameBoard.getFruitsInitPosVec()[i]);
		gameBoard.setCell(fruitsVec[i].getValue(), fruitsVec[i].getPos());
	}
	fruitsAmount = INIT_FRUIT_AMOUNT;

	setArrowKeys("adwxs");
	isSpecificMapGame = isSpecificMap;
}

void Game::setArrowKeys(const char* keys)
//This function set the arrowKeys array
{
	for (int i = 0; i < KEYSIZE; i++)
		arrowKeys[i] = keys[i];
}

void Game::runGame(int flag, int& countPoints, char& pacDir, vector<char>& behindGhosts, vector<char>& behindFruits, vector<char>& ghostsDir, int& ghostStepsCounter, int& fruitStepsCounter, const char gameLevel)
//This function controls the pacWoman and ghost movements
{
	char dirBeforeESC = pacDir;
	bool esc = false, needToAdd = false;

    if (_kbhit())
	{
		pacDir = _getch();
		if (isValidDirection(pacDir))
			pac.setDirection(pacDir);

		if (pacDir == ESC)
		{
			pac.setDirection(STAY_KEY);
			pac.movePacPosition(pac.getDirection(), countPoints);

			while (esc == false)
				if (_kbhit())
				{
					pacDir = _getch();
					if (pacDir == ESC)
						esc = true;
				}
			pacDir = dirBeforeESC;
			pac.setDirection(dirBeforeESC);
			pac.movePacPosition(pac.getDirection(), countPoints);
		}
	}
	pac.movePacPosition(pac.getDirection(), countPoints);
	pac.getPos().draw(pac.getSign());
	Sleep(PAC_SPEED);

	if (flag == 1)
	{
		for (int i = 0; i < ghostsAmount; i++)
			needToAdd = ghostsVec[i].smarterGhostsHandle(gameLevel, ghostsDir[i], behindGhosts[i], ghostStepsCounter, i + 1, pac.getPos());

		for (int i = 0; i < fruitsAmount; i++)
			fruitsVec[i].fruitMovement(behindFruits[i], fruitStepsCounter);

		if (fruitStepsCounter == FRUIT_STEP_PACE + FRUIT_STEP_DISAPPEAR)
			fruitStepsCounter = 0;

		fruitStepsCounter++;

		if (needToAdd)
			ghostStepsCounter++;
	}	
}

bool Game::isValidDirection(char direction) const
//This function returns true is the direction is valid
{
	if (direction != RIGHT_DIR_KEY && direction != 'D' && direction != LEFT_DIR_KEY && direction != 'A' && direction != UP_DIR_KEY && direction != 'W' && direction != DOWN_DIR_KEY && direction != 'X' && direction != STAY_KEY && direction != 'S')
		return false;
	return true;
}