#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>


namespace components {
    class MovementComponent final {

    public:
        MovementComponent(sf::Sprite &sprite, float max_velocity, float acceleration, float deceleration);

        void update(const float& delta_time);
        void move(const float& delta_time, const sf::Vector2f direction);

        // getters
        const float& get_max_velocity() const;
        const sf::Vector2f& get_velocity() const;
        const bool idle() const;
        const bool moving() const;
        const bool moving_left() const;
        const bool moving_right() const;
        const bool moving_up() const;
        const bool moving_down() const;
        
        // setters
        void stop_x();
        void stop_y();
        void stop();
        
    private:
        sf::Sprite& sprite;
        
        float max_velocity = 0;
        sf::Vector2f velocity;

        float acceleration = 0;
        float deceleration = 0;
    };
}
