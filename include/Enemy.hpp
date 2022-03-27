#pragma once
#include <Game.hpp>
#include <Animation.hpp>
#include <BulletManager.hpp>

enum class EnemyType
{
    Small,
    Medium,
    Big
};

class Enemy
{
    friend class EnemyManager;

public:
    Enemy(GameDataRef data);

    virtual void update(float deltaTime) = 0;

    void draw() const;

    sf::FloatRect getGlobalBounds() const;

    void setPosition(float x, float y);

    void setOut();

    const std::vector<BulletRef> &bullets() const;

protected:
    GameDataRef data;

    std::unique_ptr<Animation> animation;

    sf::Sprite sprite;

    float moveSpeed;

    bool isOut;

    std::unique_ptr<BulletManager> _bullets;

    float shootingTimer;

    void shoot();
};