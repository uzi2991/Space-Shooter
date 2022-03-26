#pragma once

#include <vector>
#include <Bullet.hpp>
#include <memory>
#include <algorithm>
#include <cstdlib>


class BulletManager {
public:
    BulletManager(GameDataRef data);
    
    std::vector<Bullet>& list();

    void shootBullet(float x, float y);
    
    void update(float deltaTime);

    void draw() const;

private:
    std::vector<Bullet> _list;

    GameDataRef data;

};