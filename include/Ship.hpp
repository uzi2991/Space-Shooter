#pragma once

#include <Animation.hpp>
#include <Game.hpp>


class Ship {
public:
    Ship(GameDataRef data);
    ~Ship();

    void setPosition(float x, float y);

    sf::FloatRect getGlobalBounds() const;

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    void stopLeft();
    void stopRight();
    void stopUp();
    void stopDown();

    virtual void update(float deltaTime);

    void draw() const;

protected:
    Animation* animation;

    sf::Sprite sprite;

    float moveSpeed;

    bool isMovingLeft, isMovingRight, isMovingUp, isMovingDown;

    GameDataRef data;
};


