#pragma once

#include <vector>
#include <Enemy.hpp>
#include <memory>
#include <algorithm>
#include <cstdlib>


class EnemyManager: public sf::Drawable {
private:
    std::vector<std::shared_ptr<Enemy>> data;

    sf::Texture texture;

    int windowWidth, windowHeight;

    float totalTime;
    float spawnCoolDown;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    EnemyManager();
    
    void setWindowSize(int windowWidth, int windowHeigh);

    void setTexture(const sf::Texture& texture);
    
    const std::vector<std::shared_ptr<Enemy>>& list() const;

    void spawnEnemy();
    
    void update(float deltaTime);
};