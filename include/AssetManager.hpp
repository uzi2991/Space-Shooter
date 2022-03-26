#pragma once

#include <map>
#include <SFML/Graphics.hpp>

class AssetManager {
public:
    AssetManager() = default;
    ~AssetManager() = default;

    void loadTexture(const std::string& name, const std::string& filePath);
    const sf::Texture& getTexture(const std::string& name) const;

    void loadFont(const std::string& name, const std::string& filePath);
    const sf::Font& getFont(const std::string& name) const;

private:
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;
};