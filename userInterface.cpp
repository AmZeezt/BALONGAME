#include "userInterface.h"

userInterface::userInterface()
{
	this->view = 0;
	this->aMUSS = false;
	this->initTextures();
	this->initSprites();
}

userInterface::~userInterface()
{
}

void userInterface::engageAMUSS()
{
	aMUSS = !this->aMUSS;
}

void userInterface::initTextures()
{
	this->gameOverTexture.loadFromFile("textures/x64/ui/game_over.png");
	this->gameOverRestart.loadFromFile("textures/x64/ui/press_enter_to_play.png");
	this->amongUsTexture.loadFromFile("textures/x64/ui/among_us_sus.png");
}

void userInterface::initSprites()
{
	this->gameOverSprite.setTexture(this->gameOverTexture);
	this->gameOverRestartSprite.setTexture(this->gameOverRestart);
	this->amongUsSprite.setTexture(this->amongUsTexture);
	this->gameOverSprite.setPosition(125.f, 160.f);
	this->gameOverSprite.setScale(3.f, 3.f);
	this->amongUsSprite.setScale(3.f, 3.f);
	this->gameOverRestartSprite.setPosition(125.f, 500.f);
	//this->amongUsSprite.setPosition(120.f, 500.f);
}

void userInterface::update(int view)
{
	this->view = view;
}

void userInterface::render(RenderTarget* target)
{
	if (this->view == 0)
	{
		target->draw(this->gameOverRestartSprite);
	}
	else if (this->view == 1)
	{

	}
	else if (this->view == 2) {
		target->draw(this->gameOverSprite);
		target->draw(this->gameOverRestartSprite);
		if (aMUSS) target->draw(this->amongUsSprite);
	}

}