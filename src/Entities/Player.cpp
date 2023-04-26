#include "Entities/Player.hpp"
#include "Constants.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <ctime>
#include <memory>

namespace game {
    Player::Player(sf::Vector2f position, const sf::Texture& texture_sheet) {

        set_sprite_texture(texture_sheet);
        set_position(position);
        
        create_movement_component(Constants::player_covement_max_speed);

        create_animation_component(texture_sheet);
        
        animation_component->add_animation(ANIMATION_ID::PLAYER_IDLE,       Constants::idle_tpf,      {4,   0}, {4, 0}, Constants::default_frame_size);
        animation_component->add_animation(ANIMATION_ID::PLAYER_MOVE_RIGHT, Constants::movement_tpf,  {16, 12}, {4, 0}, Constants::default_frame_size);
        animation_component->add_animation(ANIMATION_ID::PLAYER_MOVE_LEFT,  Constants::movement_tpf,  {16,  4}, {4, 0}, Constants::default_frame_size);
        animation_component->add_animation(ANIMATION_ID::PLAYER_MOVE_UP,    Constants::movement_tpf,  {16,  8}, {4, 0}, Constants::default_frame_size);
        animation_component->add_animation(ANIMATION_ID::PLAYER_MOVE_DOWN,  Constants::movement_tpf,  {16,  0}, {4, 0}, Constants::default_frame_size);

        animation_component->add_animation(ANIMATION_ID::PLAYER_MOVE_LEFT_UP,    Constants::movement_tpf,  {16,   6}, {4, 0}, Constants::default_frame_size);
        animation_component->add_animation(ANIMATION_ID::PLAYER_MOVE_LEFT_DOWN,  Constants::movement_tpf,  {16,   2}, {4, 0}, Constants::default_frame_size);
        animation_component->add_animation(ANIMATION_ID::PLAYER_MOVE_RIGHT_UP,   Constants::movement_tpf,  {16,  10}, {4, 0}, Constants::default_frame_size);
        animation_component->add_animation(ANIMATION_ID::PLAYER_MOVE_RIGHT_DOWN, Constants::movement_tpf,  {16,  14}, {4, 0}, Constants::default_frame_size);
    }

    void Player::update(const float delta_time) {
        
        movement_component->update(delta_time);

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