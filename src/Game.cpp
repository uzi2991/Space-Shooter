#include <Game.hpp>
#include <MenuState.hpp>

Game::Game(int width, int height, std::string title)
{
    srand(time(NULL));
    this->data->window.create(
        sf::VideoMode(width, height),
        title,
        sf::Style::Close | sf::Style::Titlebar);
    
    this->data->machine.addState(StateRef(std::make_unique<MenuState>(this->data)));
    
    this->run();
}

void Game::run()
{
    this->data->clock.restart();
    while (this->data->window.isOpen())
    {
        this->data->machine.processStateChanges();

        this->deltaTime = this->data->clock.restart().asSeconds();

        this->data->machine.getActiveState()->handleInput();

        this->data->machine.getActiveState()->update(this->deltaTime);
        
        this->data->machine.getActiveState()->draw();
    }
}