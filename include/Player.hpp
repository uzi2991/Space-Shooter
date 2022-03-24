#pragma once

#include <Ship.hpp>

class Player: public Ship {
private:
    float minX, maxX;
    float minY, maxY;

    void processBoundary();

public:
    Player(const sf::Texture& texture, int windowWidth, int windowHeight);

    void update(float deltaTime) override;
};