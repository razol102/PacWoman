#include "GameWoManager.h"
#include "Game.h"
using namespace std;

int main()
{
	GameWoManager pacGame;	
	int choice;
	char userMenuSelect, userMove;
	srand(std::time(nullptr)); // seed the random number generator
	pacGame.getMainMenu().getMenuChoice(choice);
	if (choice != EXIT)
		pacGame.manageGame(choice);
	return 0;
}
