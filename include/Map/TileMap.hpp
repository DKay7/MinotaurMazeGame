#pragma once

#include "Constants/Map.hpp"
#include "Context.hpp"
#include "Entities/Entity.hpp"
#include "Interfaces/SaveableInterface.hpp"
#include "Interfaces/LoadableInterface.hpp"
#include "Map/Tile.hpp"
#include "Map/TileMapCore.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <set>
#include <string>
#include <vector>

namespace map {

    class TileMap final: public sf::Drawable, 
                         public interfaces::Saveable<TileMap>, 
                         public interfaces::Loadable<TileMap> {
    public:
        TileMap(const TEXTURE_ID map_texture_id_, game_engine::Context* context,
                sf::Vector2u map_size=Constants::map_size, 
                uint32_t layers_num=Constants::layers_num, 
                const float grid_size=Constants::grid_size);

        // updating
        void update(const float delta_time);
        void update_world_bounds_collision(entities::Entity& entity, const float delta_time);
        void update_tiles_collision(entities::Entity& entity, const float delta_time);

        // drawing
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void draw_fogged_at_position(sf::RenderTarget& target, const sf::Vector2f position);

        // getters
        const float get_grid_size() const;
        const sf::Vector2u get_map_size() const;
        const sf::Texture& get_texture_sheet() const;
        const sf::FloatRect get_global_bounds() const;

        using coord_t = std::tuple<float, float, uint32_t>;
        const std::set<coord_t> get_spawn_points_coords() const;
        const std::set<coord_t> get_win_points_coords() const;
        const std::set<coord_t> get_tiles_coords_on_condition(std::function<bool(Tile*)> condition) const;

        // add/remove tiles
        void add_tile(const uint32_t x, const uint32_t y, const uint32_t layer_num, 
                      const sf::IntRect texture_rect, const int tile_type = TILE_TYPES_ID::DEFAULT);

        const bool add_tile_on_top_layer(const uint32_t x, const uint32_t y, const sf::IntRect texture_rect, 
                                   const int tile_type = TILE_TYPES_ID::DEFAULT);  
  
        void remove_tile(const uint32_t x, const uint32_t y, const uint32_t layer_num);
        const bool remove_tile_on_top_layer(const uint32_t x, const uint32_t y);

        // staticly inherited from Saveable and Loadable CRTP classes
        std::string serialize() const;
        static TileMap deserialize(std::stringstream file_content, game_engine::Context* context);
        
    private:
        const sf::Texture& tilemap_texture_sheet;
        const TEXTURE_ID map_texture_id;

        const float grid_size;
        sf::RectangleShape tilemap_bounds;
        
        map_engine::TileMapCore map;
    };
}