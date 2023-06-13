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
	this->health = 20;
	//Enemies (TO DELETE)
	this->enemySpawnTimerMax = 25.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 20;
	//Terrains
	this->terrainSpawnTimerMax = 25.f;
	this->terrainSpawnTimer = this->terrainSpawnTimerMax;
	this->maxTerrains = 20;

	this->mouseHeld = false;
}

void Game::initFonts()
{
	if (!this->font.loadFromFile("VT323/VT323-Regular.ttf")) std::cout << "FONT LOAD ERROR initFonts()";
}

void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(32);
	this->uiText.setFillColor(Color::White);
	this->uiText.setString("NONE");
}

void Game::initWindow()
{
	this->videoMode.height = 800;
	this->videoMode.width = 640;

	this->window = new RenderWindow(this->videoMode, "BALONG", Style::Titlebar | Style::Close);

	this->window->setFramerateLimit(60);
}

void Game::initEnemies()
{
	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setSize(Vector2f(32.f, 32.f));
	this->enemy.setScale(Vector2f(1.f, 1.f));
	this->enemy.setFillColor(Color::Green);
	//this->enemy.setOutlineColor(Color::Green);
	//this->enemy.setOutlineThickness(1.f);
}

//Constructors & Destructors
Game::Game() {
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
	this->initEnemies();

}

Game::~Game() {
	//Prevent memory leak ;-)
	delete this->window;
}

void Game::spawnEnemy()
{
	/*
		Spawns enemies and sets their colors and positions.
		-Sets random position.
		-Sets random color.
		-Adds enemy to vector.
	*/

	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);

	//Randomize blocks
	int type = rand() % 5;
	switch (type)
	{
	case 0:
		this->enemy.setScale(Vector2f(2.f, 1.f));
		break;
	case 1:
		this->enemy.setScale(Vector2f(3.f, 1.f));
		break;
	case 2:
		this->enemy.setScale(Vector2f(3.f, 2.f));
		break;
	case 3:
		this->enemy.setScale(Vector2f(6.f, 2.f));
		break;
	case 4:
		this->enemy.setScale(Vector2f(4.f, 1.f));
		break;
	default:
		break;
	}

	this->enemy.setFillColor(Color::Green);

	//Spawn the enemy
	this->enemies.push_back(this->enemy);
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
	if (this->terrainSpawnTimer < this->terrainSpawnTimerMax) {
		this->terrainSpawnTimer += 1.f;
	}
	else {
		if (this->terrains.size() < this->maxTerrains) {
			this->terrains.push_back(Terrain(*this->window));
			this->terrainSpawnTimer += 0.f;
		}
		
	}

	//Moving and updating enemies
	//for (int i = 0; i < this->terrains.size(); i++) {
	//	this->enemies[i].move(0.f, 3.f);
	//	if (this->enemies[i].getPosition().y > this->window->getSize().y) {
	//		this->terrains.erase(this->terrains.begin() + i);
	//		this->health -= 1;
	//		std::cout << "Health " << this->health << "\n";
	//	}
	//}
}

void Game::updateColision()
{
	//Check colision
	for (size_t i = 0; i < this->terrains.size(); i++)
	{
		if (this->player.getShape().getGlobalBounds().intersects(this->terrains[i].getShape().getGlobalBounds())) {
			this->terrains.erase(this->terrains.begin() + i);
		}
	}
	
}

void Game::updateText()
{
	std::stringstream ss;

	ss << "Points: " << this->points << " " << "Health: " << this->health << "\n";

	this->uiText.setString(ss.str());
}


void Game::updateEnemies()
{
	/*
		Updates the enemy spawn timer and spawns enemies
		when the total amount of enemies is smaller than the max.
		Moves the enemies downwards
		Removes enemies at the edge of the screen.
	*/

	//Updating the timer for enemy spawning
	if (this->enemies.size() < this->maxEnemies) {
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			//Spawn the enemy and reset the timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	//Moving and updating enemies
	for (int i = 0; i < this->enemies.size(); i++) {
		this->enemies[i].move(0.f, 3.f);
		if (this->enemies[i].getPosition().y > this->window->getSize().y) {
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
			std::cout << "Health " << this->health << "\n";
		}
	}

	//Check if clicked upon
	if (Mouse::isButtonPressed(Mouse::Left)) {
		if(this->mouseHeld == false) {
			this->mouseHeld = true;
			bool deleted = false;
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);

					//Gain points
					this->points += 1.f;
					std::cout << "Points " << this->points << "\n";
				}
			}
		} 
	}
	else
	{
		this->mouseHeld = false;
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
			break;
		}
	}
}

void Game::updateMousePosition()
{
	/*
		Update mouse position
		-> Relative to window
	*/

	this->mousePosWindow = Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}


//Updater & Renderer Define
void Game::update()
{
	this->pollEvents();

	//End game check
	if (!this->endGame) {
		//Update mouse position
		this->updateMousePosition();
		this->updateText();
		this->player.update(this->window);
		this->updateTerrains();
		this->updateEnemies();
		this->updateColision();
		//this->updateTerrains();
	}

	//Endgame condition
	if (this->health <= 0)
		this->endGame = true;

}

void Game::renderText(RenderTarget* target)
{
	target->draw(this->uiText);
}

void Game::renderEnemies(RenderTarget* target)
{
	for (auto& e : this->enemies) {
		target->draw(e);
	}
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

	this->window->clear();

	//Draw game object
	this->player.render(this->window);

	this->renderEnemies(this->window);

	this->renderTerrains(this->window);

	this->renderText(this->window);

	this->window->display();
}
