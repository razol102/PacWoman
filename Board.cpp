#include "Board.h"
#include <string>
#include <random>
#include "Fruit.h"

using namespace std;

Board::Board(const string& fileName)
//constructor
{
	ifstream inFile(fileName);
	string line;
	int i = 0, cols = 0, rows = 0;

	while (getline(inFile, line))
	{
		while (line[i] != '\0') 
		{
			board.push_back(line[i]);
			i++;
			if (rows == 0)
				cols++;
		}
		rows++;
		i = 0;
		board.push_back('\n');
	}
	cols++;
	this->rows = rows;
	this->cols = cols;
	board.resize(rows * cols);
	setCurrentGameBoard();

	setFruitOnBoard();
	inFile.close();
}

void Board::setFruitOnBoard()
//This function sets the fruits on the board 
{
	int randRow, randCol, fruitsLeft = INIT_FRUIT_AMOUNT;

	while (fruitsLeft > 0)
	{
		randRow = 1 + rand() % (rows - 1);
		randCol = 1 + rand() % (cols - 1);
		Position randPos(randCol, randRow);
		if (getCellFromBoard(randPos) == BREADCRUMB_SIGN || getCellFromBoard(randPos) == ' ')
		{
			fruitsInitPosVec.push_back(randPos);
			fruitsLeft--;
		}
	}
}

void Board::setCurrentGameBoard()
//This function turns the symbols in the given board to the original game symbols
{
	int currRow = 0, currCol = 0, boardSize = board.size();

	for (int i = 0; i < boardSize; i++)
	{
		if (board[i] == '\n')
		{
			currRow++;
			currCol = 0;
		}
		if (board[i] == ' ')
		{
			board[i] = BREADCRUMB_SIGN;
			maxBreadCrumbs++;
		}
		else if (board[i] == INIT_PAC_POS)
		{
			board[i] = PACWOMAN_SIGN;
			initPacPos.setPoint(Position(currCol - 1, currRow));
		}
		else if (board[i] == INIT_GHOST_POS && ghostsInitPosVec.size() <= MAX_GHOSTS)
		{
			board[i] = GHOST_SIGN;
			ghostsInitPosVec.push_back(Position(currCol - 1, currRow));
			maxBreadCrumbs++;
		}
		else if (board[i] == EMPTY_POS && (currRow == 0 || currRow == rows - 1 || currCol == 1 || currCol == cols - 1))
			board[i] = INVISIBLEWALL_SIGN;
		else if (board[i] == EMPTY_POS)
			board[i] = ' ';

		currCol++;
	}
}

bool Board::isWall(const Position& pos) const
//This function returns true if the next place the character headed to is a wall
{
	char cell = getCellFromBoard(pos);

	if (cell == WALL_SIGN)
		return true;
	return false;
}

bool Board::isInvisibleWall(const Position& pos) const
//This function returns true if the next place the character headed to is an invisible wall
{
	char posChar = getCellFromBoard(pos);

	if (posChar == INVISIBLEWALL_SIGN)
		return true;
	return false;
}

void Board::gotoxy(int x, int y)
//This function moves the cursor on the screen
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout << flush;
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

void Board::gotoxy(const Position& pos)
//This function moves the cursor on the screen
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout << flush;
	dwCursorPosition.X = pos.getCol();
	dwCursorPosition.Y = pos.getRow();
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

bool Board::isBreadCrumbs(const Position& pos) const
//This function returns true if the next place the character headed to is a bread crumbs
{
	char cell = getCellFromBoard(pos);

	if (cell == BREADCRUMB_SIGN)
		return true;
	return false;
}


