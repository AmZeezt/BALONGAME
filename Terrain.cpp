#include "Terrain.h"

using namespace sf;

void Terrain::initVariables()
{
	this->movementSpeed = 5.f;
}

void Terrain::initShape(const RenderWindow& window)
{
	this->shape.setSize(Vector2f(32.f, 32.f));
	this->shape.setPosition(
		static_cast<float>(rand()%window.getSize().x - this->shape.getGlobalBounds().width),
		0.f
	);

	int type = rand() % 5;
	switch (type)
	{
	case 0:
		this->shape.setScale(Vector2f(7.f, 1.f));
		break;
	case 1:
		this->shape.setScale(Vector2f(3.f, 1.f));
		break;
	case 2:
		this->shape.setScale(Vector2f(3.f, 2.f));
		break;
	case 3:
		this->shape.setScale(Vector2f(6.f, 2.f));
		break;
	case 4:
		this->shape.setScale(Vector2f(4.f, 1.f));
		break;
	default:
		break;
	}

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
