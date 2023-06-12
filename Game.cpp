#include "Game.h"
using namespace sf;

//Constructors & Destructors
Game::Game() {
	this->initVariables();
	this->initWindow();
	this->initEnemies();
}

Game::~Game() {
	//Prevent memory leak ;-)
	delete this->window;
}

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
	this->health = 1;
	this->enemySpawnTimerMax = 20.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 50;
	this->mouseHeld = false;
}

void Game::initWindow()
{
	this->videoMode.height = 800;
	this->videoMode.width = 600;

	this->window = new RenderWindow(this->videoMode, "BALONG", Style::Titlebar | Style::Close);

	this->window->setFramerateLimit(60);
}

void Game::initEnemies()
{
	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setSize(Vector2f(32.f, 32.f));
	this->enemy.setScale(Vector2f(1.f, 1.f));
	this->enemy.setFillColor(Color::Cyan);
	//this->enemy.setOutlineColor(Color::Green);
	//this->enemy.setOutlineThickness(1.f);
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

	this->enemy.setFillColor(Color::Green);

	//Spawn the enemy
	this->enemies.push_back(this->enemy);
}

void Game::updateEnemies()
{
	/*
		Updates the enemy spawn timer and spawns enemies
		when the total amount of enemies is smaller than the max.
		Moves the enemies downwards
		Removes enemies at the edge of the screen. //TODO
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
					std::cout << "Points " << this->points << " Health " << this->health << "\n";
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
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type) {
		case Event::Closed:
			this->window->close();
			break;
		case Event::KeyPressed:
			if (this->ev.key.code == Keyboard::Escape)
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
		this->updateEnemies();
	}

	//Endgame condition
	if (this->health <= 0)
		this->endGame = true;

}

void Game::renderEnemies()
{
	for (auto& e : this->enemies) {
		this->window->draw(e);
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
	this->renderEnemies();

	this->window->display();
}
