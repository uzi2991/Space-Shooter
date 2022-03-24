#include <Animation.hpp>

Animation::Animation(const sf::Vector2u& spriteSheetSize, int frameCount, float frameDuration) {
    this->totalTime = 0.f;

    this->frameDuration = frameDuration;

    this->curFrame = 0;

    this->frameCount = frameCount;

    this->frameRect.width = spriteSheetSize.x / this->frameCount;
    this->frameRect.height = spriteSheetSize.y;
    this->frameRect.left = 0;
    this->frameRect.top = 0;

}

void Animation::update(float deltaTime) {
    this->totalTime += deltaTime;

    if (this->totalTime >= this->frameDuration) {
        this->totalTime -= this->frameDuration;

        if (++this->curFrame >= this->frameCount) {
            this->curFrame = 0;
       
        }

        this->frameRect.left = this->curFrame * this->frameRect.width;
    }
}

void Animation::applyToSprite(sf::Sprite& sprite) const {
    sprite.setTextureRect(this->frameRect);
}

