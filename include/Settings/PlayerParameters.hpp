#pragma once

#include <SFML/System/Vector2.hpp>

namespace settings {
    // player parameters
    const float player_movement_max_speed = 250;
    const float default_acceleration = 900;
    const float default_deceleration = 600;
    const sf::Vector2f player_hitbox_offset = {0, 0};
    const sf::Vector2f player_hitbox_size = {24, 48};
    const sf::Vector2f player_hitbox_idle_size = {24, 24};
}
