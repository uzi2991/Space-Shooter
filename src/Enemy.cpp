#include <Enemy.hpp>

Enemy::Enemy(sf::Texture* texture): Entity(texture) {
    this->sprite.setScale(3.f, 3.f);

    this->movementSpeed = 100.f;
}