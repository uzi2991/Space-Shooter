#include <Bullet.hpp>
#include <Definitions.hpp>

Bullet::Bullet(GameDataRef data, const sf::Vector2f& direction) : data(data), direction(direction)
{
    this->sprite.setTexture(this->data->assets.getTexture("bullet"));
    this->sprite.setOrigin(
        this->sprite.getGlobalBounds().width / 2,
        this->sprite.getGlobalBounds().height);
    this->sprite.setScale(BULLET_SCALE, BULLET_SCALE);

    this->moveSpeed = BULLET_MOVE_SPEED;
    this->isOut = false;
}

void Bullet::update(float deltaTime)
{
    this->sprite.move(this->direction * this->moveSpeed * deltaTime);
    if (this->getGlobalBounds().top < -this->getGlobalBounds().height ||
        this->getGlobalBounds().top > SCREEN_HEIGHT)
    {
        this->setOut();
    }
}

void Bullet::setPosition(float x, float y)
{
    this->sprite.setPosition(x, y);
}

void Bullet::setOut()
{
    this->isOut = true;
}

sf::FloatRect Bullet::getGlobalBounds() const
{
    return this->sprite.getGlobalBounds();
}

void Bullet::draw() const
{
    this->data->window.draw(this->sprite);
}
