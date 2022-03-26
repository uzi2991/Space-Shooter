#include <Background.hpp>
#include <Definitions.hpp>

Background::Background(GameDataRef data) : data(data)
{
    this->sprite1.setTexture(this->data->assets.getTexture("background"));
    this->sprite2.setTexture(this->data->assets.getTexture("background"));

    this->sprite1.setScale(2.f, 2.f);
    this->sprite2.setScale(2.f, 2.f);

    this->height = this->sprite1.getGlobalBounds().height;
    this->speed = BACKGROUND_MOVE_SPEED;

    this->sprite1.setPosition(0.f, 0.f);
    this->sprite2.setPosition(0.f, this->height);
}

void Background::update(float dt)
{
    this->sprite1.move(0.f, this->speed * dt);
    this->sprite2.move(0.f, this->speed * dt);

    if (this->sprite1.getPosition().y >= this->height)
    {
        this->sprite1.setPosition(0.f, this->sprite2.getPosition().y - this->height);
    }

    if (this->sprite2.getPosition().y >= this->height)
    {
        this->sprite2.setPosition(0.f, this->sprite1.getPosition().y - this->height);
    }
}

void Background::draw() const
{
    this->data->window.draw(this->sprite1);
    this->data->window.draw(this->sprite2);
}
