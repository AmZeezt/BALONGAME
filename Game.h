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

	//Mouse positions
	Vector2i mousePosWindow;
	Vector2f mousePosView;

	//Resources
	Font font;

	//Text
	Text uiText;


	//Game logic
	bool endGame;
	unsigned points;
	int health;
	//Enemies (TO DELETE)
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	//Terrains
	float terrainSpawnTimer;
	float terrainSpawnTimerMax;
	int maxTerrains;
	bool mouseHeld;

	//Game objects
	Player player;
	std::vector<Terrain> terrains;
	std::vector<RectangleShape> enemies;
	RectangleShape enemy;
	Background* background;

	//Private functions
	void initVariables();
	void initWindow();
	void initFonts();
	void initText();
	void initEnemies();
	void init_background();
public:
	//Constructors & Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;
	const bool getEndGame() const;

	//Functions
	void spawnEnemy();
	void pollEvents();

	//Updaters
	void updateMousePosition();
	void updateText();
	void updateEnemies();
	void updateTerrains();
	void updateColision();
	void update();

	//Renderers
	void renderText(RenderTarget* target);
	void renderEnemies(RenderTarget* target);
	void renderTerrains(RenderTarget* target);
	void render();
};

