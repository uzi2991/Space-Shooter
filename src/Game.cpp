#include <Game.hpp>


// Constants

const int Game::WINDOW_WIDTH = 256 * 2;
const int Game::WINDOW_HEIGHT = 272 * 2;

// Game Logics

void Game::spawnEnemy() {
    if (this->enemySpawnTimer < this->enemySpawnMaxTimer) {
        return;
    }

    this->enemySpawnTimer -= this->enemySpawnMaxTimer;

    auto newEnemy = std::make_shared<Enemy>(this->window, this->textures["enemy"]);
    int randomXPos = rand() % (Game::WINDOW_WIDTH - int(newEnemy->getBounds().width));
    newEnemy->setPosition(randomXPos, -newEnemy->getBounds().height);

    this->enemies.push_back(newEnemy);
}

// Update functions

void Game::updatePlayerMovement() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        this->player->move(sf::Vector2f(0.f, -1.f), this->dt);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        this->player->move(sf::Vector2f(0.f, 1.f), this->dt);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        this->player->move(sf::Vector2f(-1.f, 0.f), this->dt);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        this->player->move(sf::Vector2f(1.f, 0.f), this->dt);
    }
}

void Game::updatePlayerShooting() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->bulletShootingTimer >= this->bulletShootingMaxTimer) {
        auto newBullet = std::make_shared<Bullet>(this->window, this->textures["bullet"]);
        newBullet->setPosition(
            this->player->getBounds().left + this->player->getBounds().width / 2,
            this->player->getBounds().top
        );
        this->bullets.push_back(newBullet);

        this->bulletShootingTimer = 0.f;
    }
}

void Game::updateCollision() {
    // Collision with screen
    sf::FloatRect playerRect = this->player->getBounds();

    // Upper
    if (playerRect.top < 0) {
        this->player->setPosition(playerRect.left, 0.f);
    }

    // Bottom
    if (playerRect.top > this->window->getSize().y - playerRect.height) {
        this->player->setPosition(
            playerRect.left, 
            this->window->getSize().y - playerRect.height
        );
    }

    // Left
    if (playerRect.left < 0) {
        this->player->setPosition(0.f, playerRect.top);
    }

    // Right
    if (playerRect.left > this->window->getSize().x - playerRect.width) {
        this->player->setPosition(
            this->window->getSize().x - playerRect.width, 
            playerRect.top
        );
    }
}

void Game::updateBullets() {
    int counter = 0;
    std::set<int> deleted;
    for (const auto& bullet : this->bullets) {
        sf::FloatRect rect = bullet->getBounds();
        if (rect.top + rect.height < 0.f) {
            deleted.insert(counter);
        } else {
            bullet->move(sf::Vector2f(0.f, -1.f), this->dt); 
        }

        ++counter;
    }

    if (!deleted.empty()) {
        std::vector<std::shared_ptr<Bullet>> temp;
        for (int i = 0; i < (int)this->bullets.size(); ++i) {
            if (deleted.find(i) == deleted.end()) {
                temp.push_back(this->bullets[i]);
            }
        }

        this->bullets = std::move(temp);
    }
}

void Game::updateEnemies() {
    this->spawnEnemy();
    int counter = 0;
    std::set<int> deleted;
    for (const auto& enemy : this->enemies) {
        sf::FloatRect rect = enemy->getBounds();
        if (rect.top > Game::WINDOW_HEIGHT) {
            deleted.insert(counter);
        } else if (this->checkCollisionEnemyWithBullets(enemy)) {
            deleted.insert(counter);
            this->updateScore();
        } else {
            enemy->move(sf::Vector2f(0.f, 1.f), this->dt); 
            enemy->update(this->dt);
        }

        ++counter;
    }

    if (!deleted.empty()) {
        std::vector<std::shared_ptr<Enemy>> temp;
        for (int i = 0; i < (int)this->enemies.size(); ++i) {
            if (deleted.find(i) == deleted.end()) {
                temp.push_back(this->enemies[i]);
            }
        }

        this->enemies = std::move(temp);
    }
}

void Game::updatePlaying() {
    this->bulletShootingTimer += this->dt;
    this->enemySpawnTimer += this->dt;

    // Player input
    this->updatePlayerMovement();
    this->updatePlayerShooting();

    // Game logic
    this->updateCollision();
    this->updateBullets();
    this->updateEnemies();
    if (this->checkCollisionPlayerWithEnemies()) {
        this->state = State::GAME_OVER;
    }
    this->player->update(this->dt);
}

