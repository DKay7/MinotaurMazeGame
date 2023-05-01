#pragma once

#include "Constants.hpp"
#include "GUIElements/Button.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>

namespace utils {
    void center_text_on_window(sf::Text& text, sf::Vector2f position = sf::Vector2f({game::Constants::window_width / 2.f, game::Constants::window_height / 2.}));
    const sf::Vector2f get_mouse_position(const sf::RenderWindow& window);
    gui::Button create_default_button(sf::Vector2f position, const sf::Font& font, std::string text, bool centering=true);
    sf::Vector2u get_gridded_mouse(const sf::Vector2f mouse_pos, const float grid_size);
    
}