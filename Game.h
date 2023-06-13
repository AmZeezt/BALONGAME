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

	Player player;

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
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;

	//Game objects
	std::vector<RectangleShape> enemies;
	RectangleShape enemy;

	//Private functions
	void initVariables();
	void initWindow();
	void initFonts();
	void initText();
	void initEnemies();
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
	void update();

	//Renderers
	void renderText(RenderTarget* target);
	void renderEnemies(RenderTarget* target);
	void render();
};

