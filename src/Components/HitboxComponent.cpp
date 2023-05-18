#include "Components/HitboxComponent.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <numbers>

namespace components {
    HitboxComponent::HitboxComponent(sf::Sprite& sprite_, sf::Vector2f offset_, 
                                     sf::Vector2f size, sf::Vector2f idle_size_):
        sprite(sprite_), offset(offset_), default_size(size), idle_size(idle_size_)
    {   
        hitbox.setSize(idle_size_);
        hitbox.setFillColor(sf::Color::Transparent);
        
        update_hitbox_position();

        next_position = {
            {0.f, 0.f}, size
        };
        
        #ifndef NDEBUG
            hitbox.setOutlineThickness(-1.f);                
            hitbox.setOutlineColor(sf::Color::Magenta);
        #endif
    }

//----------------------------------------GETTERS----------------------------------------

    const sf::FloatRect& HitboxComponent::get_next_position_bounds(const sf::Vector2f& delta_pos) {
        auto hitbox_pos = get_position();
        auto hitbox_bounds = get_global_bounds();
        next_position = {
            hitbox_pos.x + delta_pos.x,
            hitbox_pos.y + delta_pos.y,
            hitbox_bounds.width, hitbox_bounds.height
        };

        return next_position;
    } 

    const sf::Vector2f HitboxComponent::get_position() const {
        auto bounds = get_global_bounds();

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
        auto bounds = get_global_bounds();
        hitbox.setPosition({
            position.x + bounds.width  / 2,
            position.y + bounds.height / 2
        });

        // after we set hitbox position we have to update the sprite position
        auto hitbox_pos = hitbox.getPosition();
        auto sprite_bounds = sprite.getGlobalBounds();

        sprite.setPosition({
            hitbox_pos.x - sprite_bounds.width  / 2.f,
            hitbox_pos.y - sprite_bounds.height / 2.f,
        });
    }

//----------------------------------------UPDATING----------------------------------------

    void HitboxComponent::update_hitbox_position() {
        // updating hitbox position to make it coordinated with sprite position

        hitbox.setOrigin({
            hitbox.getLocalBounds().width  / 2,
            hitbox.getLocalBounds().height / 2,
        });

        auto position = sprite.getPosition();
        auto bounds = sprite.getGlobalBounds();
        hitbox.setPosition({
            position.x + bounds.width  / 2.f,
            position.y + bounds.height / 2.f 
        });
    }

    void HitboxComponent::update_rotation(const sf::Vector2f movement_direction) {

        // movement direction is always unit vector      
        auto angle = std::asin(movement_direction.y) * (180 / std::numbers::pi) - 90;

        hitbox.setRotation(angle);
    }

    void HitboxComponent::update_idle(const bool is_idle) {
        if (is_idle) {
            hitbox.setSize(idle_size);
            hitbox.setRotation(0);
            update_hitbox_position();
        }
        else
            hitbox.setSize(default_size);

    }

//----------------------------------------DRAW----------------------------------------

    void HitboxComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(hitbox, states); 
    }
}