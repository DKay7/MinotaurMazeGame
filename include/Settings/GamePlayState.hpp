#pragma once
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

namespace settings {
    // gameplay state
    const sf::Color game_bg_back_color  = {255, 255, 255, 240};
    const sf::Color game_bg_front_color = {255, 255, 255, 100};
    const float bg_back_offset_coef  = 300;
    const float bg_front_offset_coef = 600;
    const int game_debug_mouse_text_indent = 7;
    const sf::Vector2f player_initial_coords = {60, 60};

}
