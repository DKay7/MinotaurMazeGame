#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>

namespace utils {
    void center_text_on_window(sf::Text& text);
    const sf::Vector2f get_mouse_position(const sf::RenderWindow& window);
}