#include "Ghost.h"
#include "Position.h"
#include "Board.h"

using namespace std;

void Ghost::moveGhostPosition(char& direction, char& behindGhost)
//This function gets the ghost direction and handles it
{
	Position currGhostPos = getPos();

	switch (direction)
	{
	case UP_DIR_KEY: case 'W':// UP
	{
		Position upCell(currGhostPos.getCol(), (currGhostPos.getRow() - 1));
		handleGhostCase(upCell, currGhostPos, behindGhost);
		break;
	}
	case DOWN_DIR_KEY: case 'X':// DOWN
	{
		Position downCell(currGhostPos.getCol(), (currGhostPos.getRow() + 1));
		handleGhostCase(downCell, currGhostPos, behindGhost);
		break;
	}
	case LEFT_DIR_KEY: case 'A':// LEFT
	{
		Position leftCell((currGhostPos.getCol() - 1), currGhostPos.getRow());
		handleGhostCase(leftCell, currGhostPos, behindGhost);
		break;
	}
	case RIGHT_DIR_KEY: case 'D':// RIGHT
	{
		Position rightCell((currGhostPos.getCol() + 1), currGhostPos.getRow());
		handleGhostCase(rightCell, currGhostPos, behindGhost);
		break;
	}
	default:
		break;
	}
}

void Ghost::handleGhostCase(const Position& nextCell, Position& currGhostPos, char& behindGhost)
//This function moves the ghost on the screen to the wanted position
{
	if (!gameBoard.isWall(nextCell) && !gameBoard.isInvisibleWall(nextCell)) // keeps going
	{
		Board::gotoxy(currGhostPos.getCol(), currGhostPos.getRow());
		gameBoard.setCell(behindGhost, currGhostPos);
		cout << gameBoard.getCellFromBoard(currGhostPos);
		behindGhost = gameBoard.getCellFromBoard(nextCell);
		Board::gotoxy(nextCell);
		setPos(nextCell);
	}
}

bool Ghost::smarterGhostsHandle(const char gameLevel, char& ghostsDir, char& behindGhosts, int& stepsCounter, int ghostsCounter, const Position& pacPos)
//This function handles the smarter ghosts directions and moves on the screen
//This function returns true is we need to add 1 to stepsCounter
{
	switch (gameLevel)
	{
	case BEST:
	{
		ghostsDir = getCloserToPacDir(pacPos);
		moveGhostPosition(ghostsDir, behindGhosts);
		getPos().draw(getSign());
		break;
	}
	case GOOD:
	{
		if (stepsCounter == STEP_PACE)
		{
			moveGhostPosition(ghostsDir, behindGhosts);
			ghostsDir = randNewDirection();
			getPos().draw(getSign());

			if(ghostsCounter == gameBoard.getGhostsInitPosVec().size())
				stepsCounter = 1; 
		}
		else if (stepsCounter <= STAY_IN_DIR)
		{
			moveGhostPosition(ghostsDir, behindGhosts);
			getPos().draw(getSign());
			return true;
		}
		else
		{
			ghostsDir = getCloserToPacDir(pacPos);
			moveGhostPosition(ghostsDir, behindGhosts);
			getPos().draw(getSign());
			return true;
		}
		break;
	}
	case NOVICE:
	{
		if (stepsCounter == STEP_PACE)
		{
			moveGhostPosition(ghostsDir, behindGhosts);
			ghostsDir = randNewDirection();
			getPos().draw(getSign());

			if (ghostsCounter == gameBoard.getGhostsInitPosVec().size())
				stepsCounter = 0; 
		}
		else
		{
			moveGhostPosition(ghostsDir, behindGhosts);
			getPos().draw(getSign());
		}
		return true;
		break;
	}
	}
}

const char Ghost::getCloserToPacDir(const Position& pacPos)
//This function is getting the ghosts chasing the pacWoman
{
	DIR_DECISION desicion[DIRECTIONS];
	desicionArrInit(desicion, pacPos);

	// Find the minimum distance and return the corresponding direction
	int minDistance = desicion[0].distance;
	char bestDirection = UP_DIR_KEY;  // UP

	for (int i = 1; i < DIRECTIONS; i++)
	{
		if (desicion[i].distance < minDistance && !gameBoard.isWall(desicion[i].nextCell) && !gameBoard.isInvisibleWall(desicion[i].nextCell))
		{
			minDistance = desicion[i].distance;
			bestDirection = desicion[i].dir;
		}
	}
	return bestDirection;
}

void Ghost::desicionArrInit(DIR_DECISION desicion[], const Position& pacPos)
//This function inits direction desicion array
{
	int pacRowPos = pacPos.getRow(), pacColPos = pacPos.getCol();
	int ghostRowPos = creaturePos.getRow(), ghostColPos = creaturePos.getCol();

	desicion[0].distance = abs(ghostColPos - pacColPos) + abs(ghostRowPos - pacRowPos - 1); // Up
	desicion[0].nextCell = Position(ghostColPos, (ghostRowPos - 1)); // Up
	desicion[0].dir = UP_DIR_KEY; // Up
	desicion[1].distance = abs(ghostColPos - pacColPos) + abs(ghostRowPos - pacRowPos + 1); // Down
	desicion[1].nextCell = Position(ghostColPos, (ghostRowPos + 1)); // Down
	desicion[1].dir = DOWN_DIR_KEY; // Down
	desicion[2].distance = abs(ghostColPos - pacColPos - 1) + abs(ghostRowPos - pacRowPos); // Left
	desicion[2].nextCell = Position((ghostColPos - 1), ghostRowPos); // Left
	desicion[2].dir = LEFT_DIR_KEY; // Left
	desicion[3].distance = abs(ghostColPos - pacColPos + 1) + abs(ghostRowPos - pacRowPos); // Right
	desicion[3].nextCell = Position((ghostColPos + 1), ghostRowPos); // Right
	desicion[3].dir = RIGHT_DIR_KEY; // Right
}