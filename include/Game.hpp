#pragma once

#include <SFML/Graphics.hpp>
#include <Player.hpp>
#include <Bullet.hpp>
#include <Background.hpp>
#include <EnemyManager.hpp>
#include <BulletManager.hpp>
#include <map>
#include <set>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>

enum class State {
    GAME_OVER,
    PLAYING
};

class Game {
private:
    // Constants
    static const int WINDOW_WIDTH, WINDOW_HEIGHT;

    // Window
    std::unique_ptr<sf::RenderWindow> window;

    // Clock and time
    sf::Clock clock;
    float dt;

    // Game State
    State state;

    // Fonts and Texts
    sf::Font font;
    std::string scoreString;
    sf::Text scoreText;

    // Textures
    std::map<std::string, std::shared_ptr<sf::Texture>> textures;

    // Background
    std::unique_ptr<Background> background;

    // Player
    std::unique_ptr<Player> player;
    int playerScore;

    // Bullets
    BulletManager bullets;
    float shootingCooldown;
    float shootingTotalTime;

    // Enemies
    EnemyManager enemies;

    // Initialize Functions
    void initWindow();
    void initTextures();
    void initBullets();
    void initEnemies();
    void initPlayer();

    // Handle input
    void handleInput();
    void handlePlayerInput();
    void handleSystemInput();

    // Game Logics
    void updateScore();
    bool checkCollisionPlayerWithEnemies();
    void checkCollisionEnemiesWithBullets();

    // Per frame Update functions
    void update();

    // Draw functions
    void draw();

public:
    // Constructor
    Game();

    // Run function
    void run();
};