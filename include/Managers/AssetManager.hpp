#pragma once
#include <SFML/Graphics/Shader.hpp>
#include <map>
#include <filesystem>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <string>
#include "Constants.hpp"

namespace managers
{   
    class AssetManager final {
    public:
        AssetManager() {}
        
        const sf::Font& get_font(const FONT_ID font_id) const;
        bool add_font(const FONT_ID font_id, const std::string& path_to_font);

        const sf::Texture& get_texture(const TEXTURE_ID texture_id) const;
        sf::Texture* get_texture_ptr(const TEXTURE_ID texture_id);
        bool add_texture(const TEXTURE_ID texture_id, const std::string& path_to_texture);

        sf::Shader* get_shader_ptr(const SHADER_ID shader_id) const;
        bool add_shader(const SHADER_ID shader_id, const sf::Shader::Type, const std::string& path_to_shader);

    private:
        std::map<const TEXTURE_ID, std::unique_ptr<sf::Texture>> textures;
        std::map<const FONT_ID, std::unique_ptr<sf::Font>> fonts;
        std::map<const SHADER_ID, std::unique_ptr<sf::Shader>> shaders;

    };
} // namespace game
