#pragma once
#include <vector>
#include <iostream>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Player.h"
#include "Terrain.h"
#include "Background.h"
#include "userInterface.h"
#include "Score.h"
#include "Health.h"

using namespace sf;

class Game
{
private:
	//Window
	RenderWindow* window;
	VideoMode videoMode;
	Event sfmlEvent;
	Texture bird;
	Texture cloud1;
	Texture cloud2;
	Texture cloud3;

	//Game logic
	bool endGame;

	//Terrains
	int terrainSpawnTimer;
	int terrainSpawnTimerMax;

	int maxTerrains;
	int view;
	
	int difficultLevel;
	int gameSpeed;

	//Game objects
	Player* player;
	std::vector<Terrain> terrains;
	Background* background;
	Score* score;
	userInterface ui;
	// make player inherits from health
	Health* health;


	//Private functions
	void initVariables();
	void initWindow();
	void initBackground();
	void initUI();

public:
	//Constructors & Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;
	const bool getEndGame() const;

	//Functions
	void pollEvents();

	//Updaters
	void updateDifLevel();
	void reInitGame();
	void updatePlayer();
	void updateTerrains();
	void updateColision();
	void update();

	//Renderers
	void renderTerrains(RenderTarget* target);
	void render();
};

