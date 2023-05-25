#ifndef __POSITION_H
#define __POSITION_H

#include <iostream>
#include "stdbool.h"

class Position
{
	int col, row;
public:
	Position(int col = 1, int row = 1) : col(col), row(row) {}

	int getCol() const {return col;}
	int getRow() const { return row; }

	void setPoint(int col, int row);
	void setPoint(const Position& newPos);

	void draw(char ch);

	bool operator==(const Position& other) const;
	void operator=(const Position& other);
};
#endif