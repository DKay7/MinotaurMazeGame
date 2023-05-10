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
#include <array>
#include <cstdint>
#include <fstream>
#include <ios>
#include <iostream>
#include <memory>
#include <assert.h>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace map {
    TileMap::TileMap(const TEXTURE_ID map_texture_id_, game_engine::Context* context, 
                     sf::Vector2u map_size, uint32_t layers_num, const float grid_size): 
            tilemap_texture_sheet(context->asset_manager->get_texture(map_texture_id_)), 
            map(map_size, layers_num), grid_size(grid_size), map_texture_id(map_texture_id_)
    
    { 
        /* constructor of map (TileMapCore class) already provides filling with nullptrs.*/ 
        tilemap_bounds = sf::RectangleShape(
            static_cast<sf::Vector2f>(map_size) * grid_size
        );

        tilemap_bounds.setFillColor(sf::Color::Transparent); // TODO
        tilemap_bounds.setOutlineColor(sf::Color::Magenta);
        tilemap_bounds.setOutlineThickness(3.f);
    }

//----------------------------------------ADD/REMOVE TILES----------------------------------------
    
    void TileMap::add_tile(const uint32_t x, const uint32_t y, const uint32_t layer_num, 
                          const sf::IntRect texture_rect, const bool collidable) {
        if (map[x, y, layer_num].get() != nullptr)
            return;

        auto coord = sf::Vector2f(x * grid_size, y * grid_size);
        map.insert(std::make_unique<Tile>(coord, grid_size, tilemap_texture_sheet, texture_rect, collidable), x, y, layer_num);
    }

    void TileMap::remove_tile(const uint32_t x, const uint32_t y, const uint32_t layer_num) {
        if (map[x, y, layer_num].get() == nullptr)
            return;

        map[x, y, layer_num].reset();
    }

//----------------------------------------UPDATING----------------------------------------

    void TileMap::update(const float delta_time) { }

    void TileMap::update_world_bounds_collision(entities::Entity& entity) {
        auto entity_pos = entity.get_hitbox_position();
        auto entity_bounds = entity.get_global_bounds();
        auto map_gridded_size =  map.get_size();
        auto map_size = sf::Vector2f{
            map_gridded_size.x * grid_size,
            map_gridded_size.y * grid_size
        };
        
        auto movement_component = entity.get_movement_component();

        if (entity_pos.x < 0) {
            entity.set_position({0, entity_pos.y});
            movement_component->stop_x();
        }

        else if (entity_pos.x + entity_bounds.width >= map_size.x) {
            entity.set_position({
                map_size.x - entity_bounds.width,
                entity_pos.y 
            });

            movement_component->stop_x();
        }

        entity_pos = entity.get_hitbox_position();
        entity_bounds = entity.get_global_bounds();
        
        if (entity_pos.y < 0) {
            entity.set_position({entity_pos.x, 0});
            movement_component->stop_y();
        }

        else if (entity_pos.y + entity_bounds.height >= map_size.y) {
            entity.set_position({
                entity_pos.x,
                map_size.y - entity_bounds.height
            });
            movement_component->stop_y();
        }
    }

    void TileMap::update_tiles_collision(entities::Entity& entity) {
        auto entity_pos = entity.get_position();
        auto entity_grid_pos = sf::Vector2i{
            static_cast<int>(entity_pos.x) / static_cast<int>(grid_size),
            static_cast<int>(entity_pos.y) / static_cast<int>(grid_size)
        };

        // checkig tiles around entity
        std::set<Tile*> tiles_around_player;
        // tiles_around_player.reserve(9 * map.get_layers_num()); // FIXME maybe optimize
        auto map_size = map.get_size();


        for (int x = -5, end_x = 5; x < end_x; ++x)
            for (int y = -5, end_y = 5; y < end_y; ++y)
                for (int layer_num = 0; layer_num < map.get_layers_num(); ++layer_num) {
                    
                    #define get_tile_coord_in_bounds(coord)                                             \
                        tile_##coord = tile_##coord >= 0 ? tile_##coord : 0;                            \
                        tile_##coord = tile_##coord < map_size.coord ? tile_##coord : map_size.coord - 1;

                    auto tile_x = entity_grid_pos.x + x;
                    auto tile_y =  entity_grid_pos.y + y;
                    get_tile_coord_in_bounds(x)
                    get_tile_coord_in_bounds(y)

                    if (auto tile = map[tile_x, tile_y, layer_num].get())
                        tiles_around_player.insert(tile);
                }

        for (auto& tile : tiles_around_player) {
            if (tile->is_collidable() and tile->intersects(entity.get_global_bounds())) {
                
                entity.get_movement_component()->stop();
                std::cout << "COLLISION AT " 
                          << static_cast<int>(tile->get_shape().getPosition().x) / static_cast<int>(grid_size) 
                          << ":" 
                          << static_cast<int>(tile->get_shape().getPosition().y) / static_cast<int>(grid_size)  
                          << "\n";
            }
        }
    }

//----------------------------------------DRAWING----------------------------------------

    void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        for (auto& tile : map) {
            if (tile)
                target.draw(*tile, states);
        }
        target.draw(tilemap_bounds);
    }

//----------------------------------------SAVE/LOAD----------------------------------------

    std::string TileMap::serialize() const {
        /*
            Saves map in next format:
            map_size_x map_size_y map_layers_num grid_size map_texture_id
            tile1_x tile1_y tile1_layer_num tile1_texture_rect_x tile1_texture_rect_y collidable
            tile2_x tile2_y tile2_layer_num tile2_texture_rect_x tile2_texture_rect_y collidable
            ...
        */

        std::stringstream result_ss;

        result_ss << map.get_size().x << " " << map.get_size().y << " " 
                  << map.get_layers_num() << " " << grid_size << " " 
                  << static_cast<int>(map_texture_id) << "\n";
        
        result_ss << map.serialize();

        return result_ss.str();
    }
    
    TileMap TileMap::deserialize(std::stringstream file_content, game_engine::Context* context) {
        /*
            Loads map in next format:
            map_size_x map_size_y map_layers_num grid_size map_texture_id
            tile1_x tile1_y tile1_layer_num tile1_texture_rect_x tile1_texture_rect_y collidable 
            tile2_x tile2_y tile2_layer_num tile2_texture_rect_x tile2_texture_rect_y collidable
            ...
        */

        sf::Vector2u map_size;
        uint32_t layers_num;
        float grid_size;
        int map_texture_id;

        file_content >> map_size.x >> map_size.y >> layers_num 
                     >> grid_size >> map_texture_id;
        
        TileMap loaded_map 
            = TileMap(static_cast<TEXTURE_ID>(map_texture_id), context,
                      map_size, layers_num, grid_size);

        uint32_t x, y, layer_num;
        sf::IntRect texture_rect;
        bool collidable;
        texture_rect.width = texture_rect.height = grid_size;
        while (file_content >> x >> y >> layer_num >> texture_rect.left >> texture_rect.top >> collidable) {
            loaded_map.add_tile(x, y, layer_num, texture_rect, collidable);
        }

        return loaded_map;
    }

    const float TileMap::get_grid_size() const {
        return grid_size;
    } 
    
    const sf::Vector2u TileMap::get_map_size() const {
        return map.get_size();
    }

    const sf::Texture& TileMap::get_texture_sheet() const {
        return tilemap_texture_sheet;
    }

    const sf::FloatRect TileMap::get_global_bounds() const {
        return tilemap_bounds.getGlobalBounds();
    }
}