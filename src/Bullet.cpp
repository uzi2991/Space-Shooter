#include <Bullet.hpp>
#include <Definitions.hpp>

Bullet::Bullet(GameDataRef data, const sf::Vector2f &direction, BulletType type) : data(data), direction(direction)
{
    if (type == BulletType::Bolts)
    {
        this->sprite.setTexture(this->data->assets.getTexture("bolts"));
        this->animation = std::make_unique<Animation>(
            this->data->assets.getTexture("bolts").getSize(),
            BULLET_NUM_FRAMES,
            BULLET_FRAMES_TIMES);
    }
    else
    {
        this->sprite.setTexture(this->data->assets.getTexture("laser"));
        this->animation = std::make_unique<Animation>(
            this->data->assets.getTexture("laser").getSize(),
            BULLET_NUM_FRAMES,
            BULLET_FRAMES_TIMES);
    }

    this->animation->applyToSprite(this->sprite);
    
    this->sprite.setOrigin(
        this->sprite.getGlobalBounds().width / 2,
        this->sprite.getGlobalBounds().height);

    this->sprite.setScale(BULLET_SCALE, BULLET_SCALE);


    this->moveSpeed = BULLET_MOVE_SPEED;
    this->isOut = false;
}

void Bullet::update(float deltaTime)
{   
    this->animation->update(deltaTime);
    this->animation->applyToSprite(this->sprite);
    
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
