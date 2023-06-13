#include <iostream>
#include "Game.h"

using namespace sf;

int main() {

	//Init srand
	std::srand(static_cast<unsigned>(time(0)));

	//Init Game engine
	Game game;

	//Game loop
	while (game.running() && !game.getEndGame())
	{
		//Update
		game.update();

		//Render
		game.render();
	}


	//Proper close
	return 0;
}