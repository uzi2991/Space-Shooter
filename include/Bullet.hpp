#pragma once

#include <SFML/Graphics.hpp>
#include <Game.hpp>

class Bullet
{
    friend class BulletManager;

public:
    Bullet(GameDataRef data);

    void update(float deltaTime);

    void setPosition(float x, float y);

    void setOut();

    sf::FloatRect getGlobalBounds() const;

    void draw() const;

private:
    sf::Sprite sprite;

    float moveSpeed;

    bool isOut;

    GameDataRef data;
};