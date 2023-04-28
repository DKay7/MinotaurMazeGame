#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace game {
    class Tile: public sf::Drawable {
    public:
        Tile(sf::Vector2f position, const float grid_size, sf::Color shape_color=sf::Color::White);
        virtual ~Tile() = default;
        
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void update(const float delta_time);

    protected:
        sf::RectangleShape shape;

    private:

    };

}