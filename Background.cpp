#include "Background.h"
#include <math.h>

using namespace std;

#define TILE_SIZE 64

Background::Background(sf::RenderWindow& window, unsigned movementSpeed, int mediumLevelOffset, int highLevelOffset)
    : window(window), movementSpeed(movementSpeed), singleOffset(0), totalOffset(0), mediumLevelOffset(mediumLevelOffset), highLevelOffset(highLevelOffset){

    loadTexture(dirt, "textures/x64/background/dirt.png");
    loadTexture(grass, "textures/x64/background/grass.png");
    loadTexture(sky_1, "textures/x64/background/sky-1.png");
    loadTexture(sky_2, "textures/x64/background/sky-2.png");
    loadTexture(sky_3, "textures/x64/background/sky-3.png");
    loadTexture(sky_12, "textures/x64/background/sky-1.2.png");
    loadTexture(sky_23, "textures/x64/background/sky-2.3.png");

    sprite.setTexture(sky_1);
}

void Background::loadTexture(sf::Texture& texture, const string& fileName) {
    if (!texture.loadFromFile(fileName)) {
        throw runtime_error("Failed to load texture from file " + fileName);
    }
}

void Background::update() {
    singleOffset += movementSpeed;

    if (singleOffset > TILE_SIZE) {
		singleOffset -= TILE_SIZE;
		totalOffset++;
	}

    draw();
}

void Background::draw() {
    const unsigned windowWidth = window.getSize().x;
    const unsigned windowHeight = window.getSize().y;

    const unsigned columns = ceil(static_cast<double>(windowWidth) / TILE_SIZE);
    const unsigned rows = ceil(static_cast<double>(windowHeight) / TILE_SIZE) + (singleOffset != 0 ? 1 : 0);

    for (unsigned row = 0; row < rows; row++) {
        int y = static_cast<int>(row * TILE_SIZE) - static_cast<int>(TILE_SIZE - singleOffset);

        selectSprite(rows, row);

        for (unsigned x = 0; x < columns; x++) {
            sprite.setPosition(x * TILE_SIZE, y);
            window.draw(sprite);
        }
    }
}

void Background::selectSprite(const unsigned& rows, const unsigned& row) {
    int offsetRowDiff = static_cast<int>(totalOffset - row);

    if (totalOffset == 0 && row >= rows - 3) {
        sprite.setTexture(row == rows - 1 || row == rows - 2 ? dirt : grass);
    }
    else if (totalOffset == 1 && row >= rows - 2) {
        sprite.setTexture(row == rows - 1 ? dirt : grass);
    }
    else if (totalOffset == 2 && row == rows - 1) {
        sprite.setTexture(grass);
    }
    else if (offsetRowDiff == mediumLevelOffset) {
        sprite.setTexture(sky_12);
    }
    else if (offsetRowDiff == highLevelOffset) {
        sprite.setTexture(sky_23);
    }
    else if (offsetRowDiff > highLevelOffset) {
        sprite.setTexture(sky_3);
    }
    else if (offsetRowDiff > mediumLevelOffset && offsetRowDiff < highLevelOffset) {
        sprite.setTexture(sky_2);
    }
    else {
        sprite.setTexture(sky_1);
    }
}
