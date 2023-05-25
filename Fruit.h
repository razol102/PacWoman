#ifndef __FRUIT_H
#define __FRUIT_H

#include "GameCreatures.h"
#include <iostream>

const int FIRST_VALUE = 5;
const int INIT_FRUIT_AMOUNT = 2;
const int FRUIT_STEP_PACE = 100, FRUIT_STEP_DISAPPEAR = 50;

class Fruit: public GameCreatures
{
	int value = FIRST_VALUE;
	bool appear = true;
public:
	Fruit(Board& board, char dir = RIGHT_DIR_KEY) :GameCreatures(board, dir) { sign = value + '0'; }

	const int randomValue() { return (rand() % FIRST_VALUE + FIRST_VALUE); }
	int getValue() const { return value; }
	bool getAppear() const { return appear; }
	void setAppear(bool isAppear) { appear = isAppear; }
	void setValue(int newVal) { value = newVal; }
	char getSign() const { return value + '0'; }

	void moveFruitPosition(char& direction, char& behindFruit);
	void handleFruitCase(const Position& nextCell, char& behindFruit);
	void fruitMovement(char& behindFruit, int& fruitStepsCounter);
};
#endif
