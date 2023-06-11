#include <iostream>
#include "Game.h"

using namespace sf;

int main() {

	//Init Game engine
	Game game;

	//Game loop
	while (game.running())
	{
		//Update
		game.update();

		//Render
		game.render();
	}


	//Proper close
	return 0;
}