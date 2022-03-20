#pragma once

#include <Entity.hpp>

class Bullet: public Entity {
public:
    Bullet(sf::RenderTarget* master ,sf::Texture* texture);
};