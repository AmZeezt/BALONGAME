#include "Game.h"
using namespace sf;

//Constructors & Destructors
Game::Game() {
	this->initVariables();
	this->initWindow();
}

Game::~Game() {
	//Prevent memory leak ;-)
	delete this->window;
}

const bool Game::running() const
{
	return this->window->isOpen();
}


//Private functions
void Game::initVariables()
{
	this->window = nullptr;
	
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new RenderWindow(this->videoMode, "BALONG", Style::Titlebar | Style::Close);
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

//Updater & Renderer Define
void Game::update()
{
	this->pollEvents();
}

void Game::render()
{
	/*
		Logic
		-> Clear old window [clear()]
		-> Render objects 
		-> Display frame [display()]
	*/

	this->window->clear(Color(255, 0, 0, 255));

	//Draw game object

	this->window->display();
}
