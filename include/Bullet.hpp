#pragma once

#include <SFML/Graphics.hpp>

class Bullet: public sf::Drawable {
    friend class BulletManager;

private:
    sf::Sprite sprite;

    float moveSpeed;

    float minY;

    bool isOut;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    Bullet(const sf::Texture& texture, int windowWidth, int windowHeight);

    void update(float deltaTime);
    
    void setPosition(float x, float y);

    void setOut();

    sf::FloatRect getGlobalBounds() const;
};