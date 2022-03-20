#pragma once

#include <SFML/Graphics.hpp>

class Background {
private:
    sf::Sprite sprite1, sprite2;
    int height;
    float speed;

public:
    Background(sf::Texture* texture);

    void update(float dt);

    void render(sf::RenderTarget* target) const;
    
};