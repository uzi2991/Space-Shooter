#pragma once

#include <SFML/Graphics.hpp>
#include <Game.hpp>
#include <Animation.hpp>

enum class BulletType
{
    Laser,
    Bolts
};
class Bullet
{
    friend class BulletManager;

public:
    Bullet(GameDataRef data, const sf::Vector2f &direction, BulletType type);

    void update(float deltaTime);

    void draw() const;

    sf::FloatRect getGlobalBounds() const;

    void setPosition(float x, float y);

    void setOut();

private:
    GameDataRef data;

    std::unique_ptr<Animation> animation;

    sf::Sprite sprite;

    sf::Vector2f direction;

    float moveSpeed;

    bool isOut;
};