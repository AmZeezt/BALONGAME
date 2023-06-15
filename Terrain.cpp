#include "Terrain.h"
#include <iostream>

using namespace sf;

void Terrain::initVariables()
{
	this->movementSpeed = 5.f;
}

void Terrain::initShape(const RenderWindow& window)
{
	int type = rand() % 5;
	switch (type)
	{
	case 0:
		this->shape.setSize(Vector2f(256.f, 32.f));
		break;
	case 1:
		this->shape.setSize(Vector2f(128.f, 32.f));
		break;
	case 2:
		this->shape.setSize(Vector2f(128.f, 64.f));
		break;
	case 3:
		this->shape.setSize(Vector2f(128.f, 32.f));
		break;
	case 4:
		this->shape.setSize(Vector2f(256.f, 64.f));
		break;
	default:
		break;
	}

	float test = static_cast<float>(rand() % window.getSize().x - this->shape.getGlobalBounds().width);

	std::cout << test << "\n";

	this->shape.setPosition(
		test,
		0.f
	);

	

	this->shape.setFillColor(Color::Green);
}

Terrain::Terrain(const RenderWindow& window)
{
	this->initVariables();
	this->initShape(window);
}

Terrain::~Terrain()
{
}


const RectangleShape& Terrain::getShape() const
{
	return this->shape;
}

void Terrain::fall()
{
	this->shape.move(0.f, this->movementSpeed);
}

void Terrain::update()
{
}

void Terrain::render(RenderTarget& target)
{
	target.draw(this->shape);
}
