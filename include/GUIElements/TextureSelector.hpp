#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

namespace gui {
    class TextureSelector final: public sf::Drawable {
    
    public:
        TextureSelector(const sf::Vector2f position, const sf::Vector2f size, 
                        const sf::Texture &texture, const float grid_size);

        void update(sf::Vector2f mouse_pos);
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    private:
        const float grid_size;
        
        sf::Vector2u gridded_mouse_pos;
        sf::RectangleShape selector;
        sf::IntRect texture_rect;
        bool is_active = false;

        sf::Sprite sheet;
        sf::RectangleShape bounds;
        
    };
}