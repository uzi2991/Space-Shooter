#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class Background {
private:
    sf::Sprite sprite1, sprite2;
    int height;
    float speed;
    std::shared_ptr<sf::RenderTarget> master;

public:
    Background(const std::shared_ptr<sf::RenderTarget>& master, const std::shared_ptr<sf::Texture>& texture);

    void update(float dt);

    void render() const;
    
};