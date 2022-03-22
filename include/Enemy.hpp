#pragma once

#include <Entity.hpp>

class Enemy: public Entity {
public:
    Enemy(const std::shared_ptr<sf::RenderTarget>& master, const std::shared_ptr<sf::Texture>& texture);
};