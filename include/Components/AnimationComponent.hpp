#pragma once

#include "../Constants.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <map>
#include <memory>
#include <iostream>

namespace game {

    class AnimationComponent final {

    public:
        AnimationComponent(sf::Sprite &sprite, const sf::Texture &texture_sheet);
        void play(const ANIMATION_ID key, const float& delta_time);
        void add_animation(const ANIMATION_ID key, float time_per_frame, sf::Vector2i start_frame, 
                           sf::Vector2i num_frames, sf::Vector2i frame_size);
    private:

        class Animation final {
            public:
                Animation(sf::Sprite &sprite_, const sf::Texture& texture_sheet, float time_per_frame, 
                          sf::Vector2i start_frame, sf::Vector2i num_frames, sf::Vector2i frame_size): 
                        sprite(sprite_), texture_sheet(texture_sheet), time_per_frame(time_per_frame), frame_size(frame_size)
                {   
                    start_rect = sf::IntRect(start_frame.x * frame_size.x, start_frame.y * frame_size.y, 
                                             frame_size.x, frame_size.y);
                    current_rect = start_rect;

                    end_rect = sf::IntRect((start_frame.x + num_frames.x) * frame_size.x, 
                                           (start_frame.y + num_frames.y) * frame_size.y,
                                           frame_size.x, frame_size.y);

                    sprite.setTexture(texture_sheet, true);
                    sprite.setTextureRect(start_rect);
                }

                void play(const float& delta_time) {
                    timer += 10 * delta_time;   // mult by 10 just bc game timer is too slow
                     
                    sprite.setTextureRect(current_rect);

                    if (timer < time_per_frame)
                        return;
                    
                    timer = 0;
                    if (current_rect != end_rect)
                        current_rect.left += frame_size.x;
                    // reset animation
                    else
                        current_rect = start_rect;
                

                }
                
                void reset() {
                    timer = 0;
                    current_rect = start_rect;
                }
                
            private:
                sf::Sprite &sprite;
                const sf::Texture &texture_sheet;

                sf::Vector2i frame_size;
                float time_per_frame = 0;

                float timer = 0;
                
                sf::IntRect start_rect;
                sf::IntRect current_rect;
                sf::IntRect end_rect;
              
        };

        Animation* last_animation = nullptr; // not owning pointer to last played animation
        sf::Sprite &sprite;
        const sf::Texture &texture_sheet;
        std::map<const ANIMATION_ID, std::unique_ptr<Animation>> animations;
    };
}
