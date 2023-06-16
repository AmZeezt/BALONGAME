#pragma once

#include <SFML/Graphics.hpp>

class Obstacles
{
private:
	sf::Texture texture;
	sf::Sprite sprite;

	float speed;
	int type;

public:
	Obstacles(sf::RenderWindow& window, sf::Texture& texture, float speed, int type);
	virtual ~Obstacles();

	//Accessors
	const sf::Sprite& getSprite() const;

	//Functions
	void fall();
	void update();
	void render(sf::RenderTarget& target);
};
