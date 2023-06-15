#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;
class Player
{
private:
	Sprite sprite;
	Texture texture;

	float movementSpeed;
	int hp;
	int hpMax;

	void initVariables();
	void initSprite();
	void initTexture();
public:
	Player(float x = 280.f, float y = 320.f);
	virtual ~Player();

	//Functions
	const Sprite& getSprite() const;

	int getPlayerHp();
	void lowerPlayerHp();
	void move();
	void updateWindowBoundsCollision(const RenderTarget* target);
	void update(const RenderTarget* target);
	void render(RenderTarget* target);
};
