
#include "Map/Tile.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <sstream>

namespace map {
    
    Tile::Tile(const sf::Vector2f position, const float grid_size, 
               const sf::Texture &tile_texture, const sf::IntRect texture_rect,
               const bool collidable_): collidable(collidable_) {
        
        shape.setPosition(position);
        shape.setSize({grid_size, grid_size});

        shape.setTexture(&tile_texture);
        shape.setTextureRect(texture_rect);
        
        if (collidable) {
            shape.setOutlineColor(sf::Color::Red); // TODO remove
            shape.setOutlineThickness(1.f);
        }
        else 
            shape.setOutlineColor(sf::Color::Transparent); 
    }

//----------------------------------------GETTERS----------------------------------------

    const sf::RectangleShape& Tile::get_shape() const {
        return shape;
    }

    const bool Tile::intersects(sf::FloatRect bounds) const {
        return shape.getGlobalBounds().intersects(bounds);
    }

    const bool Tile::is_collidable() const {
        return collidable;
    }

//----------------------------------------SETTERS----------------------------------------
    
    void Tile::set_texture(const sf::Texture &tile_texture) {
        shape.setTexture(&tile_texture);
    }

    void Tile::set_texture_rect(const sf::IntRect texture_rect) {
        shape.setTextureRect(texture_rect);
    }

    void Tile::set_collidable(const bool collidable_) {
        collidable = collidable_;
    }

//----------------------------------------UPDATING----------------------------------------

    void Tile::update(const float delta_time) { }

//----------------------------------------DRAWING----------------------------------------

    void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
            
        target.draw(shape, states);
    }

//----------------------------------------SAVING----------------------------------------

    std::string Tile::serialize() const {
        std::stringstream result_ss;
        
        auto& texture_rect = shape.getTextureRect();
        result_ss << texture_rect.left  << " " << texture_rect.top << " " 
                  << collidable;

        return result_ss.str();
    } 


}