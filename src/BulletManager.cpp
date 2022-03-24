#include <BulletManager.hpp>


void BulletManager::setWindowSize(int windowWidth, int windowHeight) {
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
}

void BulletManager::setTexture(const sf::Texture& texture) {
    this->texture = texture;
}

const std::vector<std::shared_ptr<Bullet>>& BulletManager::list() const {
    return this->data;
}

void BulletManager::shootBullet(float x, float y) {
    auto newBullet = std::make_shared<Bullet>(texture, this->windowWidth, this->windowHeight);
    newBullet->setPosition(x, y);

    this->data.push_back(newBullet);
}

void BulletManager::update(float deltaTime) {

    // Update each bullet
    for (const auto& bullet: this->data) {
        bullet->update(deltaTime);
    }

    // Remove bullets out 
    auto it = std::remove_if(
        this->data.begin(), this->data.end(), 
        [](const std::shared_ptr<Bullet>& bullet) {
            return bullet->isOut;
        }
    );
    this->data.erase(it, this->data.end());
}

void BulletManager::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& bullet: this->data) {
        target.draw(*bullet, states);
    }
}