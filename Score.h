#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Score {
public:
    Score(RenderWindow& window, unsigned initialScore);
    virtual ~Score() = default;

    void update(unsigned increment);
    void reset();
    void render();
    unsigned getScore() ;

private:
    RenderWindow& window;
    Texture digit1, digit2, digit3, digit4, digit5, digit6, digit7, digit8, digit9, digit0;
    Sprite sprite;

    unsigned score;

    void setDigitTexture(const unsigned& digit);
};