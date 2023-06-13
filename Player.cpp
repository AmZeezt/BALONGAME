#include "Player.h"

using namespace sf;

void Player::initVariables()
{
	this->movementSpeed = 5.f;
}

void Player::initShape()
{
	this->shape.setFillColor(Color::Red);
	this->shape.setSize(Vector2f(32.f, 32.f));
}

Player::Player(float x, float y)
{
	//Set player starting position
	this->shape.setPosition(x, y);

	this->initVariables();
	this->initShape();
}

Player::~Player()
{
}

void Player::updateInput()
{
	//Keyboard input
	//Left and Right
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		this->shape.move(-this->movementSpeed, 0.f);
	}
	else if (Keyboard::isKeyPressed(Keyboard::D)) {
		this->shape.move(this->movementSpeed, 0.f);
	}
	//Top and Bottom
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		this->shape.move(0.f , -this->movementSpeed);
	}
	else if (Keyboard::isKeyPressed(Keyboard::S)) {
		this->shape.move(0.f, this->movementSpeed);
	}
}


void Player::update()
{
	//Window bounds collision
	this->updateInput();
}

void Player::render(RenderTarget* target)
{
	target->draw(this->shape);
}
