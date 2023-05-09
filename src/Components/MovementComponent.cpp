#include "Components/MovementComponent.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <math.h>

namespace components {
    MovementComponent::MovementComponent(sf::Sprite &sprite, float max_velocity, float acceleration, float deceleration): 
        sprite(sprite), max_velocity(max_velocity), velocity({0, 0}), 
        acceleration(acceleration), deceleration(deceleration)
    { }

    void MovementComponent::move(const float& delta_time, const sf::Vector2f direction) {
        // accelerating sprite until it reaches max speed
        
        velocity.x += acceleration * direction.x * delta_time;
        velocity.y += acceleration * direction.y * delta_time;

        
    }

    void MovementComponent::update(const float& delta_time) {

        #define speed_sign(speed) (std::signbit(speed) ? -1 : 1)

        int old_sign = 0;
        #define update_speed(speed)                                     \
            if (speed != 0)       {                                     \
                /*checking for max speed and update if needed*/         \
                if (std::abs(speed) > max_velocity)                     \
                    speed = speed_sign(speed) * max_velocity;           \
                /*if after deceleration speed sign is changed*/         \
                /*then we reaches the mininmun so set speed */          \
                /*to zero*/                                             \
                old_sign = speed_sign(speed);                           \
                speed -= speed_sign(speed) * deceleration * delta_time; \
                                                                        \
                if (old_sign != speed_sign(speed)) {                    \
                    speed = 0;                                          \
                }                                                       \
            }
 
        update_speed(velocity.x)
        update_speed(velocity.y)

        /*check for full speed for diagonal move*/
        auto full_speed = std::sqrt( velocity.x *  velocity.x + velocity.y * velocity.y);
        if (full_speed >= max_velocity) {
                velocity.x = velocity.x / std::sqrt(2); 
                velocity.y = velocity.y / std::sqrt(2);
        }

        sprite.move(velocity * delta_time);

        #undef speed_sign
        #undef decrease_speed
    }
    
    const float& MovementComponent::get_max_velocity() const {
        return max_velocity;
    }

    const sf::Vector2f& MovementComponent::get_velocity() const {
        return velocity;
    }

    void MovementComponent::stop_x() {
        velocity.x = 0;
    }

    void MovementComponent::stop_y() {
        velocity.y = 0;
    }

    void MovementComponent::stop() {
        stop_x();
        stop_y();
    }

    const bool MovementComponent::idle() const {

        // we manually sets velosity to zero, so
        // it's okay to comapre it even it's a float
        return velocity.x == 0 and velocity.y == 0;
    }

    const bool MovementComponent::moving() const {
        return !idle();
    }

    const bool MovementComponent::moving_left() const {
        return velocity.x < 0;
    }

    const bool MovementComponent::moving_right() const {
        return velocity.x > 0;
    }

    const bool MovementComponent::moving_up() const {
        return velocity.y < 0;
    }

    const bool MovementComponent::moving_down() const {
        return velocity.y > 0;
    }


}
