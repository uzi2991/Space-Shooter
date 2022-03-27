#include <Enemy.hpp>
#include <Definitions.hpp>

Enemy::Enemy(GameDataRef data, int type) : data(data)
{
    switch (type)
    {
    case 0:
        this->sprite.setTexture(this->data->assets.getTexture("big enemy"));
        this->moveSpeed = BIG_ENEMY_MOVE_SPEED;
        this->animation = std::make_unique<Animation>(
            this->data->assets.getTexture("big enemy").getSize(),
            ENEMY_NUM_FRAMES,
            ENEMY_FRAMES_TIME);
        break;
    case 1:
        this->sprite.setTexture(this->data->assets.getTexture("medium enemy"));
        this->moveSpeed = MEDIUM_ENEMY_MOVE_SPEED;
        this->animation = std::make_unique<Animation>(
            this->data->assets.getTexture("medium enemy").getSize(),
            ENEMY_NUM_FRAMES,
            ENEMY_FRAMES_TIME);
        break;
    case 2:
        this->sprite.setTexture(this->data->assets.getTexture("small enemy"));
        this->moveSpeed = SMALL_ENEMY_MOVE_SPEED;
        this->animation = std::make_unique<Animation>(
            this->data->assets.getTexture("small enemy").getSize(),
            ENEMY_NUM_FRAMES,
            ENEMY_FRAMES_TIME);
        break;
    }

    this->animation->applyToSprite(this->sprite);

    this->sprite.setScale(ENEMY_SCALE, ENEMY_SCALE);

    this->isOut = false;
}

void Enemy::update(float deltaTime)
{
    this->animation->update(deltaTime);
    this->animation->applyToSprite(this->sprite);

    this->sprite.move(0.f, this->moveSpeed * deltaTime);

    if (this->getGlobalBounds().top > SCREEN_HEIGHT)
    {
        this->setOut();
    }
}

void Enemy::draw() const
{
    this->data->window.draw(this->sprite);
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

