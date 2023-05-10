#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Vector2.hpp>

namespace components {

    class HitboxComponent final : public sf::Drawable {
    public:
        HitboxComponent(sf::Sprite& sprite, sf::Vector2f offset, sf::Vector2f size);

        // getters
        const sf::Vector2f get_position() const;
        const sf::FloatRect get_global_bounds() const;
        const bool intersects(const sf::FloatRect& rect) const;
        const sf::FloatRect& get_next_position(const sf::Vector2f& delta_pos);
        
        // setters
        void set_hitbox_position(const sf::Vector2f& position);

        // update
        void update_hitbox_position();
        void update_rotation(const sf::Vector2f movement_direction);

        // draw
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::FloatRect next_position;
        sf::RectangleShape hitbox;
        sf::Sprite& sprite;
        sf::Vector2f offset;

    };
}
