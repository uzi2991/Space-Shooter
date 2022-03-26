#include <State.hpp>
#include <Game.hpp>
#include <Background.hpp>
#include <Player.hpp>
#include <BulletManager.hpp>
#include <EnemyManager.hpp>

enum class GameStates {
    PLAYING,
    GAME_OVER
};

class GameState: public State {
public:
    GameState(GameDataRef data);

    void init() override;

    void handleInput() override;

    void update(float deltaTime) override;

    void draw() const override;

private:
    GameDataRef data;

    // State
    GameStates state;

    // Text
    std::string scoreString;
    sf::Text scoreText;

    // Background
    std::unique_ptr<Background> background;

    // Player
    std::unique_ptr<Player> player;
    int playerScore;

    // Bullets
    std::unique_ptr<BulletManager> bullets;
    float shootingTotalTime;

    // Enemies
    std::unique_ptr<EnemyManager> enemies;

    // Update Score
    void updateScore();

    // Collision Detection
    bool checkCollisionPlayerWithEnemies();
    void checkCollisionEnemiesWithBullets();
};