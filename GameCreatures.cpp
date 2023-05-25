#include "GameCreatures.h"

char GameCreatures::randNewDirection()
//This function rands new direction for the ghost
{
	char arrowKeys[] = "adwxs";
	int range = sizeof(arrowKeys) / sizeof(char);
	char randomChar = arrowKeys[rand() % (range - 1)];
	return randomChar;
}

void GameCreatures::operator=(const GameCreatures& other)
//operator =
{
	this->creaturePos = other.creaturePos;
	this->direction = other.direction;
}
