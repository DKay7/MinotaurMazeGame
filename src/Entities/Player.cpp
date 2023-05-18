#include "Entities/Player.hpp"
#include "Components/HitboxComponent.hpp"
#include "Settings/PlayerParameters.hpp"
#include "Settings/Enums.hpp"
#include "Settings/AnimationParameters.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <ctime>
#include <memory>

namespace entities {
    Player::Player(sf::Vector2f position, const sf::Texture& texture_sheet) {

        set_sprite_texture(texture_sheet);
        
        animation_component = std::make_unique<components::AnimationComponent>(sprite, texture_sheet);
        
        movement_component = std::make_unique<components::MovementComponent>(
            sprite, settings::player_movement_max_speed, 
            settings::default_acceleration, settings::default_deceleration
        );

        hitbox_component = std::make_unique<components::HitboxComponent>(
            sprite, settings::player_hitbox_offset, 
            settings::player_hitbox_size, settings::player_hitbox_idle_size
        );   

       
        animation_component->add_animation(ANIMATION_ID::PLAYER_IDLE,       settings::idle_tpf,      {0, 8}, 8, settings::default_frame_size);
        animation_component->add_animation(ANIMATION_ID::PLAYER_MOVE_RIGHT, settings::movement_tpf,  {0, 7}, 8, settings::default_frame_size);
        animation_component->add_animation(ANIMATION_ID::PLAYER_MOVE_LEFT,  settings::movement_tpf,  {0, 2}, 8, settings::default_frame_size);
        animation_component->add_animation(ANIMATION_ID::PLAYER_MOVE_UP,    settings::movement_tpf,  {0, 4}, 8, settings::default_frame_size);
        animation_component->add_animation(ANIMATION_ID::PLAYER_MOVE_DOWN,  settings::movement_tpf,  {0, 0}, 8, settings::default_frame_size);

        animation_component->add_animation(ANIMATION_ID::PLAYER_MOVE_LEFT_UP,    settings::movement_tpf,  {0, 3}, 8, settings::default_frame_size);
        animation_component->add_animation(ANIMATION_ID::PLAYER_MOVE_LEFT_DOWN,  settings::movement_tpf,  {0, 1}, 8, settings::default_frame_size);
        animation_component->add_animation(ANIMATION_ID::PLAYER_MOVE_RIGHT_UP,   settings::movement_tpf,  {0, 5}, 8, settings::default_frame_size);
        animation_component->add_animation(ANIMATION_ID::PLAYER_MOVE_RIGHT_DOWN, settings::movement_tpf,  {0, 6}, 8, settings::default_frame_size);

        // it's important to set position AFTER adding animations
        // 'cuz animations sets texture rect of the sprite
        // otherwise sprite size is incorrect
        set_position(position);
    }

    void Player::update(const float delta_time) {
        
        movement_component->update(delta_time);
        hitbox_component->update_hitbox_position();
        hitbox_component->update_idle(movement_component->idle());

        auto &max_speed = movement_component->get_max_velocity();
        
        #define play_move(condition, animation_id)                                  \
            else if((condition)) {                                                  \
                animation_component->play(ANIMATION_ID::animation_id, delta_time);  \
            }

        #define get_dir(direction) \
            movement_component->moving_##direction()
        
        if (movement_component->idle())
            animation_component->play(ANIMATION_ID::PLAYER_IDLE, delta_time);
                
        play_move(get_dir(left)  and get_dir(up),   PLAYER_MOVE_LEFT_UP)
        play_move(get_dir(left)  and get_dir(down), PLAYER_MOVE_LEFT_DOWN)
        play_move(get_dir(right) and get_dir(up),   PLAYER_MOVE_RIGHT_UP)
        play_move(get_dir(right) and get_dir(down), PLAYER_MOVE_RIGHT_DOWN)

        play_move(get_dir(left),  PLAYER_MOVE_LEFT)
        play_move(get_dir(right), PLAYER_MOVE_RIGHT)
        play_move(get_dir(up),    PLAYER_MOVE_UP)
        play_move(get_dir(down),  PLAYER_MOVE_DOWN)            
    }
}