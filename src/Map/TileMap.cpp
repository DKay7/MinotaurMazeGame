#include "Map/TileMap.hpp"
#include "Constants.hpp"
#include "Context.hpp"
#include "Map/Tile.hpp"
#include <SFML/Config.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <memory>
#include <assert.h>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

namespace map {
    TileMap::TileMap(const TEXTURE_ID map_texture_id_, game_engine::Context* context, 
                     sf::Vector2f start_position_, sf::Vector2u map_size, 
                     uint32_t layers_num, const float grid_size): 
            tilemap_texture_sheet(context->asset_manager->get_texture(map_texture_id_)), 
            start_position(start_position_), map(map_size, layers_num), 
            grid_size(grid_size), map_texture_id(map_texture_id_)
    
    { 
        /* constructor of map (TileMapCore class) already provides filling with nullptrs.*/ 
        tilemap_bounds = sf::RectangleShape(
            static_cast<sf::Vector2f>(map_size) * grid_size
        );

        tilemap_bounds.setPosition(start_position);
        tilemap_bounds.setFillColor(sf::Color::Transparent); // TODO
        tilemap_bounds.setOutlineColor(sf::Color::Magenta);
        tilemap_bounds.setOutlineThickness(3.f);
    }
    
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
        target.draw(tilemap_bounds);
    }

    std::string TileMap::serialize() const {
        /*
            Saves map in next format:
            start_position_x start_position_y map_size_x map_size_y map_layers_num grid_size map_texture_id
            tile1_x tile1_y tile1_layer_num tile1_texture_rect_x tile1_texture_rect_y 
            tile2_x tile2_y tile2_layer_num tile2_texture_rect_x tile2_texture_rect_y
            ...
        */

        std::stringstream result_ss;

        result_ss << start_position.x << " " << start_position.y << " " 
                  << map.get_size().x << " " << map.get_size().y << " " 
                  << map.get_layers_num() << " " << grid_size << " " 
                  << static_cast<int>(map_texture_id) << "\n";
        
        result_ss << map.serialize();

        return result_ss.str();
    }
    
    TileMap TileMap::deserialize(std::stringstream file_content, game_engine::Context* context) {
        /*
            Loads map in next format:
            start_position_x start_position_y map_size_x map_size_y map_layers_num grid_size map_texture_id
            tile1_x tile1_y tile1_layer_num tile1_texture_rect_x tile1_texture_rect_y 
            tile2_x tile2_y tile2_layer_num tile2_texture_rect_x tile2_texture_rect_y
            ...
        */

        sf::Vector2f start_position;
        sf::Vector2u map_size;
        uint32_t layers_num;
        float grid_size;
        int map_texture_id;

        file_content >> start_position.x >> start_position.y 
                     >> map_size.x >> map_size.y >> layers_num 
                     >> grid_size >> map_texture_id;
        
        TileMap loaded_map 
            = TileMap(static_cast<TEXTURE_ID>(map_texture_id), context,
                      start_position, map_size, layers_num, grid_size);

        uint32_t x, y, layer_num;
        sf::IntRect texture_rect;
        texture_rect.width = texture_rect.height = grid_size;
        while (file_content >> x >> y >> layer_num >> texture_rect.left >> texture_rect.top) {
            loaded_map.add_tile(x, y, layer_num, texture_rect);
        }

        return loaded_map;
    }

    const float TileMap::get_grid_size() const {
        return grid_size;
    } 

    const sf::Texture& TileMap::get_texture_sheet() const {
        return tilemap_texture_sheet;
    }

    const sf::FloatRect TileMap::get_bounds() const {
        return tilemap_bounds.getGlobalBounds();
    }
}