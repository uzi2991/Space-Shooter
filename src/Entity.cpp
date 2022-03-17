#include <Entity.hpp>

Entity::Entity(sf::Texture* texture) {
    this->sprite.setTexture(*texture);
    this->animation = nullptr;
}

Entity::~Entity() {
    delete this->animation;
}

void Entity::move(const sf::Vector2f &direction, float dt) {
    this->sprite.move(direction * this->movementSpeed * dt);
}

void Entity::setPosition(float x, float y) {
    this->sprite.setPosition(x, y);
}

void Entity::render(sf::RenderTarget* target) const {
    target->draw(this->sprite);
}

void Entity::update(float dt) {
    this->animation->update(dt);
}

sf::FloatRect Entity::getBounds() const {
    return this->sprite.getGlobalBounds();
}
