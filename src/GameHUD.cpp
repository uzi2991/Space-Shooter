#include <GameHUD.hpp>
#include <Definitions.hpp>

GameHUD::GameHUD(GameDataRef data) : data(data)
{
    this->scoreText.setFont(this->data->assets.getFont("font"));
    this->scoreText.setOutlineColor(sf::Color::Black);
    this->scoreText.setOutlineThickness(TEXT_OUTLINE_THICKNESS);
    this->updateScore(0);

    this->hp = PLAYER_HEALTH;
    this->hearts.resize(this->hp);
    float x = 0.f;
    float y = this->scoreText.getGlobalBounds().top + this->scoreText.getGlobalBounds().height;
    for (auto& heart: this->hearts) {
        heart.setTexture(this->data->assets.getTexture("heart"));
        heart.setPosition(x, y);
        x += heart.getGlobalBounds().width;
    }
 
}

void GameHUD::draw() const
{
    this->data->window.draw(this->scoreText);

    for (int i = 0; i < this->hp; ++i) {
        this->data->window.draw(this->hearts[i]);
    }
}

void GameHUD::updateScore(int score)
{
    this->score = score;
    this->scoreString = "Score: " + std::to_string(this->score);
    this->scoreText.setString(this->scoreString);
}

void GameHUD::updateHP(int hp)
{
    this->hp = hp;
}
