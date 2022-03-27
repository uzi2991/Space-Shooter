#include <GameState.hpp>
#include <Definitions.hpp>
#include <iostream>
#include <GameOverState.hpp>

GameState::GameState(GameDataRef data) : data(data) {}

void GameState::init()
{
    this->state = GameStates::PLAYING;
    this->data->assets.loadFont("font", FONT_FILEPATH);
    this->data->assets.loadTexture("background", BACKGROUND_FILEPATH);
    this->data->assets.loadTexture("player", PLAYER_FILEPATH);
    this->data->assets.loadTexture("bullet", BULLET_FILEPATH);
    this->data->assets.loadTexture("big enemy", BIG_ENEMY_FILEPATH);
    this->data->assets.loadTexture("medium enemy", MEDIUM_ENEMY_FILEPATH);
    this->data->assets.loadTexture("small enemy", SMALL_ENEMY_FILEPATH);
    this->data->assets.loadTexture("heart", HEART_FILEPATH);

    this->hud = std::make_unique<GameHUD>(this->data);

    this->background = std::make_unique<Background>(this->data);

    this->player = std::make_unique<Player>(this->data);
    this->player->setPosition(
        SCREEN_WIDTH / 2 - this->player->getGlobalBounds().width,
        SCREEN_HEIGHT - this->player->getGlobalBounds().height);
    this->playerScore = 0;

    this->enemies = std::make_unique<EnemyManager>(this->data);

    this->data->clock.restart();
}

void GameState::handleInput()
{
    // Check for closing Window
    sf::Event event;
    while (this->data->window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            this->data->window.close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Key::Escape)
            {
                this->data->window.close();
            }
        }
    }

    if (this->state == GameStates::PLAYING)
    {
        // Check for player input
        this->player->handleInput();
    }
}

void GameState::update(float deltaTime)
{   
    if (this->state == GameStates::GAME_OVER && this->clock.getElapsedTime().asSeconds() >= GAME_OVER_DELAY_TIME) {
        this->data->machine.addState(StateRef(std::make_unique<GameOverState>(this->data, this->playerScore)));
    }

    this->background->update(deltaTime);
    this->enemies->update(deltaTime);

    if (this->state == GameStates::PLAYING)
    {
        this->player->update(deltaTime);
        if (this->checkCollisionPlayerWithEnemies())
        {   
            if (this->player->takeHit())
            {
                this->state = GameStates::GAME_OVER;
                this->clock.restart();
            }

            this->hud->updateHP(this->player->getHP());      
        }   

        this->checkCollisionEnemiesWithBullets();
    }

    // std::cout << this->enemies->list().size() << " " << this->bullets->list().size() << '\n';
}

void GameState::draw() const
{
    // Clear the screen
    this->data->window.clear(sf::Color::White);

    // Draw
    this->background->draw();
    if (this->state == GameStates::PLAYING)
    {
        this->player->draw();
    }

    this->enemies->draw();
    
    this->hud->draw();

    // Display
    this->data->window.display();
}


bool GameState::checkCollisionPlayerWithEnemies()
{
    for (const auto &enemy : this->enemies->list())
    {
        if (this->player->getGlobalBounds().intersects(enemy->getGlobalBounds()))
        {
            enemy->setOut();
            return true;
        }
    }

    return false;
}

void GameState::checkCollisionEnemiesWithBullets()
{
    for (const auto &enemy : this->enemies->list())
    {
        for (const auto &bullet : this->player->bullets())
        {
            if (enemy->getGlobalBounds().intersects(bullet->getGlobalBounds()))
            {
                this->hud->updateScore(++this->playerScore);
                enemy->setOut();
                bullet->setOut();
                break;
            }
        }
    }
}
