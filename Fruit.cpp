#include "Fruit.h"
#include "Board.h"

using namespace std;

void Fruit::moveFruitPosition(char& direction, char& behindFruit)
//This function gets the fruit direction and handles it
{
	Position currFruitPos = getPos();

	switch (direction)
	{
	case UP_DIR_KEY: case 'W':// UP
	{
		Position upCell(currFruitPos.getCol(), (currFruitPos.getRow() - 1));
		handleFruitCase(upCell, behindFruit);
		break;
	}
	case DOWN_DIR_KEY: case 'X':// DOWN
	{
		Position downCell(currFruitPos.getCol(), (currFruitPos.getRow() + 1));
		handleFruitCase(downCell, behindFruit);
		break;
	}
	case LEFT_DIR_KEY: case 'A':// LEFT
	{
		Position leftCell((currFruitPos.getCol() - 1), currFruitPos.getRow());
		handleFruitCase(leftCell, behindFruit);
		break;
	}
	case RIGHT_DIR_KEY: case 'D':// RIGHT
	{
		Position rightCell((currFruitPos.getCol() + 1), currFruitPos.getRow());
		handleFruitCase(rightCell, behindFruit);
		break;
	}
	default:
		break;
	}
}

void Fruit::handleFruitCase(const Position& nextCell, char& behindFruit)
//This function moves the fruits on the screen to the wanted position
{
	if (!gameBoard.isWall(nextCell) && !gameBoard.isInvisibleWall(nextCell)) // keeps going
	{
		Board::gotoxy(creaturePos.getCol(), creaturePos.getRow());
		gameBoard.setCell(behindFruit, creaturePos);
		cout << gameBoard.getCellFromBoard(creaturePos);
		behindFruit = gameBoard.getCellFromBoard(nextCell);
		Board::gotoxy(nextCell);
		setPos(nextCell);
	}
}

void Fruit::fruitMovement(char& behindFruit, int& fruitStepsCounter)
//This function handles the fruits movements on board
{
	if (fruitStepsCounter <= FRUIT_STEP_PACE && appear == true) //move randomlly on board for FRUIT_STEP_PACE steps
	{
		if (fruitStepsCounter == 1) //new appearance => new value
			value = randomValue();
		moveFruitPosition(direction, behindFruit);
		direction = randNewDirection();
		getPos().draw(getSign());

		if (fruitStepsCounter == FRUIT_STEP_PACE)
		{
			Board::gotoxy(creaturePos.getCol(), creaturePos.getRow());
			gameBoard.setCell(behindFruit, creaturePos);
			cout << gameBoard.getCellFromBoard(creaturePos);
			appear = false;
		}
	}
	else if (fruitStepsCounter > FRUIT_STEP_PACE && fruitStepsCounter <= FRUIT_STEP_PACE + FRUIT_STEP_DISAPPEAR) //dissapear for FRUIT_STEP_DISAPPEAR steps
		if (fruitStepsCounter == FRUIT_STEP_PACE + FRUIT_STEP_DISAPPEAR)
			if (value > 0)
				appear = true;
}
