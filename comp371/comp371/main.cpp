#include "Game.h"
#include <iostream>

using namespace std;

int main()
{
	Game::getInstance()->init();
	Game::getInstance()->mainLoop();

	return 0;
}