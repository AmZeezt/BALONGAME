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

	void initVariables(float diffLevel);
	void initSprite(const Texture& texture);
	void initPosition(const RenderWindow& window);
public:
	Terrain(const RenderWindow& window, const Texture& texture, float diffLevel);
	virtual ~Terrain();

	//Functions
	const Sprite& getSprite() const;
	void fall();
	void update();
	void render(RenderTarget& target);
};

