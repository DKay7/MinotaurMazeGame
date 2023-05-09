#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

namespace components {

    class HitboxComponent final : public sf::Drawable {
    public:
        HitboxComponent(sf::Sprite& sprite, sf::Vector2f offset, sf::Vector2f size);

        const sf::Vector2f& get_position() const;
        const bool intersects(const sf::FloatRect& rect) const;
        
        void set_position(const sf::Vector2f& position);

        void update(const float delta_time);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::RectangleShape hitbox;
        sf::Sprite& sprite;
        sf::Vector2f offset;

    };
}
