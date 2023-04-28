#include "Managers/AssetManager.hpp"


namespace game
{
    const sf::Font& AssetManager::get_font(const FONT_ID font_id) const {
        return *(fonts.at(font_id).get());
    }

    bool AssetManager::add_font(const FONT_ID font_id, const std::string& path_to_font) {
        auto font = std::make_unique<sf::Font>();
        
        if (font->loadFromFile(path_to_font)) {
            fonts[font_id] = std::move(font);
            return true;
        }
        
        return false;
    }

    const sf::Texture& AssetManager::get_texture(const TEXTURE_ID texture_id) const {
        return *textures.at(texture_id);
    }

    bool AssetManager::add_texture(const TEXTURE_ID texture_id, const std::string& path_to_texture) {
        auto texture = std::make_unique<sf::Texture>();
        
        if (texture->loadFromFile(path_to_texture)) {
            textures[texture_id] = std::move(texture);
            return true;
        }

        return false;
    }

} // namespace game
