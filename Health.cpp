#include "Health.h"
#include <math.h>

#define HEART_WIDTH 32

Health::Health(RenderWindow& window, unsigned maxHealth = 3) : window(window), maxHealth(maxHealth), health(maxHealth){
	heart.loadFromFile("textures/x64/hearts/heart.png");
	emptyHeart.loadFromFile("textures/x64/hearts/heart-empty.png");
};

void Health::damage(unsigned damage) {
	health -= damage;

	if (health < 0) {
		health = 0;
	}
}

void Health::heal(unsigned heal) {
	health += heal;

	if (health > maxHealth) {
		health = maxHealth;
	}
}

void Health::reset() {
	health = maxHealth;
}

unsigned Health::getHealth() {
	return health;
}

void Health::render() {
	const unsigned startingPosition = (window.getSize().x / 2) - ((maxHealth * HEART_WIDTH) / 2);

	for (unsigned i = 0; i < maxHealth; i++) {
		sprite.setTexture(i < health ? heart : emptyHeart);
		sprite.setPosition(startingPosition + (i * HEART_WIDTH), 64);
		window.draw(sprite);
	}
}
