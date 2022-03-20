#pragma once

#include <Animation.hpp>


class Entity {
protected:
    sf::Sprite sprite;
    Animation* animation;

    float movementSpeed;
    sf::RenderTarget* master;

public:
    Entity(sf::RenderTarget* master, sf::Texture* texture);

    ~Entity();

    void move(const sf::Vector2f &direction, float dt);

    void setPosition(float x, float y);

    void render() const;

    void update(float dt);

    sf::FloatRect getBounds() const;
};