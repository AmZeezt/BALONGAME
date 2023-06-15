#include "Player.h"
#include <iostream>

using namespace sf;

void Player::initVariables()
{
	this->movementSpeed = 10.f;
	this->hpMax = 1;
	this->hp = this->hpMax;
}

void Player::initSprite()
{
	//Set texture
	this->sprite.setTexture(this->texture);

	//Set scale
	this->sprite.scale(1.f, 1.f);
}

void Player::initTexture()
{
	//Load texture from file
	if (!this->texture.loadFromFile("textures/x64/player/balloon-1.png"))
		std::cout << "TEXTURE LOAD ERROR initTexture()" << "\n";
}


Player::Player(float x, float y)
{
	//Set player starting position
	this->sprite.setPosition(x, y);
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{
}

const Sprite& Player::getSprite() const
{
	return this->sprite;
}

int Player::getPlayerHp()
{
	return this->hp;
}

void Player::lowerPlayerHp()
{
	this->hp--;
}

void Player::move()
{
	//Keyboard input

	if (Keyboard::isKeyPressed(Keyboard::A)) {
		this->sprite.move(-this->movementSpeed, 0.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		this->sprite.move(this->movementSpeed, 0.f);
	}
	//Top and Bottom
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		this->sprite.move(0.f , -this->movementSpeed);
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		this->sprite.move(0.f, this->movementSpeed);
	}
}

void Player::updateWindowBoundsCollision(const RenderTarget* target)
{
	//Player position

	//Left Colision
	if (this->sprite.getGlobalBounds().left <= 0.f)
		this->sprite.setPosition(0.f, this->sprite.getGlobalBounds().top);
	//Right Colision
	if (this->sprite.getGlobalBounds().left + this->sprite.getGlobalBounds().width >= target->getSize().x)
		this->sprite.setPosition(target->getSize().x - this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().top);
	//Top Colision
	if (this->sprite.getGlobalBounds().top <= 0.f)
		this->sprite.setPosition(this->sprite.getGlobalBounds().left, 0.f);
	//Bottom Colision
	if (this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height >= target->getSize().y)
		this->sprite.setPosition(this->sprite.getGlobalBounds().left, target->getSize().y - this->sprite.getGlobalBounds().height);
}


void Player::update(const RenderTarget* target)
{
	//Window bounds collision
	this->move();
	this->updateWindowBoundsCollision(target);
}

void Player::render(RenderTarget* target)
{
	target->draw(this->sprite);
	// target->draw(this->sprite);
}
