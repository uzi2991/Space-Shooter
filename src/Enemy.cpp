#include <Enemy.hpp>

Enemy::Enemy(const sf::Texture& texture, int windowWidth, int windowHeight): 
    Ship(texture, 2, 0.1f) {
    this->sprite.setScale(2.5f, 2.5f);
    this->moveSpeed = 100.f;

    this->minX = 0.f;
    this->maxX = windowWidth - this->getGlobalBounds().width;
    this->minY = -this->getGlobalBounds().height;
    this->maxY = windowHeight;

    this->moveDown();
    this->isOut = false;
}

void Enemy::setOut() {
    this->isOut = true;
}

void Enemy::update(float deltaTime) {
    this->Ship::update(deltaTime);
    auto [x, y, width, heigh] = this->getGlobalBounds();
    if (y > this->maxY) {
        this->setOut();
    }
}