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

using namespace sf;
/*
	Game Engine
*/

class Game
{
private:
	//Private Variables
	//Window
	RenderWindow* window;
	VideoMode videoMode;
	Event sfmlEvent;
	Texture bird;
	Texture cloud1;
	Texture cloud2;
	Texture cloud3;
	Texture gameOverTexture;
	Texture gameOverRestart;

	//Resources
	Font font;

	//Text
	Text uiText;


	//Game logic
	bool endGame;
	unsigned points;

	//Terrains
	float terrainSpawnTimer;
	float terrainSpawnTimerMax;
	int maxTerrains;

	//Game objects
	Player player;
	std::vector<Terrain> terrains;
	Sprite gameOverSprite;
	Sprite gameOverRestartSprite;

	//Private functions
	void initVariables();
	void initWindow();
	void initFonts();
	void initText();
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
	void updateText();
	void updatePlayer();
	void updateTerrains();
	void updateColision();
	void update();

	//Renderers
	void renderText(RenderTarget* target);
	void renderTerrains(RenderTarget* target);
	void render();
};

