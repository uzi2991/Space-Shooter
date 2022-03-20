#pragma once

#include <SFML/Graphics.hpp>
#include <Player.hpp>
#include <Bullet.hpp>
#include <Enemy.hpp>
#include <Background.hpp>
#include <map>
#include <vector>
#include <cstdlib>

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

    // Initialize Functions

    void initWindow();
    void initTextures();
    void initBullets();

    // Update functions

    void update();
    void updatePlayerMovement();
    void updatePlayerShooting();
    void updateCollision();
    void updateBullets();

    // Render functions

    void render();
    void renderBullets();

public:
    // Constructor

    Game();

    // Destructor

    ~Game();

    // Run function
    void run();
};