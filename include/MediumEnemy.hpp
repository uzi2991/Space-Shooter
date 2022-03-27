#pragma once

#include <Enemy.hpp>
#include <BulletManager.hpp>

class MediumEnemy: public Enemy
{
public:
    MediumEnemy(GameDataRef data);

    void update(float deltaTime) override;
};