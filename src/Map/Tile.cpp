
#include "Map/Tile.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <sstream>

namespace game {
    
    Tile::Tile(const sf::Vector2f position, const float grid_size, 
               const sf::Texture &tile_texture, const sf::IntRect texture_rect) {
        
        shape.setPosition(position);
        shape.setSize({grid_size, grid_size});

        shape.setTexture(&tile_texture);
        shape.setTextureRect(texture_rect);
        
    }

    void Tile::set_texture(const sf::Texture &tile_texture) {
        shape.setTexture(&tile_texture);
    }

    void Tile::set_texture_rect(const sf::IntRect texture_rect) {
        shape.setTextureRect(texture_rect);
    }

    void Tile::update(const float delta_time) { }

    void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(shape, states);
    }

    const sf::RectangleShape& Tile::get_shape() const {
        return shape;
    }

    std::string Tile::serialize() const {
        std::stringstream result_ss;
        
        auto& texture_rect = shape.getTextureRect();
        result_ss << texture_rect.left  << " " << texture_rect.top;

        return result_ss.str();
    } 


}