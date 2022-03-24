#pragma once

#include <SFML/Graphics.hpp>

class Animation {
private:
    float totalTime;
    float frameDuration;
    int curFrame;
    int frameCount;
    sf::IntRect frameRect;

public:
    Animation(const sf::Vector2u& spriteSheetSize, int frameCount, float frameDuration);

    void update(float deltaTime);

    void applyToSprite(sf::Sprite& sprite) const;
};