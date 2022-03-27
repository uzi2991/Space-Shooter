#include <State.hpp>
#include <Game.hpp>
#include <Background.hpp>
#include <Player.hpp>
#include <EnemyManager.hpp>
#include <GameHUD.hpp>

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

    // Clock
    sf::Clock clock;

    // HUD
    std::unique_ptr<GameHUD> hud;

    // Background
    std::unique_ptr<Background> background;

    // Player
    std::unique_ptr<Player> player;
    int playerScore;

    // Enemies
    std::unique_ptr<EnemyManager> enemies;

    // Update Score
    void updateScore();

    // Collision Detection
    bool checkCollisionPlayerWithEnemies();
    void checkCollisionEnemiesWithBullets();
};