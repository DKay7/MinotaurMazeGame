#pragma once

#include "Components/AnimationComponent.hpp"
#include "Components/HitboxComponent.hpp"
#include "Components/MovementComponent.hpp"
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

namespace entities {
    class Entity: public sf::Drawable {

    public:
        Entity();
        virtual ~Entity() = default;

        virtual void update(const float delta_time) = 0;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        virtual void move(const float& delta_time, const sf::Vector2f direction);

        // getters
        virtual const sf::Vector2f get_position() const;
        const sf::Vector2f get_hitbox_position() const;
        const sf::FloatRect get_global_bounds() const;
        components::MovementComponent* get_movement_component() const;
        components::HitboxComponent* get_hitbox_component() const;

        // setters         
        void set_sprite_texture(const sf::Texture &texture);
        void set_position(const sf::Vector2f position);


    protected:
        std::unique_ptr<components::AnimationComponent> animation_component;
        std::unique_ptr<components::MovementComponent> movement_component;
        std::unique_ptr<components::HitboxComponent> hitbox_component;

        sf::Sprite sprite;
     };
}
