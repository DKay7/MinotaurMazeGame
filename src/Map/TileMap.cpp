#include "Map/TileMap.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <memory>

namespace game {
    TileMap::TileMap(sf::Vector2u map_size, uint32_t layers_num, const float grid_size): 
    map(map_size, layers_num), grid_size(grid_size) 
    
    {    
        for (uint32_t col_idx = 0; col_idx < map_size.x; ++col_idx) {
            for (uint32_t row_idx = 0; row_idx < map_size.y; ++row_idx) {
                for (uint32_t layer = 0; layer < layers_num; ++layer) {
                    map.push_back(Tile(sf::Vector2f(col_idx * grid_size, row_idx * grid_size), grid_size, 
                        sf::Color((static_cast<float>(col_idx) /  map_size.x) * 255, (static_cast<float>(row_idx) / map_size.y) * 255, layer)));
                }
            }
        }
    }
    
    void update(const float delta_time) {

    }

    void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        for (auto& tile : map) {
            target.draw(tile, states);
        }
    }

}