#include <Player.hpp>

Player::Player(sf::Texture* texture): Entity(texture) {
    this->sprite.setScale(3.5f, 3.5f);
    this->animation = new Animation(this->sprite, 0.1f, 2);
    this->movementSpeed = 400.f;
}


