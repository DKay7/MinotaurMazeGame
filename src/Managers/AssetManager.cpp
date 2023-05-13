#include "Managers/AssetManager.hpp"
#include <SFML/Graphics/Shader.hpp>
#include <stdexcept>


namespace managers {
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

    sf::Texture* AssetManager::get_texture_ptr(const TEXTURE_ID texture_id) {
        return textures.at(texture_id).get();
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

    sf::Shader* AssetManager::get_shader_ptr(const SHADER_ID shader_id) const {
        return shaders.at(shader_id).get();
    }

    bool AssetManager::add_shader(const SHADER_ID shader_id, const sf::Shader::Type shader_type, 
                                  const std::string& path_to_shader) 
    {
        if (shaders.find(shader_id) != shaders.end())
            return false;

        auto shader = std::make_unique<sf::Shader>();
        
        if (shader->loadFromFile(path_to_shader, shader_type)) {
            shaders[shader_id] = std::move(shader);
            return true;
        }

        throw std::runtime_error("Could not load shader at " + path_to_shader + "\n");
    }

} // namespace game
