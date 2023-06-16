#include "Game.h"
#include <sstream>
using namespace sf;

//Accesors
const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}


//functions
void Game::initVariables()
{
	this->window = nullptr;
	//Game logic
	this->endGame = false;
	//Terrains
	this->terrainSpawnTimerMax = 25.f;
	this->terrainSpawnTimer = this->terrainSpawnTimerMax;
	this->maxTerrains = 20;
	this->view = 0;
	this->diffLevel = 1.f;

	//Textures
	this->bird.loadFromFile("textures/x64/obstacles/bird.png");
	this->cloud1.loadFromFile("textures/x64/obstacles/cloud-1.png");
	this->cloud2.loadFromFile("textures/x64/obstacles/cloud-2.png");
	this->cloud3.loadFromFile("textures/x64/obstacles/cloud-3.png");
}

void Game::initBackground() {
	try {
		background = new Background(*window, 2, 50, 120);
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
	this->videoMode.height = 800;
	this->videoMode.width = 640;

	this->window = new RenderWindow(this->videoMode, "BALONG", Style::Titlebar | Style::Close);

	this->window->setFramerateLimit(30);
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
	//Prevent memory leak ;-)
	delete this->window;
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

	if (this->terrains.size() < this->maxTerrains) {
		if (this->terrainSpawnTimer >= this->terrainSpawnTimerMax)
		{
			//Spawn the enemy and reset the timer
			int type = rand() % 100;

			if (type <= 8) {
				this->terrains.push_back(Terrain(*this->window, this->bird, this->diffLevel));
			} else if (type <= 16) {
				this->terrains.push_back(Terrain(*this->window, this->cloud1, this->diffLevel));
			} else if (type <= 45) {
				this->terrains.push_back(Terrain(*this->window, this->cloud2, this->diffLevel));
			} else {
				this->terrains.push_back(Terrain(*this->window, this->cloud3, this->diffLevel));
			}
			score->update(1);
			this->terrainSpawnTimer = 0.f;
		}
		else
			this->terrainSpawnTimer += 1.f;
	}
	

	//Moving and updating enemies
	for (int i = 0; i < this->terrains.size(); i++) {
		this->terrains[i].fall();
		if (this->terrains[i].getSprite().getPosition().y > (this->window->getSize().y + 128)) {
			this->terrains.erase(this->terrains.begin() + i);
		}
	}
}

void Game::updateColision()
{
	//Check colision
	for (size_t i = 0; i < this->terrains.size(); i++)
	{
		if (this->player->getSprite().getGlobalBounds().intersects(this->terrains[i].getSprite().getGlobalBounds())) {
			this->terrains.erase(this->terrains.begin() + i);
			this->player->lowerPlayerHp();
			health->damage(1);
		}
	}
	
}

void Game::updateDifLevel()
{
	switch (this->score->getScore())
	{
	case 64:
		this->diffLevel = 1.2f;
		this->terrainSpawnTimerMax = 22.f;
		break;
	case 128:
		this->diffLevel = 1.5f;
		this->terrainSpawnTimerMax = 20.f;
		break;
	case 256:
		this->diffLevel = 1.8f;
		this->terrainSpawnTimerMax = 18.f;
		break;
	case 512:
		this->diffLevel = 2.f;
		this->terrainSpawnTimerMax = 15.f;
		break;
	default:
		break;
	}
}

void Game::reInitGame()
{
	this->score->reset();
	this->health->reset();
	this->player->reset();
	this->diffLevel = 1.f;
	this->terrainSpawnTimer = 25.f;
	this->terrains.clear();
	this->background->restart();
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
	while (this->window->pollEvent(this->sfmlEvent))
	{
		switch (this->sfmlEvent.type) {
		case Event::Closed:
			this->window->close();
			break;
		case Event::KeyPressed:
			if (this->sfmlEvent.key.code == Keyboard::Escape)
				this->window->close();
			if (this->sfmlEvent.key.code == Keyboard::Enter) {
				if (this->view == 0) {
					this->view = 1;
				}
				if (this->view == 2) {
					this->view = 1;
					this->reInitGame();
				}
			}
			break;
		}
	}
}

//Updater & Renderer Define
void Game::update()
{
	this->pollEvents();

	//Game flow
	if (this->view == 0) {
		userInterface.update(view);
	}
	else if (this->view == 1)
	{
		this->updateDifLevel();
		this->updatePlayer();
		this->updateTerrains();
		background->update();
		this->updateColision();
		userInterface.update(view);
	}
	else if (this->view == 2)
	{
		userInterface.update(view);
	}

	//Endgame condition
	if (health->getHealth() <= 0)
		this->view = 2;
		this->endGame = true;

}

void Game::renderTerrains(RenderTarget* target) {
	for (auto i : this->terrains) {
		i.render(*this->window);
	}
}

void Game::render()
{
	/*
		Logic
		-> Clear old window [clear()]
		-> Render objects 
		-> Display frame [display()]
	*/

	// Bruh, you don't need this-> at the beggining if you're reffering 
	// to class owned variable/method, you use this only when the method 
	// you're in  takes argument of the same name as the class variable 
	// then you use this-> to differenciate between one another

	window->clear();

	//Draw game object
	background->render();

	player->render(window);

	renderTerrains(window);

	userInterface.render(window);

	score->render();
	health->render();

	window->display();
}
