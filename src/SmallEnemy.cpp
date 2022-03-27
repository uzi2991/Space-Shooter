#include <SmallEnemy.hpp>
#include <Definitions.hpp>

SmallEnemy::SmallEnemy(GameDataRef data) : Enemy(data)
{
    this->sprite.setTexture(this->data->assets.getTexture("small enemy"));
    this->moveSpeed = SMALL_ENEMY_MOVE_SPEED;
    this->animation = std::make_unique<Animation>(
        this->data->assets.getTexture("small enemy").getSize(),
        ENEMY_NUM_FRAMES,
        ENEMY_FRAMES_TIME);
    
    this->animation->applyToSprite(this->sprite);

    this->sprite.setScale(ENEMY_SCALE, ENEMY_SCALE);
}

void SmallEnemy::update(float deltaTime)
{
    this->animation->update(deltaTime);
    this->animation->applyToSprite(this->sprite);

    this->sprite.move(0.f, this->moveSpeed * deltaTime);
    if (this->getGlobalBounds().top > SCREEN_HEIGHT) {
        this->setOut();
    }
}