#include <Player.hpp>

Player::Player(const sf::Texture& texture, int windowWidth, int windowHeight) : 
    Ship(texture, 2, 0.1f) {
    this->sprite.setScale(3.f, 3.f);
    this->moveSpeed = 300.f;

    this->minX = 0.f;
    this->maxX = windowWidth - this->getGlobalBounds().width;
    this->minY = 0.f;
    this->maxY = windowHeight - this->getGlobalBounds().height;
}

void Player::processBoundary() {
    auto [x, y, width, heigh] = this->getGlobalBounds();
    if (x < this->minX) {
        x = this->minX;
    } else if (x > this->maxX) {
        x = this->maxX;
    }

    if (y < this->minY) {
        y = this->minY;
    } else if (y > this->maxY) {
        y = this->maxY;
    }

    this->setPosition(x, y);
}

void Player::update(float deltaTime) {
    this->Ship::update(deltaTime);
    this->processBoundary();
}