
#include "Map/Tile.hpp"
#include "Settings/Enums.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <sstream>

namespace map {
    
    Tile::Tile(const sf::Vector2f position, const float grid_size, 
               const sf::Texture &tile_texture, const sf::IntRect texture_rect,
               const int type): tile_type(type) {
        
        shape.setPosition(position);
        shape.setSize({grid_size, grid_size});

        shape.setTexture(&tile_texture);
        shape.setTextureRect(texture_rect);
        
        #ifndef NDEBUG
            if (tile_type & TILE_TYPES_ID::COLLIDABLE) {
                shape.setOutlineColor(sf::Color::Red);
                shape.setOutlineThickness(-1.f);
            }
            else
        #endif 
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
        return tile_type & TILE_TYPES_ID::COLLIDABLE;
    }

    const bool Tile::is_spawn_point() const {
        return tile_type & TILE_TYPES_ID::SPAWN_POINT;
    }

    const bool Tile::is_win_point() const {
        return tile_type & TILE_TYPES_ID::WIN_POINT;
    }

    const int Tile::get_tile_type() const {
        return tile_type;
    }

//----------------------------------------SETTERS----------------------------------------
    
    void Tile::set_texture(const sf::Texture &tile_texture) {
        shape.setTexture(&tile_texture);
    }

    void Tile::set_texture_rect(const sf::IntRect texture_rect) {
        shape.setTextureRect(texture_rect);
    }

    void Tile::add_type(const TILE_TYPES_ID type) {
        tile_type &= type;
    }

    void Tile::set_type(const TILE_TYPES_ID type) {
        tile_type = type;
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
                  << tile_type;

        return result_ss.str();
    } 


}