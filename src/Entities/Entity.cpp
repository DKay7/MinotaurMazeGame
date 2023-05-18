#include "Entities/Entity.hpp"
#include "Components/AnimationComponent.hpp"
#include "Components/HitboxComponent.hpp"
#include "Components/MovementComponent.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <memory>

namespace entities {
    Entity::Entity() { }

    void Entity::move(const float& delta_time, const sf::Vector2f direction) {
        if (movement_component)
            movement_component->move(delta_time, direction);
        if (hitbox_component)
            hitbox_component->update_rotation(direction);
    }

    void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(sprite, states);

        if (hitbox_component)
            target.draw(*hitbox_component);
    }

//----------------------------------------GETTERS----------------------------------------
    
    components::MovementComponent* Entity::get_movement_component() const {
        return movement_component.get();
    }

    components::HitboxComponent* Entity::get_hitbox_component() const {
        return hitbox_component.get();
    }

    const sf::Vector2f Entity::get_position() const{
        return sprite.getPosition();
    }

    const sf::Vector2f Entity::get_hitbox_position() const {
        if (hitbox_component)
            return hitbox_component->get_position();
        return get_position();
    }

    const sf::FloatRect Entity::get_global_bounds() const {
        if (hitbox_component)
            return hitbox_component->get_global_bounds();

        return sprite.getGlobalBounds();
    }
    
    //----------------------------------------SETTERS----------------------------------------
    
    void Entity::set_sprite_texture(const sf::Texture &texture_) {
        sprite.setTexture(texture_);
    }

    void Entity::set_position(sf::Vector2f position) {
        if (hitbox_component)
            hitbox_component->set_hitbox_position(position);
        else
            sprite.setPosition(position);
    }
}



