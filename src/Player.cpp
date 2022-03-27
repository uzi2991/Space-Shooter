#include <Player.hpp>
#include <Definitions.hpp>

Player::Player(GameDataRef data): data(data)
{
    this->sprite.setTexture(this->data->assets.getTexture("player"));
    this->sprite.setScale(PLAYER_SCALE, PLAYER_SCALE);

    this->animation = std::make_unique<Animation>(
        this->data->assets.getTexture("player").getSize(),
        PLAYER_NUM_FRAMES,
        PLAYER_FRAMES_TIME
    );

    this->animation->applyToSprite(this->sprite);

    this->direction.x = 0.f;
    this->direction.y = 0.f;

    this->moveSpeed = PLAYER_MOVE_SPEED;

    this->_bullets = std::make_unique<BulletManager>(this->data);

    this->shootingTimer = BULLET_SHOOTING_COOLDOWN;

    this->hp = PLAYER_HEALTH;
}

void Player::handleInput() {
    // Movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        this->direction.x = -1.f;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        this->direction.x = 1.f;
    } else {
        this->direction.x = 0.f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        this->direction.y = -1.f;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        this->direction.y = 1.f;
    } else {
        this->direction.y = 0.f;
    }

    // Shoot a bullet
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->shootingTimer > BULLET_SHOOTING_COOLDOWN) {
        this->shootingTimer = 0.f;
        this->shoot();
    }
}

void Player::update(float deltaTime) {
    // Update animation
    this->animation->update(deltaTime);
    this->animation->applyToSprite(this->sprite);

    // Get current position
    auto [x, y] = this->sprite.getPosition();
    
    // Update along horizontal axis
    x += this->moveSpeed * this->direction.x * deltaTime;
    if (x < 0.f) {
        x = 0.f;
    } else if (x > SCREEN_WIDTH - this->getGlobalBounds().width) {
        x = SCREEN_WIDTH - this->getGlobalBounds().width;
    }

    // Update along vertical axis
    y += this->moveSpeed * this->direction.y * deltaTime;
    if (y < 0.f) {
        y = 0.f;
    } else if (y > SCREEN_HEIGHT - this->getGlobalBounds().height) {
        y = SCREEN_HEIGHT - this->getGlobalBounds().height;
    }

    // Set position
    this->setPosition(x, y);

    // Update bullets
    this->_bullets->update(deltaTime);
    this->shootingTimer += deltaTime;
}

void Player::draw() const {
    this->data->window.draw(this->sprite);
    this->_bullets->draw();
}

sf::FloatRect Player::getGlobalBounds() const {
    return this->sprite.getGlobalBounds();
}

void Player::setPosition(float x, float y) {
    this->sprite.setPosition(x, y);
}

const std::vector<BulletRef>& Player::bullets() const {
    return this->_bullets->list();
}

void Player::shoot() {
    auto [left, top, width, height] = this->getGlobalBounds();
    this->_bullets->spawnBullet(
        left + width / 2, top,
        sf::Vector2f(0.f, -1.f)
    );
}

bool Player::takeHit() {
    return (--this->hp == 0);
}

int Player::getHP() const {
    return this->hp;
}