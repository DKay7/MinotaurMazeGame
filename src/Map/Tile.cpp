
#include "Map/Tile.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

namespace game {
    
    Tile::Tile(sf::Vector2f position, const float grid_size, sf::Color shape_color) {
        shape.setFillColor(shape_color);
        shape.setPosition(position);
        shape.setSize({grid_size, grid_size});
    }

    void Tile::update(const float delta_time) {

    }

    void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(shape, states);
    }

}