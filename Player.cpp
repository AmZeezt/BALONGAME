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

void Player::updateWindowBoundsCollision(const RenderTarget* target)
{
	//Player position
	FloatRect playerBounds = this->shape.getGlobalBounds();

	//TODO: corner positions fix

	//Left Colision
	if (playerBounds.left <= 0.f)
		this->shape.setPosition(0.f, playerBounds.top);
	//Right Colision
	else if (playerBounds.left + playerBounds.width >= target->getSize().x)
		this->shape.setPosition(target->getSize().x - playerBounds.width, playerBounds.top);
	//Top Colision
	if (playerBounds.top <= 0.f)
		this->shape.setPosition(playerBounds.left, 0.f);
	//Bottom Colision
	else if (playerBounds.top + playerBounds.height >= target->getSize().y)
		this->shape.setPosition(playerBounds.left, target->getSize().y - playerBounds.height);
}


void Player::update(const RenderTarget* target)
{
	//Window bounds collision
	this->updateInput();
	this->updateWindowBoundsCollision(target);
}

void Player::render(RenderTarget* target)
{
	target->draw(this->shape);
}
