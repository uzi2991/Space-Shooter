#pragma once

#include <Entity.hpp>

class Enemy: public Entity {
public:
    Enemy(sf::RenderTarget* master, sf::Texture* texture);
};