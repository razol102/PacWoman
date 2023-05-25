#ifndef __MENU_H
#define __MENU_H

#include <iostream>
#include <vector>
#include <string>
class GameWoManager;

const int FIRST_MAP = 1, SECOND_MAP = 2, THIRD_MAP = 3;

class Menu
{
	GameWoManager& pacWomanGame;
public:
	Menu(GameWoManager& game):pacWomanGame(game){}
	Menu(const Menu& other):pacWomanGame(other.pacWomanGame) {}

	GameWoManager& getPacWomanGame() { return pacWomanGame; }

	void printMenu() const;
	void printInstruction() const;
	bool hasEnding(std::string const& fullString, std::string const& ending);
	void listDir(const std::string& path, std::vector<std::string>& files, const std::string& suffix);
	bool activateMenuSelect(int& select);
	void getMenuChoice(int& choice);
	bool gameEnded(bool& endTheGame, int& choice);
	void generateMap(const std::string & mapName, int mapNumber, int& choice);

	void operator=(const Menu& other) {}
};
#endif

