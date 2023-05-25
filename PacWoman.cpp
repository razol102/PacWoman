#include "PacWoman.h"
#include "Position.h"
#include "Board.h"

using namespace std;

void PacWoman::movePacPosition(char direction, int& countPoints)
//This function gets the pacWoman direction and handles it
{
	switch (direction)
	{
	case LEFT_DIR_KEY: case 'A':// LEFT
	{
		Position leftCell((getPos().getCol() - 1), getPos().getRow());
		handlePacCase(leftCell, countPoints, gameBoard.getGameCols() - 3, getPos().getRow());
		break;
	}
	case RIGHT_DIR_KEY: case 'D':// RIGHT
	{
		Position rightCell((getPos().getCol() + 1), getPos().getRow());
		handlePacCase(rightCell, countPoints, 1, getPos().getRow());
		break;
	}
	case UP_DIR_KEY: case 'W':// UP
	{
		Position upCell(getPos().getCol(), (getPos().getRow() - 1));
		handlePacCase(upCell, countPoints, getPos().getCol(), gameBoard.getGameRows() - 2);
		break;
	}
	case DOWN_DIR_KEY: case 'X':// DOWN
	{
		Position downCell(getPos().getCol(), (getPos().getRow() + 1));
		handlePacCase(downCell, countPoints, getPos().getCol(), 1);
		break;
	}
	case STAY_KEY: case 'S':// STAY
		break;
	default:
		break;
	}
}

void PacWoman::handlePacCase(const Position& nextCell, int& countPoints, int tunnelCol, int tunnelRow)
//This function moves the pacWoman on the screen to the wanted position
{
	Sleep(PAC_SPEED);

	if (!gameBoard.isWall(nextCell))
	{
		if (gameBoard.isInvisibleWall(nextCell))
		{
			Board::gotoxy(getPos().getCol(), getPos().getRow());
			gameBoard.setCell(' ', getPos());
			cout << gameBoard.getCellFromBoard(getPos());
			Board::gotoxy(tunnelCol, tunnelRow);
			getPos().setPoint(tunnelCol, tunnelRow);
		}
		else // keeps going
		{
			if (gameBoard.isBreadCrumbs(nextCell))
				countPoints++;
			Board::gotoxy(getPos().getCol(), getPos().getRow());
			gameBoard.setCell(' ', getPos());
			cout << gameBoard.getCellFromBoard(getPos());
			getPos().setPoint(nextCell);
		}
	}
	else
		movePacPosition(STAY_KEY, countPoints);
}