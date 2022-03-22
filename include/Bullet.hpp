#pragma once

#include <Entity.hpp>

class Bullet: public Entity {
public:
    Bullet(const std::shared_ptr<sf::RenderTarget>& master, const std::shared_ptr<sf::Texture>& texture);
};