#include <Animation.hpp>

Animation::Animation(sf::Sprite &sprite, float duration, int numFrames): sprite(sprite) {
    this->duration = duration;
    this->numFrames = numFrames;
    this->curFrame = 0;
    this->progess = 0.f;
    this->frameWidth = this->sprite.getTexture()->getSize().x / this->numFrames;

    this->frameRect.height = this->sprite.getTexture()->getSize().y;
    this->frameRect.width = this->frameWidth;
    this->frameRect.left = 0;
    this->frameRect.top = 0;

    this->sprite.setTextureRect(this->frameRect);
}

void Animation::update(float dt) {
    this->progess += dt;
    if (this->progess >= this->duration) {
        this->progess -= dt;
        ++this->curFrame;
        if (this->curFrame >= this->numFrames) {
            this->curFrame = 0;
        }

        this->frameRect.left = this->curFrame * this->frameWidth;
        this->sprite.setTextureRect(this->frameRect);
    }
}
