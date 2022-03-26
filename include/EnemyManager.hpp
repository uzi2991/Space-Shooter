#pragma once

#include <vector>
#include <Enemy.hpp>
#include <memory>
#include <algorithm>
#include <cstdlib>

using EnemyRef = std::unique_ptr<Enemy>; 
class EnemyManager {
private:
    GameDataRef data;

    std::vector<EnemyRef> _list;

    float totalTime;
    float spawnCoolDown;

public:
    EnemyManager(GameDataRef data);
    
    const std::vector<EnemyRef>& list();

    void spawnEnemy();
    
    void update(float deltaTime);

    void draw() const;
};