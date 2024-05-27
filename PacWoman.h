#ifndef __PACWOMAN_H
#define __PACWOMAN_H

#include "GameCreatures.h"

const int PAC_SPEED = 102;

class PacWoman : public GameCreatures
{
public:
	PacWoman(Board& board, char dir = STAY_KEY) : GameCreatures(board, dir) { sign = PACWOMAN_SIGN; }

	void movePacPosition(char direction, int& countPoints);
	void handlePacCase(const Position& nextCell, int& countPoints, int tunnelCol, int tunnelRow);
};
#endif

