#include <Player.hpp>

Player::Player(const std::shared_ptr<sf::RenderTarget>& master, const std::shared_ptr<sf::Texture>& texture): Entity(master, texture) {
    this->sprite.setScale(3.f, 3.f);
    this->animation = std::make_shared<Animation>(this->sprite, 0.1f, 2);
    this->movementSpeed = 400.f;
}


