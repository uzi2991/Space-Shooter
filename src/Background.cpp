#include <Background.hpp>

Background::Background(const std::shared_ptr<sf::RenderTarget>& master, const std::shared_ptr<sf::Texture>& texture) {
    this->sprite1.setTexture(*texture);
    this->sprite2.setTexture(*texture);
    this->sprite1.setScale(2.f, 2.f);
    this->sprite2.setScale(2.f, 2.f);

    this->height = this->sprite1.getGlobalBounds().height;
    this->speed = 50.f;

    this->sprite1.setPosition(0.f, 0.f);
    this->sprite2.setPosition(0.f, this->height);

    this->master = master;
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

void Background::render() const {
    this->master->draw(this->sprite1);
    this->master->draw(this->sprite2);
}
