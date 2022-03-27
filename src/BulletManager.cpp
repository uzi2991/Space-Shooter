#include <BulletManager.hpp>

BulletManager::BulletManager(GameDataRef data) : data(data) {}

void BulletManager::update(float deltaTime)
{

    // Update each bullet
    for (const auto &bullet : this->_list)
    {
        bullet->update(deltaTime);
    }

    // Remove bullets out
    int size = std::remove_if(
                   this->_list.begin(), this->_list.end(),
                   [](const BulletRef &bullet)
                   {
                       return bullet->isOut;
                   }) -
               this->_list.begin();

    while ((int)this->_list.size() > size)
    {
        this->_list.pop_back();
    }
        
}

void BulletManager::draw() const
{
    for (const auto &bullet : this->_list)
    {
        bullet->draw();
    }
}

const std::vector<BulletRef>& BulletManager::list()
{
    return this->_list;
}

void BulletManager::spawnBullet(float x, float y, const sf::Vector2f &direction)
{
    auto newBullet = std::make_unique<Bullet>(this->data, direction);

    newBullet->setPosition(x, y);

    this->_list.push_back(std::move(newBullet));
}
