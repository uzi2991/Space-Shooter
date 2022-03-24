#pragma once

#include <Ship.hpp>

class Enemy: public Ship {
    friend class EnemyManager;

private:
    float minX, maxX;
    float minY, maxY;
    bool isOut;

public:
    Enemy(const sf::Texture& texture, int windowWidth, int windowHeight);

    void setOut();

    void update(float deltaTime) override;
};