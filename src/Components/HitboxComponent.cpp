#include "Components/HitboxComponent.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace components {
    HitboxComponent::HitboxComponent(sf::Sprite& sprite_, sf::Vector2f offset_, sf::Vector2f size):
        sprite(sprite_), offset(offset_) 
    {
        auto position = sprite.getPosition();
        hitbox.setPosition({
            position.x + offset.x,
            position.y + offset.y
        });

        next_position = {
            {0.f, 0.f}, size
        };

        hitbox.setSize(size);
        hitbox.setFillColor(sf::Color::Transparent);

        hitbox.setOutlineThickness(1.f); // TODO
        hitbox.setOutlineColor(sf::Color::Magenta); // TODO
    }

//----------------------------------------GETTERS----------------------------------------

    const sf::FloatRect& HitboxComponent::get_next_position(const sf::Vector2f& delta_pos) {
        auto hitbox_pos = get_position();
        next_position.left = hitbox_pos.x + delta_pos.x;
        next_position.top = hitbox_pos.y + delta_pos.y;

        return next_position;
    } 

    const sf::Vector2f& HitboxComponent::get_position() const {
        return hitbox.getPosition();
    }

    const sf::FloatRect HitboxComponent::get_global_bounds() const {
        return hitbox.getGlobalBounds();
    }

    const bool HitboxComponent::intersects(const sf::FloatRect& rect) const {
        return hitbox.getGlobalBounds().intersects(rect);
    }

//----------------------------------------SETTERS----------------------------------------

    void HitboxComponent::set_position(const sf::Vector2f& position) {
        hitbox.setPosition(position);
        sprite.setPosition({
            position.x - offset.x,
            position.y - offset.y
        });
    }

//----------------------------------------UPDATING----------------------------------------

    void HitboxComponent::update(const float delta_time) {
        auto position = sprite.getPosition();
        hitbox.setPosition({
            position.x + offset.x,
            position.y + offset.y
        });
    }

//----------------------------------------DRAW----------------------------------------

    void HitboxComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(hitbox, states);
        
    }

}