#pragma once

#include "Map/Tile.hpp"
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <vector>

namespace engine {
    class TileMapCore final {
    public:
        using tilemap_t = std::vector<game::Tile>;

        TileMapCore(sf::Vector2u map_size, uint32_t layers_num);
        void push_back(game::Tile tile);
        
        game::Tile* operator[](uint32_t x, uint32_t y, uint32_t layer_num);

        tilemap_t::iterator begin();
        tilemap_t::iterator end();

        tilemap_t::const_iterator begin() const;
        tilemap_t::const_iterator end() const;

    private:
        sf::Vector2u map_size;
        uint32_t layers_num;
        tilemap_t tilemap;
    };
}