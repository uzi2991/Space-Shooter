#pragma once

#include <vector>
#include <Bullet.hpp>
#include <memory>
#include <algorithm>
#include <cstdlib>
#include <Bullet.hpp>


class BulletManager: public sf::Drawable {
private:
    std::vector<std::shared_ptr<Bullet>> data;

    sf::Texture texture;

    int windowWidth, windowHeight;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    void setWindowSize(int windowWidth, int windowHeigh);

    void setTexture(const sf::Texture& texture);
    
    const std::vector<std::shared_ptr<Bullet>>& list() const;

    void shootBullet(float x, float y);
    
    void update(float deltaTime);
};