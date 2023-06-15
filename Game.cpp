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
	this->points = 0;
	this->view = 0;
	//Terrains
	this->terrainSpawnTimerMax = 25.f;
	this->terrainSpawnTimer = this->terrainSpawnTimerMax;
	this->maxTerrains = 20;

	//Textures

	this->bird.loadFromFile("textures/x64/obstacles/bird.png");
	this->cloud1.loadFromFile("textures/x64/obstacles/cloud-1.png");
	this->cloud2.loadFromFile("textures/x64/obstacles/cloud-2.png");
	this->cloud3.loadFromFile("textures/x64/obstacles/cloud-3.png");


}

void Game::initFonts()
{
	if (!this->font.loadFromFile("VT323/VT323-Regular.ttf")) std::cout << "FONT LOAD ERROR initFonts()" << "\n";
}

void Game::initText()
{
	//Points and Lives
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(32);
	this->uiText.setFillColor(Color::White);
	this->uiText.setString("");
}

void Game::initBackground() {
	try {
		background = new Background(*window, 2, 50, 120);
	}
	catch (const std::runtime_error& e) {
		std::cerr << "Caught exception: " << e.what() << '\n';
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
	initVariables();
	initWindow();
	initFonts();
	initText();
	initBackground();
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
				this->terrains.push_back(Terrain(*this->window, this->bird));
			} else if (type <= 16) {
				this->terrains.push_back(Terrain(*this->window, this->cloud1));
			} else if (type <= 45) {
				this->terrains.push_back(Terrain(*this->window, this->cloud2));
			} else {
				this->terrains.push_back(Terrain(*this->window, this->cloud3));
			}
			this->points += 1;
			std::cout << "Points " << this->points << "\n";
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
		if (this->player.getSprite().getGlobalBounds().intersects(this->terrains[i].getSprite().getGlobalBounds())) {
			this->terrains.erase(this->terrains.begin() + i);
			this->player.lowerPlayerHp();
			std::cout << "Health " << this->player.getPlayerHp() << "\n";
		}
	}
	
}

void Game::updateText()
{
	std::stringstream ss;

	ss << "Points: " << this->points << " " << "Health: " << this->player.getPlayerHp() << "\n";

	this->uiText.setString(ss.str());
}

void Game::updatePlayer()
{
	this->player.update(this->window);
	if (this->player.getPlayerHp() <= 0) {
		this->endGame = true;
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
			if (this->sfmlEvent.key.code == Keyboard::Enter)
				if (this->view == 0) {
					this->view = 1;
				}
			break;
		}
	}
}



//Updater & Renderer Define
void Game::update()
{
	this->pollEvents();

	//End game check
	if (this->view == 0) {
		userInterface.update(view);
	}
	else if (this->view == 1) {
		if (!this->endGame) {
			//Update mouse position
			this->updateText();
			this->updatePlayer();
			this->updateTerrains();
			background->update();
			this->updateColision();
			userInterface.update(view);
		}
	}
	else if (this->view == 2) {
		userInterface.update(view);
	}
	

	//Endgame condition
	if (this->player.getPlayerHp() <= 0) {
		this->endGame = true;
		this->view = 2;
	}
		

}

void Game::renderText(RenderTarget* target)
{
	target->draw(this->uiText);
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

	player.render(window);

	renderTerrains(window);

	renderText(window);

	userInterface.render(window);

	window->display();
}
