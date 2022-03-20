#pragma once

#include <SFML/Graphics.hpp>

class Background {
private:
    sf::Sprite sprite1, sprite2;
    int height;
    float speed;
    sf::RenderTarget* master;

public:
    Background(sf::RenderTarget* master, sf::Texture* texture);

    void update(float dt);

    void render() const;
    
};