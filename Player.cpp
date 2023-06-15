#include "Player.h"

using namespace sf;

void Player::initVariables()
{
	this->movementSpeed = 5.f;
	this->hpMax = 10;
	this->hp = this->hpMax;
}

void Player::initSprite()
{
	this->sprite.setTexture(this->texture);
}

void Player::initTexture()
{
	//Load texture from file
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
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{
}

const RectangleShape& Player::getShape() const
{
	return this->shape;
}

int Player::getPlayerHp()
{
	return this->hp;
}

void Player::lowerPlayerHp()
{
	this->hp--;
}

void Player::updateInput()
{
	//Keyboard input
	//Left and Right
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		this->shape.move(-this->movementSpeed, 0.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		this->shape.move(this->movementSpeed, 0.f);
	}
	//Top and Bottom
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		this->shape.move(0.f , -this->movementSpeed);
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		this->shape.move(0.f, this->movementSpeed);
	}
}

void Player::updateWindowBoundsCollision(const RenderTarget* target)
{
	//Player position

	//Left Colision
	if (this->shape.getGlobalBounds().left <= 0.f)
		this->shape.setPosition(0.f, this->shape.getGlobalBounds().top);
	//Right Colision
	if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x)
		this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);
	//Top Colision
	if (this->shape.getGlobalBounds().top <= 0.f)
		this->shape.setPosition(this->shape.getGlobalBounds().left, 0.f);
	//Bottom Colision
	if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y)
		this->shape.setPosition(this->shape.getGlobalBounds().left, target->getSize().y - this->shape.getGlobalBounds().height);
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
	// target->draw(this->sprite);
}
