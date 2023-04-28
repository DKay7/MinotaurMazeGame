#include "Map/TileMapCore.hpp"
#include "Map/Tile.hpp"
#include "Map/TileMap.hpp"

namespace engine {
    TileMapCore::TileMapCore(sf::Vector2u map_size, uint32_t layers_num):
        map_size(map_size), layers_num(layers_num)
    {
        tilemap.reserve(map_size.x * map_size.y * layers_num);
    }

    game::Tile* TileMapCore::operator[](uint32_t x, uint32_t y, uint32_t layer_num) {
        return &tilemap[x * map_size.y + y * layers_num + layer_num];
    }

    void TileMapCore::push_back(game::Tile tile) {
        tilemap.push_back(tile);
    }

    TileMapCore::tilemap_t::iterator TileMapCore::begin() {
        return tilemap.begin();
    }

    TileMapCore::tilemap_t::iterator TileMapCore::end() {
        return tilemap.end();
    }

    TileMapCore::tilemap_t::const_iterator TileMapCore::begin() const {
        return tilemap.cbegin();
    }

    TileMapCore::tilemap_t::const_iterator TileMapCore::end() const {
        return tilemap.cend();
    }
}