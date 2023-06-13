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

	void initVariables();
	void initShape();
public:
	Player(float x = 320.f, float y = 320.f);
	virtual ~Player();

	void updateInput();
	void update();
	void render(RenderTarget* target);
};

