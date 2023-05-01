#include "Map/TileMap.hpp"
#include "Map/Tile.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <memory>
#include <assert.h>

namespace game {
    TileMap::TileMap(sf::Vector2f start_position_, sf::Vector2u map_size, uint32_t layers_num, const float grid_size): 
    start_position(start_position_), map(map_size, layers_num), grid_size(grid_size) 
    
    {    
        for (uint32_t col_idx = 0; col_idx < map_size.x; ++col_idx) {
            for (uint32_t row_idx = 0; row_idx < map_size.y; ++row_idx) {
                for (uint32_t layer = 0; layer < layers_num; ++layer) {
                    auto coord = 
                        sf::Vector2f(start_position.x + col_idx * grid_size, 
                                     start_position.y + row_idx * grid_size);
                    // map.push_back(std::make_unique<Tile>(coord, layer));
                    map.push_back(nullptr);
                    // map.push_back(std::make_unique<Tile>(sf::Vector2f(start_position.x + col_idx * grid_size, start_position.y + row_idx * grid_size), grid_size, 
                    //     sf::Color((static_cast<float>(col_idx) /  map_size.x) * 255, (static_cast<float>(row_idx) / map_size.y) * 255, layer)));
                }
            }
        }
    }
    
    void TileMap::add_tile(uint32_t x, uint32_t y, uint32_t layer_num) {
        if (map[x, y, layer_num].get() != nullptr)
            return;

        auto coord = sf::Vector2f(x * grid_size, y * grid_size);
        map.insert(std::make_unique<Tile>(coord, grid_size, sf::Color::Green), x, y, layer_num);
    }

    void TileMap::remove_tile(uint32_t x, uint32_t y, uint32_t layer_num) {
        if (map[x, y, layer_num].get() == nullptr)
            return;

        map[x, y, layer_num].reset();

    }


    void TileMap::update(const float delta_time) {

    }

    void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        for (auto& tile : map) {
            if (tile)
                target.draw(*tile, states);
        }
    }

    const float TileMap::get_grid_size() const {
        return grid_size;
    }    
}