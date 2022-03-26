#pragma once

#include <Ship.hpp>

class Enemy: public Ship {
    friend class EnemyManager;

private:
    bool isOut;

public:
    Enemy(GameDataRef data, int type);

    void setOut();

    void update(float deltaTime) override;
};