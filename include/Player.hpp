#pragma once

#include <Game.hpp>
#include <Animation.hpp>

class Player
{
public:
    Player(GameDataRef data);

    void handleInput();

    void update(float deltaTime);

    void draw() const;

    sf::FloatRect getGlobalBounds() const;

    void setPosition(float x, float y);

private:
    GameDataRef data;

    std::unique_ptr<Animation> animation;

    sf::Sprite sprite;

    float moveSpeed;

    sf::Vector2f direction;
};