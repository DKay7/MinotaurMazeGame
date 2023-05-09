#include "Entities/Entity.hpp"
#include "Components/AnimationComponent.hpp"
#include "Components/MovementComponent.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <memory>

namespace game {
    Entity::Entity() { }

    void Entity::move(const float& delta_time, sf::Vector2f direction) {
        if (movement_component)
            movement_component->move(delta_time, direction);
    }

    void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(sprite, states);

        if (hitbox_component)
            target.draw(*hitbox_component);
    }

    const sf::Vector2f& Entity::get_position() const{
        if (hitbox_component)
            return hitbox_component->get_position();
        
        return sprite.getPosition();
    }


    void Entity::set_sprite_texture(const sf::Texture &texture_) {
        sprite.setTexture(texture_, true);
    }

    void Entity::set_position(sf::Vector2f position) {
        if (hitbox_component)
            hitbox_component->set_position(position);
        else
            sprite.setPosition(position);
    }
}



