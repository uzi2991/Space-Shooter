#include <Game.hpp>


// Constants

const int Game::WINDOW_WIDTH = 256 * 2;
const int Game::WINDOW_HEIGHT = 272 * 2;

// Constructor
Game::Game() {
    this->initWindow();
    this->initTextures();
    this->initBullets();
    this->initEnemies();
    this->initPlayer();

    this->background = std::make_unique<Background>(*this->textures["background"]);

    this->state = State::PLAYING;

    this->font.loadFromFile("res/Fonts/Game Played.otf");
    this->scoreText.setFont(this->font);
    this->scoreText.setString("SCORE: 0");
    this->playerScore = 0;

    srand(time(NULL));
}

// Initialize Functions

void Game::initWindow() {
    this->window = std::make_unique<sf::RenderWindow>(
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
    this->bullets.setTexture(*this->textures.at("bullet"));
    this->bullets.setWindowSize(Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT);

    this->shootingCooldown = 0.5f;
    this->shootingTotalTime = this->shootingCooldown;
}

void Game::initEnemies() {
    this->enemies.setTexture(*this->textures.at("enemy"));
    this->enemies.setWindowSize(Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT);
}

void Game::initPlayer() {
    this->player = std::make_unique<Player>(*this->textures["player"], Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT);
    this->player->setPosition(
        Game::WINDOW_WIDTH / 2 - this->player->getGlobalBounds().width / 2,
        Game::WINDOW_HEIGHT - this->player->getGlobalBounds().height
    );
}

// Handle input

void Game::handleInput() {
    this->handleSystemInput();
    this->handlePlayerInput();
}

void Game::handlePlayerInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        this->player->moveLeft();
    } else {
        this->player->stopLeft();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        this->player->moveRight();
    } else {
        this->player->stopRight();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        this->player->moveUp();
    } else {
        this->player->stopUp();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        this->player->moveDown();
    } else {
        this->player->stopDown();
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->shootingTotalTime >= this->shootingCooldown) {
        this->shootingTotalTime = 0.f;
        this->bullets.shootBullet(
            this->player->getGlobalBounds().left + this->player->getGlobalBounds().width / 2,
            this->player->getGlobalBounds().top
        );
    }
}

void Game::handleSystemInput() {
    // Check close window
    sf::Event ev;
    while (this->window->pollEvent(ev)) {
        if (ev.type == sf::Event::Closed) {
            this->window->close();
        }
    }
}

// Update functions

void Game::update() {
    // Player input
    this->handleInput();

    // Game logic
    this->background->update(this->dt);
    this->player->update(this->dt);
    this->enemies.update(this->dt);
    this->bullets.update(this->dt);
    if (this->checkCollisionPlayerWithEnemies()) {
        this->state = State::GAME_OVER;
    }

    this->checkCollisionEnemiesWithBullets();

    std::cout << "Enemies: " << this->enemies.list().size() << "\n";
    std::cout << "Bullets: " << this->bullets.list().size() << "\n";
}

// Game Logics
void Game::updateScore() {
    ++this->playerScore;
    this->scoreString = "Score: " + std::to_string(this->playerScore);
    this->scoreText.setString(this->scoreString);
}

void Game::checkCollisionEnemiesWithBullets() {
    for (const auto& enemy: this->enemies.list()) {
        for (const auto& bullet: this->bullets.list()) {
            if (enemy->getGlobalBounds().intersects(bullet->getGlobalBounds())) {
                this->updateScore();
                enemy->setOut();
                bullet->setOut();
                break;
            }
        }
    }
}

bool Game::checkCollisionPlayerWithEnemies() {
    for (const auto& enemy: this->enemies.list()) {
        if (this->player->getGlobalBounds().intersects(enemy->getGlobalBounds())) {
            enemy->setOut();
            return true;
        }
    }

    return false;
}

// Draw functions
void Game::draw() {
    // Clear
    this->window->clear(sf::Color::White);

    // Draw
    this->window->draw(*this->background);
    this->window->draw(*this->player);
    this->window->draw(this->bullets);
    this->window->draw(this->enemies);
    this->window->draw(this->scoreText);

    // Display
    this->window->display();
}

// Run function
void Game::run() {
    this->clock.restart();
    while (this->window->isOpen() && this->state != State::GAME_OVER) {
        // Time
        this->dt = this->clock.restart().asSeconds();
        this->shootingTotalTime += this->dt;

        this->update();
        
        this->draw();
    }
}