#include "Components/AnimationComponent.hpp"

namespace game {
    AnimationComponent::AnimationComponent(sf::Sprite &sprite, const sf::Texture &texture_sheet):
        sprite(sprite), texture_sheet(texture_sheet)
    {
        sprite.setTexture(texture_sheet);
    }

    void AnimationComponent::add_animation(const ANIMATION_ID key, float time_per_frame, sf::Vector2i start_frame, 
                                           sf::Vector2i num_frames, sf::Vector2i frame_size) 
    {
        animations[key] = std::make_unique<Animation>(sprite, texture_sheet, time_per_frame, start_frame, num_frames, frame_size);
    }

    void AnimationComponent::play(const ANIMATION_ID key, const float& delta_time) {
        animations[key]->play(delta_time);
    }

}
