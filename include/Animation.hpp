#pragma once

#include <SFML/Graphics.hpp>

class Animation {
private:
    float duration;
    float progess;
    int curFrame;
    int numFrames;
    int frameWidth;
    sf::IntRect frameRect;
    sf::Sprite& sprite;

public:
    Animation(sf::Sprite& sprite, float duration, int numFrames);

    void update(float dt);
};