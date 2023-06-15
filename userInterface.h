#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;

class userInterface
{
private:
	int view;
	Texture gameOverTexture;
	Texture gameOverRestart;
	Sprite gameOverSprite;
	Sprite gameOverRestartSprite;
public:
	userInterface();
	~userInterface();

	void initTextures();
	void initSprites();
	void update(int view);
	void render(RenderTarget* target);
};