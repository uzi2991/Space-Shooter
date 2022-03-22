#include <Enemy.hpp>

Enemy::Enemy(const std::shared_ptr<sf::RenderTarget>& master, const std::shared_ptr<sf::Texture>& texture): Entity(master, texture) {
    this->sprite.setScale(2.5f, 2.5f);
    this->animation = std::make_shared<Animation>(this->sprite, 0.1f, 2);

    this->movementSpeed = 100.f;
}