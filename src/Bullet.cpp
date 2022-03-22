#include <Bullet.hpp>

Bullet::Bullet(const std::shared_ptr<sf::RenderTarget>& master, const std::shared_ptr<sf::Texture>& texture): Entity(master, texture) {
    this->sprite.setScale(4.f, 4.f);
    this->sprite.setOrigin(8.f, 8.f);

    this->movementSpeed = 600.f;
}
