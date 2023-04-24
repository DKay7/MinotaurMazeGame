#pragma once

#include "../Components/AnimationComponent.hpp"
#include "Components/MovementComponent.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

namespace game {
    class Entity {

    public:
        Entity();
        virtual ~Entity() = default;

        virtual void update(const float delta_time) = 0;
        virtual void draw(sf::RenderTarget& target);
        virtual void move(const float delta_time, sf::Vector2f direction);

        void set_sprite_texture(const sf::Texture &texture);
        void set_position(const sf::Vector2f position);
        void create_animation_component(const sf::Texture &texture_sheet);
        void create_movement_component(const float max_velocity, const float acceleration = 15, const float deceleration = 0.1);

    protected:
        std::unique_ptr<AnimationComponent> animation_component;
        std::unique_ptr<MovementComponent> movement_component;

        sf::Sprite sprite;
     };
}
