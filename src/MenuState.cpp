#include <MenuState.hpp>
#include <Definitions.hpp>
#include <GameState.hpp>

MenuState::MenuState(GameDataRef data) : data(data) {}

void MenuState::init()
{
    this->data->assets.loadFont("font", FONT_FILEPATH);
    this->data->assets.loadTexture("background", BACKGROUND_FILEPATH);

    this->background = std::make_unique<Background>(this->data);

    this->enterString = "PRESS ENTER TO PLAY!!!";
    this->enterText.setString(this->enterString);
    this->enterText.setOutlineColor(sf::Color::Black);
    this->enterText.setOutlineThickness(TEXT_OUTLINE_THICKNESS);
    this->enterText.setFont(this->data->assets.getFont("font"));

    this->enterText.setPosition(
        SCREEN_WIDTH / 2 - this->enterText.getGlobalBounds().width / 2,
        SCREEN_HEIGHT / 2 - this->enterText.getGlobalBounds().height / 2);
}

void MenuState::handleInput()
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
            // Check for entering the game
            else if (event.key.code == sf::Keyboard::Key::Enter)
            {
                this->data->machine.addState(StateRef(std::make_unique<GameState>(this->data)));
            }
        }
    }
}

void MenuState::update(float deltaTime)
{
    this->background->update(deltaTime);
}

void MenuState::draw() const {
    this->data->window.clear(sf::Color::White);

    this->background->draw();

    this->data->window.draw(this->enterText);
    
    this->data->window.display();
}