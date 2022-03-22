#pragma once

#include <SFML/Graphics.hpp>
#include <Player.hpp>
#include <Bullet.hpp>
#include <Enemy.hpp>
#include <Background.hpp>
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
    
    std::shared_ptr<sf::RenderWindow> window;

    // Clock and time

    sf::Clock clock;
    float dt;

    // Fonts and Texts

    sf::Font font;
    std::string scoreString;
    sf::Text scoreText;
    sf::Text gameOverText;

    // Textures

    std::map<std::string, std::shared_ptr<sf::Texture>> textures;

    // Background

    std::shared_ptr<Background> background;

    // Player

    std::shared_ptr<Player> player;
    int playerScore;

    // Bullets

    std::vector<std::shared_ptr<Bullet>> bullets;
    float bulletShootingMaxTimer;
    float bulletShootingTimer;

    // Enemies

    std::vector<std::shared_ptr<Enemy>> enemies;
    float enemySpawnMaxTimer;
    float enemySpawnTimer;
    void spawnEnemy();

    // Initialize Functions

    void initWindow();
    void initTextures();
    void initBullets();
    void initEnemies();

    // Update functions

    void updatePlaying();
    void updatePlayerMovement();
    void updatePlayerShooting();
    void updateCollision();
    void updateBullets();
    void updateEnemies();

    // Misc

    void updateScore();

    // Collision

    bool checkCollisionEnemyWithBullets(const std::shared_ptr<Enemy>& enemy);
    bool checkCollisionPlayerWithEnemies();

    // Game states

    State state;

    // All state update

    void updateAll();

    // Render functions

    void renderPlaying();
    void renderBullets();
    void renderEnemies();
    void renderGameOver();

public:
    // Constructor

    Game();

    // Run function
    void run();
};