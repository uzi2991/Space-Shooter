#include <Background.hpp>

Background::Background(sf::Texture* texture) {
    this->sprite1.setTexture(*texture);
    this->sprite2.setTexture(*texture);
    this->sprite1.setScale(2.f, 2.f);
    this->sprite2.setScale(2.f, 2.f);

    this->height = this->sprite1.getGlobalBounds().height;
    this->speed = 50.f;

    this->sprite1.setPosition(0.f, 0.f);
    this->sprite2.setPosition(0.f, this->height);
}

void Background::update(float dt) {
    this->sprite1.move(0.f, this->speed * dt);
    this->sprite2.move(0.f, this->speed * dt);

    if (this->sprite1.getPosition().y >= this->height) {
        this->sprite1.setPosition(0.f, this->sprite1.getPosition().y - 2 * this->height);
    }

    
    if (this->sprite2.getPosition().y >= this->height) {
        this->sprite2.setPosition(0.f, this->sprite2.getPosition().y - 2 * this->height);
    }
}

void Background::render(sf::RenderTarget* target) const {
    target->draw(this->sprite1);
    target->draw(this->sprite2);
}
