#include "Game.h"
#include <sstream>

#define DEFAULT_DIFFICULTY 1
#define DEFAULT_GAME_SPEED 5
#define MEDIUM_GAME_SPEED 7
#define HARD_GAME_SPEED 9
#define DEFAULT_TERRAIN_SPAWN_TIMER 25


using namespace sf;

//Accesors
const bool Game::running() const
{
	return window->isOpen();
}

const bool Game::getEndGame() const
{
	return endGame;
}


//functions
void Game::initVariables()
{
	window = nullptr;
	//Game logic
	endGame = false;
	//Terrains
	terrainSpawnTimerMax = DEFAULT_TERRAIN_SPAWN_TIMER;
	terrainSpawnTimer = terrainSpawnTimerMax;
	maxTerrains = 20;
	view = 0;

	difficultLevel = DEFAULT_DIFFICULTY;
	gameSpeed = DEFAULT_GAME_SPEED;

	//Textures
	bird.loadFromFile("textures/x64/obstacles/bird.png");
	cloud1.loadFromFile("textures/x64/obstacles/cloud-1.png");
	cloud2.loadFromFile("textures/x64/obstacles/cloud-2.png");
	cloud3.loadFromFile("textures/x64/obstacles/cloud-3.png");
}

void Game::initBackground() {
	try {
		background = new Background(2);
	}
	catch (const std::runtime_error& e) {
		std::cerr << "Caught exception: " << e.what() << '\n';
	}
}

void Game::initUI() {
	try {
		const unsigned maxHp = 5;

		score = new Score(*window, 0);
		health = new Health(*window, maxHp);
		player->setMaxHp(maxHp);
	}
	catch (const std::runtime_error& e) {
		std::cerr << "Caught exception in initializing UI: " << e.what() << '\n';
	}
}

void Game::initWindow()
{
	videoMode.height = 800;
	videoMode.width = 640;

	window = new RenderWindow(videoMode, "BALONG", Style::Titlebar | Style::Close);

	window->setFramerateLimit(30);
}

//Constructors & Destructors
Game::Game() {
	player = new Player();
	initVariables();
	initWindow();
	initBackground();
	initUI();
}

Game::~Game() {
	delete window;
}

void Game::updateTerrains()
{
	/*
		Updates the terrain spawn timer and spawns terrain
		when the total amount of terrain is smaller than the max.
		Moves the terrain downwards
		Removes terrain at the edge of the screen.
	*/

	//Updating the timer for terrain spawning

	if (terrains.size() < maxTerrains) {
		if (terrainSpawnTimer >= terrainSpawnTimerMax)
		{
			//Spawn the enemy and reset the timer
			int type = rand() % 100;

			if (type <= 8) {
				terrains.push_back(Terrain(*window, bird, gameSpeed, 0));
			} else if (type <= 16) {
				terrains.push_back(Terrain(*window, cloud1, gameSpeed, 1));
			}
			else if (type <= 45) {
				terrains.push_back(Terrain(*window, cloud2, gameSpeed, 1));
			}
			else if (type <= 50) {
				terrains.push_back(Terrain(*window, cloud2, gameSpeed, 0));
			}
			else if (type <= 65) {
				terrains.push_back(Terrain(*window, cloud3, gameSpeed, 0));
			}
			else {
				terrains.push_back(Terrain(*window, cloud3, gameSpeed, 1));
			}
			score->update(1);
			terrainSpawnTimer = 0.f;
		}
		else
			terrainSpawnTimer += 1.f;
	}
	

	//Moving and updating enemies
	for (int i = 0; i < terrains.size(); i++) {
		terrains[i].fall();
		if (terrains[i].getSprite().getPosition().y > (window->getSize().y + 128)) {
			terrains.erase(terrains.begin() + i);
		}
	}
}

void Game::updateColision()
{
	//Check colision
	for (size_t i = 0; i < terrains.size(); i++)
	{
		if (player->getSprite().getGlobalBounds().intersects(terrains[i].getSprite().getGlobalBounds())) {
			terrains.erase(terrains.begin() + i);
			player->lowerPlayerHp();
			health->damage(1);
		}
	}
	
}

void Game::updateDifLevel()
{
	switch (score->getScore())
	{
	case 64:
		difficultLevel = 2;
		gameSpeed = MEDIUM_GAME_SPEED;
		terrainSpawnTimerMax = 22;
		background->setMovementSpeed(MEDIUM_GAME_SPEED);
		break;
	case 128:
		difficultLevel = 3;
		gameSpeed = HARD_GAME_SPEED;
		terrainSpawnTimerMax = 21;
		background->setMovementSpeed(HARD_GAME_SPEED);
		break;
	case 256:
		gameSpeed = HARD_GAME_SPEED + 3;
		terrainSpawnTimerMax = 29;
		break;
	case 512:
		gameSpeed = HARD_GAME_SPEED + 7;
		terrainSpawnTimerMax = 17;
		break;
	default:
		break;
	}
}

void Game::reInitGame()
{	
	difficultLevel = DEFAULT_DIFFICULTY;
	gameSpeed = DEFAULT_GAME_SPEED;
	terrainSpawnTimer = DEFAULT_TERRAIN_SPAWN_TIMER;

	terrains.clear();

	score->reset();
	health->reset();
	player->reset();
	background->setMovementSpeed(DEFAULT_GAME_SPEED);
	background->restart();
}

void Game::updatePlayer()
{
	player->update(window);

	if (health->getHealth() <= 0 ) {
		endGame = true;
	}
}

void Game::pollEvents()
{
	//Event polling
	while (window->pollEvent(sfmlEvent))
	{
		switch (sfmlEvent.type) {
		case Event::Closed:
			window->close();
			break;
		case Event::KeyPressed:
			if (sfmlEvent.key.code == Keyboard::Escape)
				window->close();
			if (sfmlEvent.key.code == Keyboard::Enter) {
				if (view == 0) {
					view = 1;
				}
				if (view == 2) {
					view = 1;
					reInitGame();
				}
			}
			if (sfmlEvent.key.code == Keyboard::K)
				ui.engageAMUSS();
			break;
		}
	}
}

//Updater & Renderer Define
void Game::update()
{
	pollEvents();

	//Game flow
	if (view == 0) {
		ui.update(view);
	}
	else if (view == 1)
	{
		updateDifLevel();
		updatePlayer();
		updateTerrains();
		background->update(difficultLevel);
		updateColision();
		ui.update(view);
	}
	else if (view == 2)
	{
		ui.update(view);
	}

	//Endgame condition
	if (health->getHealth() <= 0) {
		view = 2;
		endGame = true;
	}
}

void Game::renderTerrains(RenderTarget* target) {
	for (auto i : terrains) {
		i.render(*window);
	}
}

void Game::render()
{
	window->clear();

	//Draw game object
	background->render(window);

	player->render(window);

	renderTerrains(window);

	ui.render(window);

	score->render();
	health->render();

	window->display();
}
