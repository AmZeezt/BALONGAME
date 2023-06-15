#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Health {
public:
    Health(RenderWindow& window, unsigned maxHealth);
    virtual ~Health() = default;

    void damage(unsigned damage);
    void heal(unsigned heal);
    void reset();
    void render();
    unsigned getHealth();

private:
    RenderWindow& window;
    Texture heart, emptyHeart;
    Sprite sprite;
     
    unsigned maxHealth;
    unsigned health;
};