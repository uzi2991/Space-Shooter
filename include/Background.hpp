#pragma once

#include <SFML/Graphics.hpp>

class Background: public sf::Drawable {
private:
    sf::Sprite sprite1, sprite2;
    int height;
    float speed;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    Background(const sf::Texture& texture);

    void update(float dt); 
};