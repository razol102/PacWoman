#include "Position.h"
#include "Game.h"
#include "Board.h"

using namespace std;

void Position::setPoint(int col, int row)
//This function sets new point
{
	this->col = col;
	this->row = row;
}

void Position::setPoint(const Position& newPos)
//This function sets new point
{
	col = newPos.getCol();
	row = newPos.getRow();
}

void Position::draw(char ch)
//This function puts the sent char on the visited place in the board
{
	Board::gotoxy(col, row);
	cout << ch;
	cout.flush();
}

void Position::operator=(const Position& other)
//operator= for position
{
	col = other.col;
	row = other.row;
}

bool Position::operator==(const Position& other) const
//operator== between 2 positions
{
	if (other.col == col && other.row == row)
		return true;
	return false;
}
