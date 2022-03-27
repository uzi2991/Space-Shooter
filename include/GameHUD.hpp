#pragma once

#include <Game.hpp>
#include <vector>

class GameHUD {
public:
    GameHUD(GameDataRef data);

    void draw() const;

    void updateScore(int score);

    void updateHP(int hp);

private:
    GameDataRef data;

    int hp;
    std::vector<sf::Sprite> hearts;

    int score;
    sf::Text scoreText;
    std::string scoreString;
};