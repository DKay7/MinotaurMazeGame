#include "Managers/AssetManager.hpp"
#include <stdexcept>


namespace game
{
    const sf::Font& AssetManager::get_font(const FONT_ID font_id) const {
        return *fonts.at(font_id);
    }

    bool AssetManager::add_font(const FONT_ID font_id, const std::string& path_to_font) {

        if (fonts.find(font_id) != fonts.end())
            return false;

        auto font = std::make_unique<sf::Font>();
        
        if (font->loadFromFile(path_to_font)) {
            fonts[font_id] = std::move(font);
            return true;
        }
        
        throw std::runtime_error("Could not load font at " + path_to_font + "\n");
    }

    const sf::Texture& AssetManager::get_texture(const TEXTURE_ID texture_id) const {
        return *textures.at(texture_id);
    }

    bool AssetManager::add_texture(const TEXTURE_ID texture_id, const std::string& path_to_texture) {
        if (textures.find(texture_id) != textures.end())
            return false;

        auto texture = std::make_unique<sf::Texture>();
        
        if (texture->loadFromFile(path_to_texture)) {
            textures[texture_id] = std::move(texture);
            return true;
        }

        throw std::runtime_error("Could not load texture at " + path_to_texture + "\n");
    }

} // namespace game
