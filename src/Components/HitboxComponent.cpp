#include "Components/HitboxComponent.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <numbers>

namespace components {
    HitboxComponent::HitboxComponent(sf::Sprite& sprite_, sf::Vector2f offset_, sf::Vector2f size):
        sprite(sprite_), offset(offset_) 
    {   
        hitbox.setSize(size);
        hitbox.setFillColor(sf::Color::Transparent);
        
        hitbox.setOrigin({
            hitbox.getLocalBounds().width  / 2,
            hitbox.getLocalBounds().height / 2,
        });

        update_hitbox_position();

        next_position = {
            {0.f, 0.f}, size
        };

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

    const sf::Vector2f HitboxComponent::get_position() const {
        auto bounds = hitbox.getGlobalBounds();

        return {
            hitbox.getPosition().x - bounds.width  / 2,
            hitbox.getPosition().y - bounds.height / 2
        };
    }

    const sf::FloatRect HitboxComponent::get_global_bounds() const {
        auto bounds = hitbox.getGlobalBounds();
        return bounds;
    }

    const bool HitboxComponent::intersects(const sf::FloatRect& rect) const {
        return get_global_bounds().intersects(rect);
    }

//----------------------------------------SETTERS----------------------------------------

    void HitboxComponent::set_hitbox_position(const sf::Vector2f& position) {
        auto bounds = hitbox.getGlobalBounds();
        hitbox.setPosition({
            position.x + bounds.width  / 2,
            position.y + bounds.height / 2
        });

        auto hitbox_pos = hitbox.getPosition();
        auto sprite_bounds = sprite.getGlobalBounds();

        sprite.setPosition({
            hitbox_pos.x - sprite_bounds.width  / 2,
            hitbox_pos.y - sprite_bounds.height / 2,
        });
    }

//----------------------------------------UPDATING----------------------------------------

    void HitboxComponent::update_hitbox_position() {
        auto position = sprite.getPosition();
        auto bounds = sprite.getGlobalBounds();
        hitbox.setPosition({
            position.x + bounds.width  / 2,
            position.y + bounds.height / 2 
        });
    }

    void HitboxComponent::update_rotation(const sf::Vector2f movement_direction) {
        auto move_vec_len = std::sqrt(movement_direction.x * movement_direction.x + 
                                      movement_direction.y * movement_direction.y);
        
        auto angle = std::asin(movement_direction.y / move_vec_len) * (180 / std::numbers::pi) - 90;

        hitbox.setRotation(angle);
    }
//----------------------------------------DRAW----------------------------------------

    void HitboxComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(hitbox, states);
        
    }

}