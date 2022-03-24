#pragma once

#include <Animation.hpp>


class Ship: public sf::Drawable {
protected:
    Animation animation;

    sf::Sprite sprite;

    float moveSpeed;

    bool isMovingLeft, isMovingRight, isMovingUp, isMovingDown;
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    Ship(const sf::Texture& texture, int frameCount, float frameDuration);

    void setPosition(float x, float y);

    sf::FloatRect getGlobalBounds() const;

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    void stopLeft();
    void stopRight();
    void stopUp();
    void stopDown();

    virtual void update(float deltaTime);
};


