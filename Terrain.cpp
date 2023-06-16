#include "Terrain.h"
#include <iostream>

using namespace sf;

void Terrain::initVariables(float diffLevel, int type)
{
	this->movementSpeed = 10.f * diffLevel;
	this->type = type;
}

void Terrain::initSprite(const Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Terrain::initPosition(const RenderWindow& window)
{
	int randomHelper = rand() % static_cast<int>(window.getSize().x - this->sprite.getGlobalBounds().width);
	if (randomHelper < 320) {
		side = 1;
	}
	else
	{
		side = -1;
	}
	this->sprite.setPosition(
		static_cast<float>(randomHelper),
		-63.f
	);
	if (this->side == 1 && type == 0) sprite.scale(-1, 1);
}

Terrain::Terrain(const RenderWindow& window, const Texture& texture, float diffLevel, int type)
{
	this->initVariables(diffLevel, type);
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

int Terrain::getType()
{
	return this->type;
}

void Terrain::fall()
{
	if (this->type == 0) {
		this->sprite.move((this->movementSpeed * side) / 2, this->movementSpeed);
	}
	else
	{
		this->sprite.move(0.f, this->movementSpeed);
	}
	
}

void Terrain::update()
{
}

void Terrain::render(RenderTarget& target)
{
	target.draw(this->sprite);
}
