#include "Map/TileMapCore.hpp"
#include "Map/Tile.hpp"
#include "Map/TileMap.hpp"
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <memory>
#include <sstream>
#include <string>
#include <tuple>

namespace engine {
    TileMapCore::TileMapCore(sf::Vector2u map_size, uint32_t layers_num):
        map_size(map_size), layers_num(layers_num),
        tilemap(map_size.x * map_size.y * layers_num)
    { }

    void TileMapCore::insert(std::unique_ptr<game::Tile> tile, uint32_t x, uint32_t y, uint32_t layer_num) {
        tilemap[get_idx_from_coords(x, y, layer_num)] = std::move(tile);
    }
    
    std::unique_ptr<game::Tile>& TileMapCore::operator[](uint32_t x, uint32_t y, uint32_t layer_num) {
        return tilemap[get_idx_from_coords(x, y, layer_num)];
    }
    
    uint64_t TileMapCore::get_idx_from_coords(uint32_t x, uint32_t y, uint32_t layer_num) const {
        assert (x < map_size.x);
        assert (y < map_size.y);
        assert (layer_num < layers_num);

        return x * map_size.y * layers_num + y * layers_num + layer_num;
    }

    std::tuple<uint32_t, uint32_t, uint32_t> TileMapCore::get_coords_from_idx(uint64_t index) const {
        /*
            DANGER: very hard math. 
            No one including me knows how it works
        */
        uint32_t layer_num = index % layers_num;
        uint32_t y = ((index - layer_num) / layers_num) % map_size.y;        
        uint32_t x = (index  - y * layers_num - layer_num) / (map_size.y * layers_num);

        return {x, y, layer_num};
    }

    const sf::Vector2u TileMapCore::get_size() const {
        return map_size;
    }

    const uint32_t TileMapCore::get_layers_num() const {
        return layers_num;
    }

    void TileMapCore::push_back(std::unique_ptr<game::Tile> tile) {
        tilemap.push_back(std::move(tile));
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

    std::string TileMapCore::serialize() const {
        std::stringstream result_ss;

        for (int tile_idx = 0; tile_idx < tilemap.size(); ++tile_idx) {
            if (!tilemap[tile_idx])
                continue;

            auto [x, y, layer_num] = get_coords_from_idx(tile_idx);
            result_ss << x << " " << y << " " << layer_num  << " "
                      << tilemap[tile_idx]->serialize()     << "\n";
        }

        return result_ss.str();
    }
}