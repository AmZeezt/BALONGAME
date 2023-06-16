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
	float posStartX, posStartY;

	void initVariables();
	void initSprite();
	void initTexture();
public:
	Player(int maxHealth = 5, float x = 287.f, float y = 320.f);
	virtual ~Player();

	//Functions
	const Sprite& getSprite() const;

	void setMaxHp(int maxHp);
	int getPlayerHp();
	void reset();
	void lowerPlayerHp();
	void move();
	void updateWindowBoundsCollision(const RenderTarget* target);
	void update(const RenderTarget* target);
	void render(RenderTarget* target);
};
