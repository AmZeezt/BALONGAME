#include "Score.h"
#include <math.h>

#define DIGIT_WIDTH 32

Score::Score(RenderWindow& window, unsigned initialScore) : window(window), score(initialScore) {
	digit1.loadFromFile("textures/x64/digits/1.png");
	digit2.loadFromFile("textures/x64/digits/2.png");
	digit3.loadFromFile("textures/x64/digits/3.png");
	digit4.loadFromFile("textures/x64/digits/4.png");
	digit5.loadFromFile("textures/x64/digits/5.png");
	digit6.loadFromFile("textures/x64/digits/6.png");
	digit7.loadFromFile("textures/x64/digits/7.png");
	digit8.loadFromFile("textures/x64/digits/8.png");
	digit9.loadFromFile("textures/x64/digits/9.png");
	digit0.loadFromFile("textures/x64/digits/0.png");
};

void Score::update(unsigned increment) {
	score += increment;
}

void Score::reset() {
	score = 0;
}

unsigned Score::getScore() {
	return score;
}

void Score::render() {
	const unsigned numberOfDigits = score == 0 ? 1 : (ceil((int)log10(score) + 1) + 1);
	const unsigned scoreWidth = numberOfDigits * DIGIT_WIDTH;
	const unsigned startingPosition = (window.getSize().x / 2) + (scoreWidth / 2);

	unsigned digit = score * 10;

	for (unsigned i = 0; i < numberOfDigits; i++) {
		setDigitTexture(digit % 10);
		sprite.setPosition(startingPosition - ((i + 1) * DIGIT_WIDTH), 14);
		window.draw(sprite);
		digit /= 10;
	}
}

void Score::setDigitTexture(const unsigned& digit) {
	switch (digit) {
		case 0:
			sprite.setTexture(digit0);
			break;
		case 1:
			sprite.setTexture(digit1);
			break;
		case 2:
			sprite.setTexture(digit2);
			break;
		case 3:
			sprite.setTexture(digit3);
			break;
		case 4:
			sprite.setTexture(digit4);
			break;
		case 5:
			sprite.setTexture(digit5);
			break;
		case 6:
			sprite.setTexture(digit6);
			break;
		case 7:
			sprite.setTexture(digit7);
			break;
		case 8:
			sprite.setTexture(digit8);
			break;
		case 9:
			sprite.setTexture(digit9);
			break;
		default:
			sprite.setTexture(digit0);
			break;
	}
}