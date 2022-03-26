#include <Ship.hpp>


Ship::Ship(GameDataRef data) : data(data)
{
    this->isMovingLeft = false;
    this->isMovingRight = false;
    this->isMovingRight = false;
    this->isMovingDown = false;
}

Ship::~Ship() {
    delete this->animation;
}

void Ship::setPosition(float x, float y) {
    this->sprite.setPosition(x, y);
}

sf::FloatRect Ship::getGlobalBounds() const {
    return this->sprite.getGlobalBounds();
}

void Ship::moveLeft() {
    this->isMovingLeft = true;
}

void Ship::moveRight() {
    this->isMovingRight = true;
}

void Ship::moveUp() {
    this->isMovingUp = true;
}

void Ship::moveDown() {
    this->isMovingDown = true;
}

void Ship::stopLeft() {
    this->isMovingLeft = false;
}

void Ship::stopRight() {
    this->isMovingRight = false;
}

void Ship::stopUp() {
    this->isMovingUp = false;
}

void Ship::stopDown() {
    this->isMovingDown = false;
}

void Ship::update(float deltaTime) {
    this->animation->update(deltaTime);
    this->animation->applyToSprite(this->sprite);

    float x = this->getGlobalBounds().left;
    float y = this->getGlobalBounds().top;

    if (this->isMovingLeft) {
        x -= this->moveSpeed * deltaTime;
    }

    if (this->isMovingRight) {
        x += this->moveSpeed * deltaTime;
    }

    if (this->isMovingUp) {
        y -= this->moveSpeed * deltaTime;
    }

    if (this->isMovingDown) {
        y += this->moveSpeed * deltaTime;
    }

    this->setPosition(x, y);
}

void Ship::draw() const {
    this->data->window.draw(this->sprite);
}