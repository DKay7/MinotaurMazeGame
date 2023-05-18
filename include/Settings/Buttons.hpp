#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

namespace settings {
    // buttons
    const int default_bt_text_size = 15;
    const sf::Vector2f button_size = {75, 35};
    const sf::Color button_bg_color    = sf::Color::Transparent;
    const sf::Color button_text_idle   = sf::Color::White;
    const sf::Color button_text_hover  = {100, 107, 99};
    const sf::Color button_text_active = {46, 139, 87};
    const int button_bg_indent = 20;
}
