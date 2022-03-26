#include <Bullet.hpp>
#include <Definitions.hpp>

Bullet::Bullet(GameDataRef data) : data(data)
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
    this->sprite.move(sf::Vector2f(0.f, -1.f) * this->moveSpeed * deltaTime);
    if (this->sprite.getGlobalBounds().top < -this->getGlobalBounds().height)
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
