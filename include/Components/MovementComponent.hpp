#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>


namespace game {
    class MovementComponent final {

    public:
        MovementComponent(sf::Sprite &sprite, float max_velocity, float acceleration, float deceleration);

        void update(const float& delta_time);
        void move(const float& delta_time, const sf::Vector2f direction);

        const sf::Vector2f& get_velocity() const;
        const bool idle() const;
        const bool moving() const;
        const bool moving_left() const;
        const bool moving_right() const;
        const bool moving_up() const;
        const bool moving_down() const;
        
    private:
        sf::Sprite& sprite;
        
        float max_velocity = 0;
        sf::Vector2f velocity = {0, 0};

        float acceleration = 0;
        float deceleration = 0;
    };
}
