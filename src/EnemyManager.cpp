#include <EnemyManager.hpp>


EnemyManager::EnemyManager() {
    this->spawnCoolDown = 1.f;
    this->totalTime = this->spawnCoolDown;
}

void EnemyManager::setWindowSize(int windowWidth, int windowHeight) {
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
}

void EnemyManager::setTexture(const sf::Texture& texture) {
    this->texture = texture;
}

const std::vector<std::shared_ptr<Enemy>>& EnemyManager::list() const {
    return this->data;
}

void EnemyManager::spawnEnemy() {
    auto newEnemy = std::make_shared<Enemy>(texture, this->windowWidth, this->windowHeight);
    float randomX = rand() % int(newEnemy->maxX) + newEnemy->minX;
    newEnemy->setPosition(randomX, newEnemy->minY);

    this->data.push_back(newEnemy);
}

void EnemyManager::update(float deltaTime) {
    this->totalTime += deltaTime;

    // Spawn enemy
    if (this->totalTime >= this->spawnCoolDown) {
        this->spawnEnemy();
        this->totalTime -= this->spawnCoolDown;
    }

    // Update each enemy
    for (const auto& enemy: this->data) {
        enemy->update(deltaTime);
    }

    // Remove enemies out 
    auto it = std::remove_if(
        this->data.begin(), this->data.end(), 
        [](const std::shared_ptr<Enemy>& enemy) {
            return enemy->isOut;
        }
    );
    this->data.erase(it, this->data.end());
}

void EnemyManager::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& enemy: this->data) {
        target.draw(*enemy, states);
    }
}