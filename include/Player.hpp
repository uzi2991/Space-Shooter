#pragma once

#include <Entity.hpp>

class Player: public Entity {
public:
    Player(sf::RenderTarget* master, sf::Texture* texture);
};