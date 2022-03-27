#include <BigEnemy.hpp>
#include <Definitions.hpp>

BigEnemy::BigEnemy(GameDataRef data) : Enemy(data)
{
    this->sprite.setTexture(this->data->assets.getTexture("big enemy"));
    this->moveSpeed = BIG_ENEMY_MOVE_SPEED;
    this->animation = std::make_unique<Animation>(
        this->data->assets.getTexture("big enemy").getSize(),
        ENEMY_NUM_FRAMES,
        ENEMY_FRAMES_TIME);

    this->animation->applyToSprite(this->sprite);
    this->sprite.setScale(ENEMY_SCALE, ENEMY_SCALE);

    this->direction.x = rand() % 3 - 1;
    this->direction.y = 1.f;
}

void BigEnemy::update(float deltaTime)
{   
    this->animation->update(deltaTime);
    this->animation->applyToSprite(this->sprite);
    
    this->shootingTimer += deltaTime;
    if (this->shootingTimer > BIG_ENEMY_SHOOTING_COOLDOWN)
    {
        this->shootingTimer = 0.f;
        this->shoot();
    }

    this->_bullets->update(deltaTime);

    this->direction.y = rand() % 2;

    if (this->getGlobalBounds().left < 0.f)
    {
        this->direction.x = abs(this->direction.x);
    }
    else if (this->getGlobalBounds().left > SCREEN_WIDTH - this->getGlobalBounds().width)
    {
        this->direction.x = -abs(this->direction.x);
    }

    this->sprite.move(this->direction * this->moveSpeed * deltaTime);

    if (this->getGlobalBounds().top > SCREEN_HEIGHT)
    {
        this->setOut();
    }
}
