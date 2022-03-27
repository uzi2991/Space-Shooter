#pragma once

#include <Enemy.hpp>
#include <BulletManager.hpp>

class BigEnemy: public Enemy
{
public:
    BigEnemy(GameDataRef data);

    void update(float deltaTime) override;

private:
    sf::Vector2f direction;
};