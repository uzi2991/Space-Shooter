#include <Game.hpp>

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
        this->bullets.push_back(new Bullet(this->textures["bullet"]));
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

    for (auto bullet : this->bullets) {
        sf::FloatRect rect = bullet->getBounds();
        if (rect.left + rect.height < 0.f) {
            delete bullet;
            this->bullets.erase(this->bullets.begin() + counter);
        } else {
            bullet->move(sf::Vector2f(0.f, -1.f), this->dt); 
        }

        ++counter;
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

    // Player input
    this->updatePlayerMovement();
    this->updatePlayerShooting();

    // Game logic
    this->updateCollision();
    this->updateBullets();
    this->player->update(this->dt);
}

// Render functions

void Game::render() {
    // Clear
    this->window->clear(sf::Color::White);

    // Draw
    this->window->draw(this->background);
    this->player->render(this->window);
    this->renderBullets();

    // Display
    this->window->display();
}

void Game::renderBullets() {
    for (auto bullet: this->bullets) {
        bullet->render(this->window);
    }
}


// Initialize Functions

void Game::initWindow() {
    this->window = new sf::RenderWindow(
        sf::VideoMode(600, 600),
        "Space Shooter",
        sf::Style::Close | sf::Style::Titlebar
    );
    this->window->setFramerateLimit(120);
}

void Game::initTextures() {
    this->textures["background"] = new sf::Texture();
    this->textures["background"]->loadFromFile("res/Graphics/backgrounds/desert-background.png");

    this->textures["player"] = new sf::Texture();
    this->textures["player"]->loadFromFile("res/Graphics/spritesheets/ship.png");

    this->textures["bullet"] = new sf::Texture();
    this->textures["bullet"]->loadFromFile("res/Graphics/spritesheets/bullet.png", sf::IntRect(0, 0, 16, 16));
    
    this->textures["enemy"] = new sf::Texture();
    this->textures["enemy"]->loadFromFile(
        "res/Graphics/spritesheets/enemy-medium.png",
        sf::IntRect(0, 0, 32, 8)
    );

}

void Game::initBullets() {
    this->bulletShootingMaxTimer = 0.5f;
    this->bulletShootingTimer = this->bulletShootingMaxTimer;
}


// Constructor

Game::Game() {
    this->initWindow();
    this->initTextures();
    this->initBullets();

    this->player = new Player(this->textures["player"]);
    this->player->setPosition(
        this->window->getSize().x / 2 - this->player->getBounds().width / 2,
        this->window->getSize().y - this->player->getBounds().height
    );

    this->background.setTexture(*this->textures["background"]);
    this->background.setPosition(0.f, 0.f);
}

// Destructor

Game::~Game() {
    // Delete window
    delete this->window;

    // Delete player
    delete this->player;

    // Delete textures
    for (auto &it : this->textures) {
        delete it.second;
    }

    // Delete bullets
    for (auto it : this->bullets) {
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