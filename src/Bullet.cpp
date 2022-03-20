#include <Bullet.hpp>

Bullet::Bullet(sf::RenderTarget* master, sf::Texture* texture): Entity(master, texture) {
    this->sprite.setScale(4.f, 4.f);
    this->sprite.setOrigin(8.f, 8.f);

    this->movementSpeed = 600.f;
}
