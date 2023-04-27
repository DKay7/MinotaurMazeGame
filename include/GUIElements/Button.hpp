#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>

namespace game
{
   class Button final: public sf::Drawable, public sf::Transformable {
    public:
        Button(sf::Vector2f position, sf::Vector2f size, const sf::Font& font, 
                   std::string button_text, sf::Color default_text_color, 
                   sf::Color hover_text_color, sf::Color pressed_text_color, 
                   sf::Color default_bg_color=sf::Color::Transparent, 
                   sf::Color hover_bg_color=sf::Color::Transparent, 
                   sf::Color pressed_bg_color=sf::Color::Transparent);
        
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void update(sf::Vector2f mouse_position);
        bool is_pressed() const;

        enum class BUTTON_STATE {
            DEFAULT = 0,
            HOVER   = 1,
            PRESSED = 2,
        };


    private:
        BUTTON_STATE state = BUTTON_STATE::DEFAULT;
        sf::Color default_bg_color;
        sf::Color hover_bg_color;
        sf::Color pressed_bg_color;
        
        sf::Color default_text_color;
        sf::Color hover_text_color;
        sf::Color pressed_text_color;

        sf::Vector2f position;
        sf::RectangleShape shape;
        sf::Text text;
        
        bool switch_text_color;
    }; 
} // namespace engine

