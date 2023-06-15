#include "Terrain.h"
#include <iostream>

using namespace sf;

void Terrain::initVariables()
{
	this->movementSpeed = 10.f;
}

void Terrain::initSprite(const Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Terrain::initPosition(const RenderWindow& window)
{
	this->sprite.setPosition(
		static_cast<float>(rand() % static_cast<int>(window.getSize().x - this->sprite.getGlobalBounds().width)),
		-63.f
	);
}

Terrain::Terrain(const RenderWindow& window, const Texture& texture)
{
	this->initVariables();
	this->initSprite(texture);
	this->initPosition(window);
}

Terrain::~Terrain()
{
}


const Sprite& Terrain::getSprite() const
{
	return this->sprite;
}

void Terrain::fall()
{
	this->sprite.move(0.f, this->movementSpeed);
}

void Terrain::update()
{
}

void Terrain::render(RenderTarget& target)
{
	target.draw(this->sprite);
}
