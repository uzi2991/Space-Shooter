#include <EnemyManager.hpp>
#include <Definitions.hpp>

EnemyManager::EnemyManager(GameDataRef data) : data(data)
{
    this->spawnCoolDown = ENEMY_SPAWN_COOLDOWN;
    this->totalTime = this->spawnCoolDown;
}

void EnemyManager::update(float deltaTime)
{
    this->totalTime += deltaTime;

    // Spawn enemy
    if (this->totalTime >= this->spawnCoolDown)
    {
        this->spawnEnemy();
        this->totalTime -= this->spawnCoolDown;
    }

    // Update each enemy
    for (const auto &enemy : this->_list)
    {
        enemy->update(deltaTime);
    }

    // Remove enemies out
    int size = std::remove_if(
                   this->_list.begin(), this->_list.end(),
                   [](const EnemyRef &enemy)
                   {
                       return enemy->isOut;
                   }) -
               this->_list.begin();

    while ((int)this->_list.size() > size)
    {
        this->_list.pop_back();
    }
}

void EnemyManager::draw() const
{
    for (const auto &enemy : this->_list)
    {
        enemy->draw();
    }
}

const std::vector<EnemyRef>& EnemyManager::list()
{
    return this->_list;
}

void EnemyManager::spawnEnemy()
{
    int type = rand() % 3;

    auto newEnemy = std::make_unique<Enemy>(this->data, type);
    float randomX = rand() % int(SCREEN_WIDTH - newEnemy->getGlobalBounds().width);
    newEnemy->setPosition(randomX, -newEnemy->getGlobalBounds().height);

    this->_list.push_back(std::move(newEnemy));
}

