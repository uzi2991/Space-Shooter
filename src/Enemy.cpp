#include <Enemy.hpp>
#include <Definitions.hpp>

Enemy::Enemy(GameDataRef data, int type) : Ship(data)
{
    switch (type)
    {
    case 0:
        this->sprite.setTexture(this->data->assets.getTexture("big enemy"));
        this->moveSpeed = BIG_ENEMY_MOVE_SPEED;
        this->animation = new Animation(
            this->data->assets.getTexture("big enemy").getSize(),
            ENEMY_NUM_FRAMES,
            ENEMY_FRAMES_TIME);
        break;
    case 1:
        this->sprite.setTexture(this->data->assets.getTexture("medium enemy"));
        this->moveSpeed = MEDIUM_ENEMY_MOVE_SPEED;
        this->animation = new Animation(
            this->data->assets.getTexture("medium enemy").getSize(),
            ENEMY_NUM_FRAMES,
            ENEMY_FRAMES_TIME);
        break;
    case 2:
        this->sprite.setTexture(this->data->assets.getTexture("small enemy"));
        this->moveSpeed = SMALL_ENEMY_MOVE_SPEED;
        this->animation = new Animation(
            this->data->assets.getTexture("small enemy").getSize(),
            ENEMY_NUM_FRAMES,
            ENEMY_FRAMES_TIME);
        break;
    }

    this->animation->applyToSprite(this->sprite);

    this->sprite.setScale(ENEMY_SCALE, ENEMY_SCALE);
    this->moveDown();
    this->isOut = false;
}

void Enemy::setOut()
{
    this->isOut = true;
}

void Enemy::update(float deltaTime)
{
    this->Ship::update(deltaTime);
    if (this->getGlobalBounds().top > SCREEN_HEIGHT)
    {
        this->setOut();
    }
}