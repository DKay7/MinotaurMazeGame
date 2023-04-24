#include "Entities/Player.hpp"
#include "Constants.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <memory>

namespace game {
    Player::Player(sf::Vector2f position, const sf::Texture& texture_sheet) {

        set_sprite_texture(texture_sheet);
        set_position(position);
        
        create_animation_component(texture_sheet);
        animation_component->add_animation(ANIMATION_ID::PLAYER_IDLE,       12, {4,   0}, {4, 0}, {48, 48});
        animation_component->add_animation(ANIMATION_ID::PLAYER_MOVE_LEFT,  1,  {16, 12}, {4, 0}, {48, 48});
        animation_component->add_animation(ANIMATION_ID::PLAYER_MOVE_RIGHT, 1,  {16,  4}, {4, 0}, {48, 48});
        animation_component->add_animation(ANIMATION_ID::PLAYER_MOVE_UP,    1,  {16,  8}, {4, 0}, {48, 48});
        animation_component->add_animation(ANIMATION_ID::PLAYER_MOVE_DOWN,  1,  {16,  0}, {4, 0}, {48, 48});

    }

    void Player::update(const float delta_time) {
        using kb = sf::Keyboard;

        if (kb::isKeyPressed(kb::W)) {
            animation_component->play(ANIMATION_ID::PLAYER_MOVE_UP, delta_time);
            move(delta_time, {0, -1});
        }
        
        else if (kb::isKeyPressed(kb::S)) {
            animation_component->play(ANIMATION_ID::PLAYER_MOVE_DOWN, delta_time);
            move(delta_time, {0, 1});
        }
        
        else if (kb::isKeyPressed(kb::D)) {
            move(delta_time, {1, 0});
            animation_component->play(ANIMATION_ID::PLAYER_MOVE_LEFT, delta_time);
        }

        else if (kb::isKeyPressed(kb::A)) {
            animation_component->play(ANIMATION_ID::PLAYER_MOVE_RIGHT, delta_time);
            move(delta_time, {-1, 0});
        }

        else 
            animation_component->play(ANIMATION_ID::PLAYER_IDLE, delta_time);
    }
}