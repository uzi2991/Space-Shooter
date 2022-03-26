#pragma once

#include <StateMachine.hpp>
#include <AssetManager.hpp>
#include <cstdlib>
#include <ctime>

struct GameData {
    StateMachine machine;
    sf::RenderWindow window;
    AssetManager assets;
    sf::Clock clock;
};

using GameDataRef = std::shared_ptr<GameData>;

class Game {
public:
    Game(int width, int height, std::string title);

private:
    float deltaTime;

    GameDataRef data = std::make_shared<GameData>();

    void run();
};