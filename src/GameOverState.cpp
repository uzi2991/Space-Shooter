#include <GameOverState.hpp>
#include <Definitions.hpp>
#include <GameState.hpp>

GameOverState::GameOverState(GameDataRef data, int score) : data(data), score(score) {}

void GameOverState::init()
{
    this->data->assets.loadFont("font", FONT_FILEPATH);
    this->data->assets.loadTexture("background", BACKGROUND_FILEPATH);

    this->background = std::make_unique<Background>(this->data);

    this->scoreString = "YOUR SCORE IS: " + std::to_string(this->score);
    this->scoreText.setString(this->scoreString);
    this->scoreText.setOutlineColor(sf::Color::Black);
    this->scoreText.setOutlineThickness(TEXT_OUTLINE_THICKNESS);
    this->scoreText.setFont(this->data->assets.getFont("font"));
    this->scoreText.setPosition(
        SCREEN_WIDTH / 2 - this->scoreText.getGlobalBounds().width / 2,
        SCREEN_HEIGHT / 2 - this->scoreText.getGlobalBounds().height);

    this->retryString = "PRESS ENTER TO TRY AGAIN!!!";
    this->retryText.setString(this->retryString);
    this->retryText.setOutlineColor(sf::Color::Black);
    this->retryText.setOutlineThickness(TEXT_OUTLINE_THICKNESS);
    this->retryText.setFont(this->data->assets.getFont("font"));
    this->retryText.setPosition(
        SCREEN_WIDTH / 2 - this->retryText.getGlobalBounds().width / 2,
        this->scoreText.getGlobalBounds().top + this->scoreText.getGlobalBounds().height + 10.f);
}

void GameOverState::handleInput()
{
    sf::Event event;
    while (this->data->window.pollEvent(event))
    {
        // Check for closing Window
        if (event.type == sf::Event::Closed)
        {
            this->data->window.close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            // Check for closing Window
            if (event.key.code == sf::Keyboard::Key::Escape)
            {
                this->data->window.close();
            }
            // Check for retrying the game
            else if (event.key.code == sf::Keyboard::Key::Enter)
            {
                this->data->machine.addState(StateRef(std::make_unique<GameState>(this->data)));
            }
        }
    }
}

void GameOverState::update(float deltaTime)
{
    this->background->update(deltaTime);
}

void GameOverState::draw() const
{
    this->data->window.clear(sf::Color::White);

    this->background->draw();

    this->data->window.draw(this->scoreText);
    this->data->window.draw(this->retryText);

    this->data->window.display();
}