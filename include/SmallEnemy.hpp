#pragma once

#include <Enemy.hpp>

class SmallEnemy: public Enemy
{
public:
    SmallEnemy(GameDataRef data);

    void update(float deltaTime) override;
};
