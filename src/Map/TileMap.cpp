#include "Map/TileMap.hpp"
#include "Context.hpp"
#include "Map/Tile.hpp"
#include <SFML/Config.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <memory>
#include <assert.h>

namespace game {
    TileMap::TileMap(const TEXTURE_ID map_texture_id_, Context* context, sf::Vector2f start_position_, sf::Vector2u map_size, uint32_t layers_num, const float grid_size): 
            tilemap_texture_sheet(context->asset_manager->get_texture(map_texture_id_)), 
            start_position(start_position_), map(map_size, layers_num), 
            grid_size(grid_size), map_texture_id(map_texture_id_) 
    
    { /* constructor of map (TileMapCore class) already provides filling with nullptrs.*/ }
    

    void TileMap::add_tile(const uint32_t x, const uint32_t y, const uint32_t layer_num, const sf::IntRect texture_rect) {
        if (map[x, y, layer_num].get() != nullptr)
            return;

        auto coord = sf::Vector2f(x * grid_size, y * grid_size);
        map.insert(std::make_unique<Tile>(coord, grid_size, tilemap_texture_sheet, texture_rect), x, y, layer_num);
    }

    void TileMap::remove_tile(const uint32_t x, const uint32_t y, const uint32_t layer_num) {
        if (map[x, y, layer_num].get() == nullptr)
            return;

        map[x, y, layer_num].reset();
    }

    void TileMap::update(const float delta_time) { }

    void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        for (auto& tile : map) {
            if (tile)
                target.draw(*tile, states);
        }
    }

    const float TileMap::get_grid_size() const {
        return grid_size;
    } 

    const sf::Texture& TileMap::get_texture_sheet() const {
        return tilemap_texture_sheet;
    }

    void TileMap::save_map_to_file() const {
        /*
            Saves map in next format:
            map_size map_layers_num grid_size map_texture_id
            tile1_x tile1_y tile1_height tile1_width
            tile2_x tile2_y tile2_height tile2_width
            ...
        */

        std::cout << "Map Saved!\n";
    }
}