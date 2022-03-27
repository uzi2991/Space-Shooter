#include <Enemy.hpp>
#include <Definitions.hpp>

Enemy::Enemy(GameDataRef data) : data(data)
{
    this->isOut = false;
    this->_bullets = std::make_unique<BulletManager>(this->data, BulletType::Laser);
    this->shootingTimer = 0.f;
}


void Enemy::draw() const
{
    this->data->window.draw(this->sprite);
    this->_bullets->draw();
}

void Enemy::setOut()
{
    this->isOut = true;
}

sf::FloatRect Enemy::getGlobalBounds() const {
    return this->sprite.getGlobalBounds();
}

void Enemy::setPosition(float x, float y) {
    this->sprite.setPosition(x, y);
}

void Enemy::shoot()
{   
    auto [left, top, width , height] = this->getGlobalBounds();
    this->_bullets->spawnBullet(
        left + width / 2, top + height,
        sf::Vector2f(0.f, 1.f)
    );
}

const std::vector<BulletRef>& Enemy::bullets() const
{
    return this->_bullets->list();
}

