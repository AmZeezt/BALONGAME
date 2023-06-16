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
	Sprite sprite;
	Texture texture;

	float movementSpeed;
	int type;
	int side;

	void initVariables(int speed, int type);
	void initSprite(const Texture& texture);
	void initPosition(const RenderWindow& window);
public:
	Terrain(const RenderWindow& window, const Texture& texture, int speed, int type);
	virtual ~Terrain();

	//Functions
	const Sprite& getSprite() const;
	int getType();
	void fall();
	void update();
	void render(RenderTarget& target);
};

