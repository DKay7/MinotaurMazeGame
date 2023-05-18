#pragma once

#include "Constants/WindowParameters.hpp"
#include "Entities/Entity.hpp"
#include "GUIElements/Button.hpp"
#include "Map/TileMap.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

namespace utils {
    void center_text_on_window(sf::Text& text, sf::Vector2f position = sf::Vector2f({Constants::window_width / 2.f, Constants::window_height / 2.}));
    const sf::Vector2f get_mouse_position(const sf::RenderWindow& window);
    gui::Button create_default_button(sf::Vector2f position, const sf::Font& font, std::string text, bool centering=true);
    sf::Vector2i get_gridded_mouse(const sf::Vector2f mouse_pos, const float grid_size);
    std::string get_string_tile_types(const int tile_type);

    inline const float distance(sf::Vector2f v1, sf::Vector2f v2) {
        return std::sqrt(
                    std::pow(v1.x - v2.x, 2) + std::pow(v1.y - v2.y, 2)
                );
    }

    inline const char sign(int num) {
        return (-2 * std::signbit(num) + 1);
    } 
}