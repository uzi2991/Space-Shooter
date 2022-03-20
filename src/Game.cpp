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

    auto newEnemy = new Enemy(this->window, this->textures["enemy"]);
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
        this->bullets.push_back(new Bullet(this->window, this->textures["bullet"]));
        this->bullets.back()->setPosition(
            this->player->getBounds().left + this->player->getBounds().width / 2,
            this->player->getBounds().top
        );

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
    for (auto bullet : this->bullets) {
        sf::FloatRect rect = bullet->getBounds();
        if (rect.top + rect.height < 0.f) {
            delete bullet;
            deleted.insert(counter);
        } else {
            bullet->move(sf::Vector2f(0.f, -1.f), this->dt); 
        }

        ++counter;
    }

    if (!deleted.empty()) {
        std::vector<Bullet*> temp;
        for (int i = 0; i < (int)this->bullets.size(); ++i) {
            if (deleted.find(i) == deleted.end()) {
                temp.push_back(this->bullets[i]);
            }
        }

        this->bullets = temp;
    }
}

void Game::updateEnemies() {
    this->spawnEnemy();
    int counter = 0;
    std::set<int> deleted;
    for (auto enemy : this->enemies) {
        sf::FloatRect rect = enemy->getBounds();
        if (rect.top > Game::WINDOW_HEIGHT) {
            delete enemy;
            deleted.insert(counter);
        } else {
            enemy->move(sf::Vector2f(0.f, 1.f), this->dt); 
            enemy->update(this->dt);
        }

        ++counter;
    }

    if (!deleted.empty()) {
        std::vector<Enemy*> temp;
        for (int i = 0; i < (int)this->enemies.size(); ++i) {
            if (deleted.find(i) == deleted.end()) {
                temp.push_back(this->enemies[i]);
            }
        }

        this->enemies = temp;
    }
}

void Game::update() {
    // Check close window
    sf::Event ev;
    while (this->window->pollEvent(ev)) {
        if (ev.type == sf::Event::Closed) {
            this->window->close();
        }
    }

    // Measure time
    this->dt = this->clock.restart().asSeconds();
    this->bulletShootingTimer += this->dt;
    this->enemySpawnTimer += this->dt;

    this->background->update(dt);
    // Player input
    this->updatePlayerMovement();
    this->updatePlayerShooting();

    // Game logic
    this->updateCollision();
    this->updateBullets();
    this->updateEnemies();
    this->player->update(this->dt);
}

// Render functions

void Game::render() {
    // Clear
    this->window->clear(sf::Color::White);

    // Draw
    this->background->render();
    this->player->render();
    this->renderBullets();
    this->renderEnemies();

    std::cout << this->enemies.size() << " " << this->bullets.size() << "\n";

    // Display
    this->window->display();
}

void Game::renderBullets() {
    for (auto bullet: this->bullets) {
        bullet->render();
    }
}

void Game::renderEnemies() {
    for (auto enemy: this->enemies) {
        enemy->render();
    }
}


// Initialize Functions

void Game::initWindow() {
    this->window = new sf::RenderWindow(
        sf::VideoMode(Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT),
        "Space Shooter",
        sf::Style::Close | sf::Style::Titlebar
    );
}

void Game::initTextures() {
    this->textures["background"] = new sf::Texture();
    this->textures["background"]->loadFromFile("res/Graphics/backgrounds/desert-background.png");

    this->textures["player"] = new sf::Texture();
    this->textures["player"]->loadFromFile("res/Graphics/spritesheets/ship.png");

    this->textures["bullet"] = new sf::Texture();
    this->textures["bullet"]->loadFromFile("res/Graphics/spritesheets/bullet.png", sf::IntRect(0, 0, 16, 16));
    
    this->textures["enemy"] = new sf::Texture();
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

    this->player = new Player(this->window, this->textures["player"]);
    this->player->setPosition(
        this->window->getSize().x / 2 - this->player->getBounds().width / 2,
        this->window->getSize().y - this->player->getBounds().height
    );

    this->background = new Background(this->window, this->textures["background"]);

    srand(time(NULL));
}

// Destructor

Game::~Game() {
    // Delete window
    delete this->window;

    // Delete player
    delete this->player;

    // Delete background
    delete this->background;

    // Delete textures
    for (auto &it : this->textures) {
        delete it.second;
    }

    // Delete bullets
    for (auto it : this->bullets) {
        delete it;
    }

    // Delete enemies
    for (auto it : this->enemies) {
        delete it;
    }
}

// Run function

void Game::run() {
    while (this->window->isOpen()) {
        this->update();

        this->render();
    }
}