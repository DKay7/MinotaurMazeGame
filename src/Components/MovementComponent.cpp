#include "Components/MovementComponent.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <iostream>

namespace game {
    MovementComponent::MovementComponent(sf::Sprite &sprite, float max_velocity, float acceleration, float deceleration): 
        sprite(sprite), max_velocity(max_velocity), 
        acceleration(acceleration), deceleration(deceleration)
    { }

    void MovementComponent::move(const float& delta_time, const sf::Vector2f direction) {
        // accelerating sprite until it reaches max speed

        velocity.x += acceleration * direction.x;
        velocity.y += acceleration * direction.y;
    }

    void MovementComponent::update(const float& delta_time) {

        #define speed_sign(speed) (std::signbit(speed) ? -1 : 1)

        int old_sign = 0;
        #define update_speed(speed)                         \
            /*checks for max speed and set the max*/        \
            if (std::abs(speed) > max_velocity)             \
                speed = speed_sign(speed) * max_velocity;   \
                                                            \
            /*if after deceleration speed sign is changed*/ \
            /*then we reaches the mininmun so set speed */  \
            /*to zero*/                                     \
            old_sign = speed_sign(speed);                   \
            speed -= speed_sign(speed) * deceleration;      \
                                                            \
            if (old_sign != speed_sign(speed))              \
                speed = 0;

        update_speed(velocity.x)
        update_speed(velocity.y)
        
        sprite.move(velocity * delta_time);

        #undef speed_sign
        #undef update_speed

    }
    
    const sf::Vector2f& MovementComponent::get_velocity() const {
        return velocity;
    }
}
