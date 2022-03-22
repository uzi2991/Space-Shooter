#pragma once

#include <Entity.hpp>

class Player: public Entity {
public:
    Player(const std::shared_ptr<sf::RenderTarget>& master, const std::shared_ptr<sf::Texture>& texture);
};