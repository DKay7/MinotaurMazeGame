#pragma once

#include "Constants/Enums.hpp"
#include "Interfaces/SaveableInterface.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>


namespace map {
    class Tile final: public sf::Drawable, public interfaces::Saveable<Tile> {
    public:
        Tile(const sf::Vector2f position, const float grid_size, 
             const sf::Texture& tile_texture, const sf::IntRect texture_rect,
             const int type = TILE_TYPES_ID::DEFAULT);
             
        
        // getters
        const bool intersects(sf::FloatRect bounds) const;
        const sf::RectangleShape& get_shape() const;
        const bool is_collidable() const;
        const bool is_spawn_point() const;
        const bool is_win_point() const;
        const int get_tile_type() const;

        // setters
        void set_texture(const sf::Texture &tile_texture);
        void set_texture_rect(const sf::IntRect texture_rect);
        void set_collidable(const bool collidable);
        void add_type(const TILE_TYPES_ID type);
        void set_type(const TILE_TYPES_ID type);

        // update & draw        
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void update(const float delta_time);

        // saving
        std::string serialize() const;

    private:
        sf::RectangleShape shape;
        int tile_type;
    };

}