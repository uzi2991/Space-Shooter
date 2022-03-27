#include <MediumEnemy.hpp>
#include <Definitions.hpp>

MediumEnemy::MediumEnemy(GameDataRef data) : Enemy(data)
{
    this->sprite.setTexture(this->data->assets.getTexture("medium enemy"));
    this->moveSpeed = MEDIUM_ENEMY_MOVE_SPEED;
    this->animation = std::make_unique<Animation>(
        this->data->assets.getTexture("medium enemy").getSize(),
        ENEMY_NUM_FRAMES,
        ENEMY_FRAMES_TIME);

    this->animation->applyToSprite(this->sprite);
    this->sprite.setScale(ENEMY_SCALE, ENEMY_SCALE);
}

void MediumEnemy::update(float deltaTime)
{
    this->animation->update(deltaTime);
    this->animation->applyToSprite(this->sprite);
    this->shootingTimer += deltaTime;
    if (this->shootingTimer > MEDIUM_ENEMY_SHOOTING_COOLDOWN)
    {
        this->shootingTimer = 0.f;
        this->shoot();
    }

    this->_bullets->update(deltaTime);

    this->sprite.move(0.f, this->moveSpeed * deltaTime);

    if (this->getGlobalBounds().top > SCREEN_HEIGHT)
    {
        this->setOut();
    }
}
