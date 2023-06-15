#include "Game.h"
#include <sstream>
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
	points = 0;
	health = 1000; // TODO: CHANGE
	//Enemies (TO DELETE)
	enemySpawnTimerMax = 25.f;
	enemySpawnTimer = enemySpawnTimerMax;
	maxEnemies = 20;
	//Terrains
	terrainSpawnTimerMax = 25.f;
	terrainSpawnTimer = terrainSpawnTimerMax;
	maxTerrains = 20;

	mouseHeld = false;
}

void Game::initFonts()
{
	if (!font.loadFromFile("VT323/VT323-Regular.ttf")) std::cout << "FONT LOAD ERROR initFonts()";
}

void Game::initText()
{
	uiText.setFont(font);
	uiText.setCharacterSize(32);
	uiText.setFillColor(Color::White);
	uiText.setString("NONE");
}

void Game::initWindow()
{
	videoMode.height = 800;
	videoMode.width = 640;

	window = new RenderWindow(videoMode, "BALONG", Style::Titlebar | Style::Close);

	window->setFramerateLimit(60);
}

void Game::initEnemies()
{
	enemy.setPosition(10.f, 10.f);
	enemy.setSize(Vector2f(32.f, 32.f));
	enemy.setScale(Vector2f(1.f, 1.f));
	enemy.setFillColor(Color::Green);
	//enemy.setOutlineColor(Color::Green);
	//enemy.setOutlineThickness(1.f);
}

//Constructors & Destructors
Game::Game() {
	initVariables();
	initWindow();
	initFonts();
	initText();
	initEnemies();
	init_background();
}

Game::~Game() {
	//Prevent memory leak ;-)
	delete window;
}

void Game::init_background() {
	try {
		background = new Background(*window, 2, 50, 120);
	}
	catch (const std::runtime_error& e) {
		std::cerr << "Caught exception: " << e.what() << '\n';
	}
}

void Game::spawnEnemy()
{
	/*
		Spawns enemies and sets their colors and positions.
		-Sets random position.
		-Sets random color.
		-Adds enemy to vector.
	*/

	enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(window->getSize().x - enemy.getSize().x)),
		0.f
	);

	//Randomize blocks
	int type = rand() % 5;
	switch (type)
	{
	case 0:
		enemy.setScale(Vector2f(2.f, 1.f));
		break;
	case 1:
		enemy.setScale(Vector2f(3.f, 1.f));
		break;
	case 2:
		enemy.setScale(Vector2f(3.f, 2.f));
		break;
	case 3:
		enemy.setScale(Vector2f(6.f, 2.f));
		break;
	case 4:
		enemy.setScale(Vector2f(4.f, 1.f));
		break;
	default:
		break;
	}

	enemy.setFillColor(Color::Green);

	//Spawn the enemy
	enemies.push_back(enemy);
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
	if (terrainSpawnTimer < terrainSpawnTimerMax) {
		terrainSpawnTimer += 1.f;
	}
	else {
		if (terrains.size() < maxTerrains) {
			terrains.push_back(Terrain(*window));
			terrainSpawnTimer += 0.f;
		}
		
	}

	//Moving and updating enemies
	//for (int i = 0; i < terrains.size(); i++) {
	//	enemies[i].move(0.f, 3.f);
	//	if (enemies[i].getPosition().y > window->getSize().y) {
	//		terrains.erase(terrains.begin() + i);
	//		health -= 1;
	//		std::cout << "Health " << health << "\n";
	//	}
	//}
}

void Game::updateColision()
{
	//Check colision
	for (size_t i = 0; i < terrains.size(); i++)
	{
		if (player.getShape().getGlobalBounds().intersects(terrains[i].getShape().getGlobalBounds())) {
			terrains.erase(terrains.begin() + i);
		}
	}
	
}

void Game::updateText()
{
	std::stringstream ss;

	ss << "Points: " << points << " " << "Health: " << health << "\n";

	uiText.setString(ss.str());
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
	if (enemies.size() < maxEnemies) {
		if (enemySpawnTimer >= enemySpawnTimerMax)
		{
			//Spawn the enemy and reset the timer
			spawnEnemy();
			enemySpawnTimer = 0.f;
		}
		else
			enemySpawnTimer += 1.f;
	}

	//Moving and updating enemies
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i].move(0.f, 3.f);
		if (enemies[i].getPosition().y > window->getSize().y) {
			enemies.erase(enemies.begin() + i);
			health -= 1;
			std::cout << "Health " << health << "\n";
		}
	}

	//Check if clicked upon
	if (Mouse::isButtonPressed(Mouse::Left)) {
		if(mouseHeld == false) {
			mouseHeld = true;
			bool deleted = false;
			for (size_t i = 0; i < enemies.size() && deleted == false; i++)
			{
				if (enemies[i].getGlobalBounds().contains(mousePosView)) {
					deleted = true;
					enemies.erase(enemies.begin() + i);

					//Gain points
					points += 1.f;
					std::cout << "Points " << points << "\n";
				}
			}
		} 
	}
	else
	{
		mouseHeld = false;
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

	mousePosWindow = Mouse::getPosition(*window);
	mousePosView = window->mapPixelToCoords(mousePosWindow);
}


//Updater & Renderer Define
void Game::update()
{
	pollEvents();

	//End game check
	if (!endGame) {
		//Update mouse position
		updateMousePosition();
		updateText();
		player.update(window);
		updateTerrains();
		updateEnemies();
		updateColision();
		//updateTerrains();
	}

	//Endgame condition
	if (health <= 0)
		endGame = true;

}

void Game::renderText(RenderTarget* target)
{
	target->draw(uiText);
}

void Game::renderEnemies(RenderTarget* target)
{
	for (auto& e : enemies) {
		target->draw(e);
	}
}

void Game::renderTerrains(RenderTarget* target) {
	for (auto i : terrains) {
		i.render(*window);
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

	window->clear();

	background->update();
	points++;

	//Draw game object
	player.render(window);

	renderEnemies(window);

	renderTerrains(window);

	renderText(window);

	window->display();
}
