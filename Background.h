#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Background {
public:
    Background(unsigned movementSpeed);
    virtual ~Background() = default;

    void update(const unsigned level);
    void render(RenderWindow* window);
    void restart();
    void setMovementSpeed(const unsigned& movementSpeed);

private:
    Texture dirt, grass, sky_1, sky_2, sky_3, sky_12, sky_23;
    Sprite sprite;

    unsigned singleOffset;
    unsigned totalOffset;
    unsigned movementSpeed;

    int mediumLevelOffset;
    int highLevelOffset;

    void loadTexture(Texture& texture, const std::string& fileName);
    void selectSprite(const unsigned& rows, const unsigned& row);
    void draw(RenderWindow& window);
};