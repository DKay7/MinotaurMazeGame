#pragma once

#include "Constants.hpp"
#include "Context.hpp"
#include "Map/Tile.hpp"
#include "Map/TileMapCore.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <string>
#include <vector>

namespace game {

    class TileMap final: public sf::Drawable {
    public:
        TileMap(const TEXTURE_ID map_texture_id, Context* context, 
                sf::Vector2f start_position_ = {0.f, 0.f}, 
                sf::Vector2u map_size=Constants::map_size, 
                uint32_t layers_num=Constants::layers_num, 
                const float grid_size=Constants::grid_size);


        void update(const float delta_time);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        const float get_grid_size() const;
        const sf::Texture& get_texture_sheet() const;
        
        void add_tile(const uint32_t x, const uint32_t y, const uint32_t layer_num, const sf::IntRect texture_rect);
        void remove_tile(const uint32_t x, const uint32_t y, const uint32_t layer_num);
        
        void save_map_to_file(std::string filename="aboba.map") const;
        
    private:
        const TEXTURE_ID map_texture_id;
        const sf::Texture& tilemap_texture_sheet;
        const float grid_size;
        sf::Vector2f start_position;
        engine::TileMapCore map;

    };

    std::unique_ptr<TileMap> load_map_from_file(std::string filename, Context* context);

}