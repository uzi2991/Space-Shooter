#pragma once

#include <Animation.hpp>
#include <memory>


class Entity {
protected:
    sf::Sprite sprite;
    std::shared_ptr<Animation> animation;

    float movementSpeed;
    std::shared_ptr<sf::RenderTarget> master;

public:
    Entity(const std::shared_ptr<sf::RenderTarget>& master, const std::shared_ptr<sf::Texture>& texture);

    void move(const sf::Vector2f &direction, float dt);

    void setPosition(float x, float y);

    void render() const;

    void update(float dt);

    sf::FloatRect getBounds() const;
};