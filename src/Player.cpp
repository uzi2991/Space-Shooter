#include <Player.hpp>

Player::Player(sf::RenderTarget* master ,sf::Texture* texture): Entity(master, texture) {
    this->sprite.setScale(3.f, 3.f);
    this->animation = new Animation(this->sprite, 0.1f, 2);
    this->movementSpeed = 400.f;
}


