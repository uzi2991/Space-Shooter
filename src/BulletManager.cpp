#include <BulletManager.hpp>


BulletManager::BulletManager(GameDataRef data): data(data) {}

std::vector<Bullet>& BulletManager::list() {
    return this->_list;
}

void BulletManager::shootBullet(float x, float y) {
    Bullet newBullet(this->data);
    newBullet.setPosition(x, y);

    this->_list.push_back(newBullet);
}

void BulletManager::update(float deltaTime) {

    // Update each bullet
    for (auto& bullet: this->_list) {
        bullet.update(deltaTime);
    }

    // Remove bullets out 
    auto it = std::remove_if(
        this->_list.begin(), this->_list.end(), 
        [](const Bullet& bullet) {
            return bullet.isOut;
        }
    );

    this->_list.erase(it, this->_list.end());
}

void BulletManager::draw() const {
    for (const auto& bullet: this->_list) {
        bullet.draw();
    }
}