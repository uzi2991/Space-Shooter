#include <Enemy.hpp>

Enemy::Enemy(sf::RenderTarget* master, sf::Texture* texture): Entity(master, texture) {
    this->sprite.setScale(2.5f, 2.5f);
    this->animation = new Animation(this->sprite, 0.1f, 2);

    this->movementSpeed = 100.f;
}