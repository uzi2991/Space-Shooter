#pragma once

#include <SFML/Graphics.hpp>
#include <Game.hpp>

class Background {
public:
    Background(GameDataRef data);

    void update(float dt); 

    void draw() const;

private:
    sf::Sprite sprite1, sprite2;

    int height;

    float speed;

    GameDataRef data;
};