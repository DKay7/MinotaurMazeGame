#pragma once

#include "Constants.hpp"
#include "Map/Tile.hpp"
#include "Map/TileMapCore.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <vector>

namespace game {

    class TileMap final: public sf::Drawable {
    public:
        TileMap(sf::Vector2f start_position_ = {0.f, 0.f}, sf::Vector2u map_size=Constants::map_size, uint32_t layers_num=Constants::layers_num, const float grid_size=Constants::grid_size);

        void update(const float delta_time);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        const float get_grid_size() const;
        void add_tile(uint32_t x, uint32_t y, uint32_t layer_num);
        void remove_tile(uint32_t x, uint32_t y, uint32_t layer_num);
        
    private:
        const float grid_size;
        sf::Vector2f start_position;
        engine::TileMapCore map;

    };
}