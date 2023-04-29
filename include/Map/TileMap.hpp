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
        TileMap(sf::Vector2u map_size, uint32_t layers_num, const float grid_size=Constants::grid_size);

        void update(const float delta_time);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        const float grid_size;

        engine::TileMapCore map;

    };
}