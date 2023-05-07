#pragma once

#include "Interfaces/SaveableInterface.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>


namespace map {
    class Tile: public sf::Drawable, public interfaces::Saveable<Tile> {
    public:
        Tile(const sf::Vector2f position, const float grid_size, 
             const sf::Texture& tile_texture, const sf::IntRect texture_rect);
             
        virtual ~Tile() = default;
        
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void update(const float delta_time);
        void set_texture(const sf::Texture &tile_texture);
        void set_texture_rect(const sf::IntRect texture_rect);
        
        std::string serialize() const;

        const sf::RectangleShape& get_shape() const;


    protected:
        sf::RectangleShape shape;

    private:

    };

}