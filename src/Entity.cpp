#include <Entity.hpp>

Entity::Entity(const std::shared_ptr<sf::RenderTarget>& master, const std::shared_ptr<sf::Texture>& texture) {
    this->sprite.setTexture(*texture);
    this->animation = nullptr;
    this->master = master;
}

void Entity::move(const sf::Vector2f &direction, float dt) {
    this->sprite.move(direction * this->movementSpeed * dt);
}

void Entity::setPosition(float x, float y) {
    this->sprite.setPosition(x, y);
}

void Entity::render() const {
    this->master->draw(this->sprite);
}

void Entity::update(float dt) {
    this->animation->update(dt);
}

sf::FloatRect Entity::getBounds() const {
    return this->sprite.getGlobalBounds();
}
