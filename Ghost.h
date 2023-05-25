#ifndef __GHOST_H
#define __GHOST_H

#include "GameCreatures.h"
class Position;

const char BEST = LEFT_DIR_KEY, GOOD = 'b', NOVICE = 'c';
const int STEP_PACE = 19;
const int STAY_IN_DIR = 5;

typedef struct dirDesicion
{
	int distance;
	Position nextCell;
	char dir;

}DIR_DECISION;


class Ghost : public GameCreatures
{
public:
	Ghost(Board& board, char dir = RIGHT_DIR_KEY) : GameCreatures(board, dir) { sign = GHOST_SIGN; }
	void moveGhostPosition(char& direction, char& behindGhost);
	void handleGhostCase(const Position& nextCell, Position& currGhostPos, char& behindGhost);
	bool smarterGhostsHandle(const char gameLevel, char& ghostsDir, char& behindGhosts, int& stepsCounter, int ghostsCounter, const Position& pacPos);
	const char getCloserToPacDir(const Position& pacPos);
	void desicionArrInit(DIR_DECISION desicion[], const Position& pacPos);
};
#endif