#pragma once

#include <SFML/System/Vector2.hpp>

namespace settings {
    // map
    const sf::Vector2u map_size = {20, 20};
    const int layers_num = 3;
    const float grid_size = 48; 
    const int rebound_coef = 2;
    const int tiles_to_check = 8;
    const int fogged_map_size = 5;
}
