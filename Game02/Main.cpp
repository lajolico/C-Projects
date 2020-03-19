#include "Game.h"

/*
Author: warsoldier011
PURPOSE: Simple Click and Attack Game
*/


int main() 
{
	//Init the random
	std::srand(static_cast<unsigned int>(time(NULL)));

	Game game;

	while (game.isRunning())
	{
		//update Game loop
		game.update();

		//Render objects
		game.render();
	}

	//Return 0 = End of Application	
	return 0;
}




