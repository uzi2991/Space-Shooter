#include <Player.hpp>
#include <Definitions.hpp>

Player::Player(GameDataRef data) : Ship(data)
{
    this->sprite.setTexture(this->data->assets.getTexture("player"));
    this->sprite.setScale(PLAYER_SCALE, PLAYER_SCALE);

    this->animation = new Animation(
        this->data->assets.getTexture("player").getSize(),
        PLAYER_NUM_FRAMES,
        PLAYER_FRAMES_TIME
    );

    this->animation->applyToSprite(this->sprite);


    this->moveSpeed = PLAYER_MOVE_SPEED;
}

void Player::processBoundary() {
    auto [x, y, width, height] = this->getGlobalBounds();
    
    if (x < 0.f) {
        x = 0.f;
    } else if (x > SCREEN_WIDTH - width) {
        x = SCREEN_WIDTH - width;
    }

    if (y < 0.f) {
        y = 0.f;
    } else if (y > SCREEN_HEIGHT - height) {
        y = SCREEN_HEIGHT - height;
    }

    this->setPosition(x, y);
}

void Player::update(float deltaTime) {
    this->Ship::update(deltaTime);
    this->processBoundary();
}