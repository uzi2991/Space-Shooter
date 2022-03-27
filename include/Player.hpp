#pragma once

#include <Game.hpp>
#include <Animation.hpp>
#include <BulletManager.hpp>

class Player
{
public:
    Player(GameDataRef data);

    void handleInput();

    void update(float deltaTime);

    void draw() const;

    sf::FloatRect getGlobalBounds() const;

    void setPosition(float x, float y);

    const std::vector<BulletRef>& bullets() const;

    void shoot();

    // player takes damage and return true if player is dead
    bool takeHit();

    // Return the current HP
    int getHP() const;

private:
    GameDataRef data;

    std::unique_ptr<Animation> animation;

    sf::Sprite sprite;

    float moveSpeed;

    sf::Vector2f direction;

    std::unique_ptr<BulletManager> _bullets;

    float shootingTimer;

    int hp;
};