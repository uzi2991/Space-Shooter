#pragma once

#include <Ship.hpp>

class Player: public Ship {
private:
    void processBoundary();

public:
    Player(GameDataRef data);

    void update(float deltaTime) override;
};