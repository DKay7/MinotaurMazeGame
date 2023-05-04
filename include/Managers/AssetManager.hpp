#pragma once
#include <map>
#include <filesystem>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Constants.hpp"

namespace game
{   
    class AssetManager final {
    public:
        AssetManager() {}
        
        const sf::Font& get_font(const FONT_ID font_id) const;
        bool add_font(const FONT_ID font_id, const std::string& path_to_font);

        const sf::Texture& get_texture(const TEXTURE_ID texture_id) const;
        bool add_texture(const TEXTURE_ID texture_id, const std::string& path_to_texture);

    private:
        std::map<const TEXTURE_ID, std::unique_ptr<sf::Texture>> textures;
        std::map<const FONT_ID, std::unique_ptr<sf::Font>> fonts;


    };
} // namespace game
