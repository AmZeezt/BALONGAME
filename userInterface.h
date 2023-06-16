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
	bool aMUSS;
	Texture gameOverTexture;
	Texture gameOverRestart;
	Texture amongUsTexture;
	Sprite gameOverSprite;
	Sprite gameOverRestartSprite;
	Sprite amongUsSprite;
public:
	userInterface();
	~userInterface();

	void engageAMUSS();
	void initTextures();
	void initSprites();
	void update(int view);
	void render(RenderTarget* target);
};