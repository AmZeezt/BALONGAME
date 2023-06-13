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
	RectangleShape shape;

	float movementSpeed;

	int hp;
	int hpMax;

	void initVariables();
	void initShape();
public:
	Player(float x = 320.f, float y = 320.f);
	virtual ~Player();

	//Functions
	const RectangleShape& getShape() const;

	void updateInput();
	void updateWindowBoundsCollision(const RenderTarget* target);
	void update(const RenderTarget* target);
	void render(RenderTarget* target);
};
