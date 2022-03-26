#include <AssetManager.hpp>

void AssetManager::loadTexture(const std::string &name, const std::string &filePath)
{
    sf::Texture tex;
    if (tex.loadFromFile(filePath))
    {
        this->textures[name] = tex;
    }
}

const sf::Texture &AssetManager::getTexture(const std::string &name) const
{
    return this->textures.at(name);
}

void AssetManager::loadFont(const std::string &name, const std::string &filePath)
{
    sf::Font font;
    if (font.loadFromFile(filePath))
    {
        this->fonts[name] = font;
    }
}

const sf::Font &AssetManager::getFont(const std::string &name) const
{
    return this->fonts.at(name);
}
