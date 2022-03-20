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

class Game {
private:
    // Constants

    static const int WINDOW_WIDTH, WINDOW_HEIGHT;
    // Window
    
    sf::RenderWindow* window;

    // Clock and time
    sf::Clock clock;
    float dt;

    // Textures

    std::map<std::string, sf::Texture*> textures;

    // Background

    Background* background;

    // Player

    Player* player;

    // Bullets
    std::vector<Bullet*> bullets;
    float bulletShootingMaxTimer;
    float bulletShootingTimer;

    // Enemies
    std::vector<Enemy*> enemies;
    float enemySpawnMaxTimer;
    float enemySpawnTimer;
    void spawnEnemy();

    // Initialize Functions

    void initWindow();
    void initTextures();
    void initBullets();
    void initEnemies();

    // Update functions

    void update();
    void updatePlayerMovement();
    void updatePlayerShooting();
    void updateCollision();
    void updateBullets();
    void updateEnemies();

    // Render functions

    void render();
    void renderBullets();
    void renderEnemies();

public:
    // Constructor

    Game();

    // Destructor

    ~Game();

    // Run function
    void run();
};