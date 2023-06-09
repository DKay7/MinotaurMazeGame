#pragma once

#include "Interfaces/SaveableInterface.hpp"
#include "Map/Tile.hpp"
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <memory>
#include <vector>

namespace map_engine {
    class TileMapCore final: public interfaces::Saveable<TileMapCore> {
    public:
        using tilemap_t = std::vector<std::unique_ptr<map::Tile>>;

        TileMapCore(sf::Vector2u map_size, uint32_t layers_num);
        void push_back(std::unique_ptr<map::Tile> tile);
        
        void insert(std::unique_ptr<map::Tile> tile, uint32_t x, uint32_t y, uint32_t layer_num);

        std::unique_ptr<map::Tile>& operator[](uint32_t x, uint32_t y, uint32_t layer_num);
        uint64_t get_idx_from_coords(uint32_t x, uint32_t y, uint32_t layer_num) const;
        std::tuple<uint32_t, uint32_t, uint32_t> get_coords_from_idx(uint64_t position) const;

        tilemap_t::iterator begin();
        tilemap_t::iterator end();

        tilemap_t::const_iterator begin() const;
        tilemap_t::const_iterator end() const;

        const sf::Vector2u get_size() const;
        const uint32_t get_layers_num() const;

        // staticly inherited from Saveable CRTP class
        std::string serialize() const;
        

    private:
        sf::Vector2u map_size;
        uint32_t layers_num;
        tilemap_t tilemap;
    };
}