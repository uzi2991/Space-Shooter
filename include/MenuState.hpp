#pragma once

#include <State.hpp>
#include <Game.hpp>
#include <Background.hpp>

class MenuState : public State
{
public:
    MenuState(GameDataRef data);

    void init() override;

    void handleInput() override;

    void update(float deltaTime) override;

    void draw() const override;

private:
    GameDataRef data;

    // Text
    std::string enterString;
    sf::Text enterText;

    // Background
    std::unique_ptr<Background> background;
};
