#pragma once

#include "GUIElements/Button.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>

namespace utils {
    void center_text_on_window(sf::Text& text);
    const sf::Vector2f get_mouse_position(const sf::RenderWindow& window);
    std::unique_ptr<gui::Button> create_default_button(sf::Vector2f position, const sf::Font& font, std::string text);
}