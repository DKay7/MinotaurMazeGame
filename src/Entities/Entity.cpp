#include "Entities/Entity.hpp"
#include "Components/AnimationComponent.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <memory>

namespace game {
    Entity::Entity() { }

    void Entity::move(const float delta_time, sf::Vector2f direction) {
        sprite.move(direction.x * movement_speed * delta_time, direction.y * movement_speed * delta_time);
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

}