void Game::updateAll() {
    // Measure time
    this->dt = this->clock.restart().asSeconds();

    // Check close window
    sf::Event ev;
    while (this->window->pollEvent(ev)) {
        if (ev.type == sf::Event::Closed) {
            this->window->close();
        }
    }

    this->background->update(dt);
}

// Misc

void Game::updateScore() {
    ++this->playerScore;
    this->scoreString = "Score: " + std::to_string(this->playerScore);
    this->scoreText.setString(this->scoreString);
}

bool Game::checkCollisionEnemyWithBullets(const std::shared_ptr<Enemy>& enemy) {
    int counter = 0;
    for (const auto& bullet: this->bullets) {
        if (enemy->getBounds().intersects(bullet->getBounds())) {
            this->bullets.erase(this->bullets.begin() + counter);
            return true;
        }

        ++counter;
    }

    return false;
}

bool Game::checkCollisionPlayerWithEnemies() {
    for (const auto& enemy: this->enemies) {
        if (this->player->getBounds().intersects(enemy->getBounds())) {
            return true;
        }
    }

    return false;
}

// Render functions

void Game::renderPlaying() {
    // Clear
    this->window->clear(sf::Color::White);

    // Draw
    this->background->render();
    this->player->render();
    this->renderBullets();
    this->renderEnemies();
    this->window->draw(this->scoreText);

    // Display
    this->window->display();
}

void Game::renderBullets() {
    for (const auto& bullet: this->bullets) {
        bullet->render();
    }
}

void Game::renderEnemies() {
    for (const auto& enemy: this->enemies) {
        enemy->render();
    }
}

void Game::renderGameOver() {
    // Clear
    this->window->clear(sf::Color::White);

    // Draw
    this->background->render();
    this->window->draw(this->scoreText);
    this->window->draw(this->gameOverText);

    // Display
    this->window->display();
}


// Initialize Functions

void Game::initWindow() {
    this->window = std::make_shared<sf::RenderWindow>(
        sf::VideoMode(Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT),
        "Space Shooter",
        sf::Style::Close | sf::Style::Titlebar
    );
}

void Game::initTextures() {
    this->textures["background"] = std::make_shared<sf::Texture>();
    this->textures["background"]->loadFromFile("res/Graphics/backgrounds/desert-background.png");

    this->textures["player"] = std::make_shared<sf::Texture>();
    this->textures["player"]->loadFromFile("res/Graphics/spritesheets/ship.png");

    this->textures["bullet"] = std::make_shared<sf::Texture>();
    this->textures["bullet"]->loadFromFile("res/Graphics/spritesheets/bullet.png", sf::IntRect(0, 0, 16, 16));
    
    this->textures["enemy"] = std::make_shared<sf::Texture>();
    this->textures["enemy"]->loadFromFile("res/Graphics/spritesheets/enemy-medium.png");

}

void Game::initBullets() {
    this->bulletShootingMaxTimer = 0.5f;
    this->bulletShootingTimer = this->bulletShootingMaxTimer;
}

void Game::initEnemies() {
    this->enemySpawnMaxTimer = 1.f;
    this->enemySpawnTimer = this->enemySpawnTimer;
}


// Constructor

Game::Game() {
    this->initWindow();
    this->initTextures();
    this->initBullets();
    this->initEnemies();

    this->player = std::make_shared<Player>(this->window, this->textures["player"]);
    this->player->setPosition(
        this->window->getSize().x / 2 - this->player->getBounds().width / 2,
        this->window->getSize().y - this->player->getBounds().height
    );

    this->background = std::make_shared<Background>(this->window, this->textures["background"]);
    this->state = State::PLAYING;

    this->font.loadFromFile("res/Fonts/Game Played.otf");
    this->scoreText.setFont(this->font);
    this->scoreText.setString("SCORE: 0");
    this->gameOverText.setFont(this->font);
    this->gameOverText.setString("GAME OVER!!!");
    this->gameOverText.setPosition(
        Game::WINDOW_WIDTH / 2 - this->gameOverText.getGlobalBounds().width / 2,
        Game::WINDOW_HEIGHT / 2 - this->gameOverText.getGlobalBounds().height / 2
    );

    this->playerScore = 0;

    srand(time(NULL));
}

// Run function

void Game::run() {
    while (this->window->isOpen()) {
        this->updateAll();
        if (this->state == State::PLAYING) {
            this->updatePlaying();
            this->renderPlaying();
        } else {
            this->renderGameOver();
        }
        

        
    }
}