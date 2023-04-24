#include "Entities/Entity.hpp"
#include "Components/AnimationComponent.hpp"
#include "Components/MovementComponent.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <memory>

namespace game {
    Entity::Entity() { }

    void Entity::move(const float delta_time, sf::Vector2f direction) {
        if (movement_component)
            movement_component->move(delta_time, direction);
    }

    void Entity::draw(sf::RenderTarget &target) {
        target.draw(sprite);
    }

    void Entity::set_sprite_texture(const sf::Texture &texture_) {
        sprite.setTexture(texture_);
    }

    void Entity::set_position(sf::Vector2f position) {
        sprite.setPosition(position);
    }
    
    void Entity::create_animation_component(const sf::Texture &texture_sheet) {
        animation_component = std::make_unique<AnimationComponent>(sprite, texture_sheet);
    }

    void Entity::create_movement_component(const float max_velocity, const float acceleration, 
                                           const float deceleration) 
    {
        movement_component = std::make_unique<MovementComponent>(sprite, max_velocity, acceleration, deceleration);
    }
}



