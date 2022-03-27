#pragma once

#include <vector>
#include <Bullet.hpp>
#include <memory>
#include <algorithm>
#include <cstdlib>

using BulletRef = std::unique_ptr<Bullet> ;
class BulletManager
{
public:
    BulletManager(GameDataRef data, BulletType type);

    void update(float deltaTime);

    void draw() const;

    void spawnBullet(float x, float y, const sf::Vector2f& direction);

    const std::vector<BulletRef>& list();

private:
    GameDataRef data;

    std::vector<BulletRef> _list;

    BulletType type;
};