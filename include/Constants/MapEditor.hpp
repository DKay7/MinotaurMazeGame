#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

namespace Constants {
    // map editor
    const sf::Color mouse_rect_bg_color = {255, 255, 255, 150};
    const sf::Color mouse_rect_outline_color = sf::Color::Cyan;
    const sf::Vector2f selector_gui_pos = {40, 40};
    const int mouse_text_size = 12;
    const float editor_mouse_text_indent = 7;
}
