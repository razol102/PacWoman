#include "Menu.h"
#include "Game.h"
#include <filesystem>
#include <fstream>
#include <algorithm>
#include "GameWoManager.h"

namespace fs = std::filesystem;
using namespace std;

void Menu::printMenu() const
//This function prints the main menu of the game 
{
	cout << "Welcome to pacWoman MTA!" << endl
		<< "Please choose one of the following:" << endl
		<< "(1) Start a new game" << endl
		<< "(2) Upload specific map" << endl
		<< "(8) Present instructions and keys" << endl
		<< "(9) EXIT" << endl;
}

void Menu::printInstruction() const
//This function prints the game instructions
{
	cout << "Let's get started!\nYou are playing PacWoman game, that's because girls run the world:)" << endl;
	cout << "You have to collect all the bread crumbs on the game board in order to win the game." << endl;
	cout << "While you do that you also need to figure out a way to avoid all those ghosts that are coming to get you.." << endl;
	cout << "LEFT........................................................ a or A" << endl;
	cout << "RIGHT....................................................... d or D" << endl;
	cout << "UP.......................................................... w or W" << endl;
	cout << "DOWN........................................................ x or X" << endl;
	cout << "STAY........................................................ s or S" << endl;
	cout << endl << "Press any key to return to the menu" << endl << endl;
}

bool Menu::hasEnding(string const& fullString, string const& ending) 
{
	if (fullString.length() >= ending.length())
		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	else
		return false;
}

void Menu::listDir(const string& path, vector<string>& files, const string& suffix)
//This function gets the files names from the file
{
	for (const auto& entry : fs::directory_iterator(path))
		if (hasEnding(entry.path().string(), suffix))
			files.push_back(entry.path().string());
}

bool Menu::activateMenuSelect(int& choice)
//This function gets the user's choice to the main menu and activate it
{
	vector<string> files;
	listDir(".", files, "screen");
	sort(files.begin(), files.end());
	bool activated = true;

	switch (choice)
	{
	case NEW_GAME:
	{
		if (pacWomanGame.getTheGame() != nullptr)
			delete pacWomanGame.getTheGame();
		pacWomanGame.setTheGame(files[0], false); //initial game or restart
		pacWomanGame.initStats(MAX_LIVES);
		pacWomanGame.clearScreen();
		pacWomanGame.manageGame(choice);
		break;
	}
	case MAP_CHOICE:
	{
		int mapChoice;
		pacWomanGame.clearScreen();

		cout << "Please insert a specific map (1-3): ";
		cin >> mapChoice;

		if (mapChoice == FIRST_MAP)
			generateMap(files[0], FIRST_MAP, choice);
		else if (mapChoice == SECOND_MAP)
			generateMap(files[1], SECOND_MAP, choice);
		else if (mapChoice == THIRD_MAP)
			generateMap(files[2], THIRD_MAP, choice);
		else
		{
			cout << "Invalid choice, returninig to main menu." << endl << endl;
			printMenu();
			activated = false;
		}
		break;
	}
	case INSTRUCTION:
	{
		char c;
		pacWomanGame.clearScreen();
		printInstruction();
		c = _getch();
		pacWomanGame.clearScreen();
		getMenuChoice(choice);
		break;
	}
	case EXIT:
	{
		pacWomanGame.clearScreen();
		cout << "GoodBye!" << endl;
		break;
	}
	default:
	{
		cout << "Invalid choice, please try again: ";
		activated = false;
		break;
	}
	}
	return activated;
}

void Menu::getMenuChoice(int& choice)
//This function gets the user's menu choice and call activateMenuSelect function
{
	printMenu();
	cin >> choice;

	while (!activateMenuSelect(choice))
		cin >> choice;
}

bool Menu::gameEnded(bool& endTheGame, int& choice)
//This function is being called when the user loses the game or wining it
{
	bool isGameEnded = true;
	pacWomanGame.clearScreen();

	if (pacWomanGame.getLives() == 0) //all lives are over
	{
		cout << "Game Over" << endl;
		endTheGame = true;
	}
	else if (pacWomanGame.getLevel() == MAX_SCREENS) //all levels are done
	{
		cout << "Well done! YOU WON!" << endl;
		endTheGame = true;
	}
	else if (!pacWomanGame.getTheGame()->getIsSpecificMapGame()) //if we are'nt in a specific map game
	{
		cout << "HOORAY! You have passed level " << pacWomanGame.getLevel() << endl;
		cout << "You are mooving to the next stage";
		pacWomanGame.setLevel(pacWomanGame.getLevel() + 1);
		isGameEnded = false;
		endTheGame = false;
	}
	
	cout << endl << "Press any key to continue." << endl << endl;
	cin.clear();
	char c = _getch();
	pacWomanGame.clearScreen();
	return isGameEnded;
}

void Menu::generateMap(const string& mapName, int mapNumber, int& choice)
//This function generates a specific map
{
	if (pacWomanGame.getTheGame() != nullptr)
		delete pacWomanGame.getTheGame();

	pacWomanGame.clearScreen();
	pacWomanGame.setTheGame(mapName, true);
	pacWomanGame.setLevel(mapNumber);
	pacWomanGame.initStats(MAX_LIVES);
	pacWomanGame.manageGame(choice);
}