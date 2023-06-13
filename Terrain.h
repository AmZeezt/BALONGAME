#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;

class Terrain
{
private:
	RectangleShape shape;

	float movementSpeed;

	void initVariables();
	void initShape(const RenderWindow& window);
public:
	Terrain(const RenderWindow& window);
	virtual ~Terrain();

	//Functions
	const RectangleShape& getShape() const;
	void fall();
	void update();
	void render(RenderTarget& target);
};

