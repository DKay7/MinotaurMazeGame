#pragma once

#include "Components/AnimationComponent.hpp"
#include "Components/MovementComponent.hpp"
#include "Constants.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

namespace game {
    class Entity: public sf::Drawable {

    public:
        Entity();
        virtual ~Entity() = default;

        virtual void update(const float delta_time) = 0;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void move(const float& delta_time, sf::Vector2f direction);
    
        virtual const sf::Vector2f& get_position() const;

        void set_sprite_texture(const sf::Texture &texture);
        void set_position(const sf::Vector2f position);

        void create_animation_component(const sf::Texture &texture_sheet);
        void create_movement_component(const float max_velocity, const float acceleration = Constants::default_acceleration, const float deceleration = Constants::default_deceleration);

    protected:
        std::unique_ptr<AnimationComponent> animation_component;
        std::unique_ptr<MovementComponent> movement_component;

        sf::Sprite sprite;
     };
}
