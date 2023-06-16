#include "Terrain.h"
#include <iostream>
#include <math.h>

using namespace sf;

void Terrain::initVariables(int speed, int type)
{
	movementSpeed = ceil(speed * 1.3f) - 1;
	type = type;
}

void Terrain::initSprite(const Texture& texture)
{
	sprite.setTexture(texture);
}

void Terrain::initPosition(const RenderWindow& window)
{
	int randomHelper = rand() % static_cast<int>(window.getSize().x - sprite.getGlobalBounds().width);
	if (randomHelper < 320) {
		side = 1;
	}
	else
	{
		side = -1;
	}
	sprite.setPosition(
		static_cast<float>(randomHelper),
		-63.f
	);
	if (side == 1 && type == 0) sprite.scale(-1, 1);
}

Terrain::Terrain(const RenderWindow& window, const Texture& texture, int speed, int type)
{
	initVariables(speed, type);
	initSprite(texture);
	initPosition(window);
}

Terrain::~Terrain()
{
}


const Sprite& Terrain::getSprite() const
{
	return sprite;
}

int Terrain::getType()
{
	return type;
}

void Terrain::fall()
{
	if (type == 0) {
		sprite.move((movementSpeed * side) / 2, movementSpeed);
	}
	else
	{
		sprite.move(0.f, movementSpeed);
	}
	
}

void Terrain::update()
{
}

void Terrain::render(RenderTarget& target)
{
	target.draw(sprite);
}
