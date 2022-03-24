#include <Bullet.hpp>


Bullet::Bullet(const sf::Texture& texture, int windowWidth, int windowHeight) {
    this->sprite.setTexture(texture);
    this->sprite.setOrigin(8.f, 8.f);
    this->sprite.setScale(4.f, 4.f);

    this->moveSpeed = 600.f;
    this->minY = -this->getGlobalBounds().height;
    this->isOut = false;
}

void Bullet::update(float deltaTime) {
    this->sprite.move(sf::Vector2f(0.f, -1.f) * this->moveSpeed * deltaTime);
    if (this->sprite.getGlobalBounds().top < this->minY) {
        this->setOut();
    }
}

void Bullet::setPosition(float x, float y) {
    this->sprite.setPosition(x, y);
}

void Bullet::setOut() {
    this->isOut = true;
}

sf::FloatRect Bullet::getGlobalBounds() const {
    return this->sprite.getGlobalBounds();
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(this->sprite, states);
}
