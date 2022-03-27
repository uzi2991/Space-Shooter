#pragma once
#include <Game.hpp>
#include <Animation.hpp>

class Enemy
{
    friend class EnemyManager;

public:
    Enemy(GameDataRef data, int type);

    void update(float deltaTime);

    void draw() const;

    sf::FloatRect getGlobalBounds() const;

    void setPosition(float x, float y);
    
    void setOut();

private:
    GameDataRef data;

    std::unique_ptr<Animation> animation;

    sf::Sprite sprite;

    float moveSpeed;

    bool isOut;
};