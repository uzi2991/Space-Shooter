#pragma once

#include <State.hpp>
#include <Game.hpp>
#include <Background.hpp>

class GameOverState: public State {
public:
    GameOverState(GameDataRef data, int score);

    void init() override;

    void handleInput() override;

    void update(float deltaTime) override;

    void draw() const override;

private:
    GameDataRef data;
    int score;

    // Text
    std::string scoreString;
    sf::Text scoreText;
    std::string retryString;
    sf::Text retryText;

    // Background
    std::unique_ptr<Background> background;
};