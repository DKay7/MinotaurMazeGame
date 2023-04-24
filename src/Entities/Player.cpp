#include "Entities/Player.hpp"
#include "Constants.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <ctime>
#include <memory>

namespace game {
    Player::Player(sf::Vector2f position, const sf::Texture& texture_sheet) {

        set_sprite_texture(texture_sheet);
        set_position(position);
        
        create_movement_component(250.);

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

        if (movement_component->idle())
            animation_component->play(ANIMATION_ID::PLAYER_IDLE, delta_time);
        else if (movement_component->moving_left() and movement_component->moving_up())
            animation_component->play(ANIMATION_ID::PLAYER_MOVE_LEFT_UP, delta_time);
        else if (movement_component->moving_left() and movement_component->moving_down())
            animation_component->play(ANIMATION_ID::PLAYER_MOVE_LEFT_DOWN, delta_time);
        else if (movement_component->moving_right() and movement_component->moving_up())
            animation_component->play(ANIMATION_ID::PLAYER_MOVE_RIGHT_UP, delta_time);
        else if (movement_component->moving_right() and movement_component->moving_down())
            animation_component->play(ANIMATION_ID::PLAYER_MOVE_RIGHT_DOWN, delta_time);

        else if (movement_component->moving_left())
            animation_component->play(ANIMATION_ID::PLAYER_MOVE_LEFT, delta_time);
        else if (movement_component->moving_right())
            animation_component->play(ANIMATION_ID::PLAYER_MOVE_RIGHT, delta_time);
        else if (movement_component->moving_down())
            animation_component->play(ANIMATION_ID::PLAYER_MOVE_DOWN, delta_time);
        else if (movement_component->moving_up())
            animation_component->play(ANIMATION_ID::PLAYER_MOVE_UP, delta_time);

        using kb = sf::Keyboard;
        // TODO process inputs is GamePlay responsibility!
        if (kb::isKeyPressed(kb::W)) {
            move(delta_time, {0, -1});
        }
        
        if (kb::isKeyPressed(kb::S)) {
            move(delta_time, {0, 1});
        }
        
        if (kb::isKeyPressed(kb::D)) {
            move(delta_time, {1, 0});
        }

        if (kb::isKeyPressed(kb::A)) {
            move(delta_time, {-1, 0});
        }

    }
}