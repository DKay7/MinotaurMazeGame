#include "GUIElements/Button.hpp"
#include <SFML/Graphics/RenderStates.hpp>

namespace gui {

    Button::Button(sf::Vector2f position, sf::Vector2f size, 
                   const sf::Font& font, std::string button_text, 
                   sf::Color default_text_color, sf::Color hover_text_color, 
                   sf::Color pressed_text_color, sf::Color default_bg_color, 
                   sf::Color hover_bg_color,  sf::Color pressed_bg_color)
               : default_bg_color(default_bg_color)
               , hover_bg_color(hover_bg_color)
               , pressed_bg_color(pressed_bg_color)
               , default_text_color(default_text_color)
               , hover_text_color(hover_text_color)
               , pressed_text_color(pressed_text_color)
               
    {   
        shape.setSize(size);

        auto shape_bounds = shape.getLocalBounds();
        shape.setOrigin(shape_bounds.width / 2, shape_bounds.height / 2);
        
        shape.setPosition(position);
        shape.setFillColor(default_bg_color);

        text.setFont(font);
        text.setString(button_text);
        text.setCharacterSize(15);
        text.setFillColor(default_text_color);

        auto text_bounds = text.getLocalBounds();
        text.setOrigin(text_bounds.width / 2, text_bounds.height / 2);
        text.setPosition(
            shape.getPosition().x, 
            shape.getPosition().y 
        );
    }

    void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(shape);
        target.draw(text);
    }

    void Button::update(sf::Vector2f mouse_position) {
        
        state = BUTTON_STATE::DEFAULT;

        if (shape.getGlobalBounds().contains(mouse_position)) {
            state = BUTTON_STATE::HOVER;

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                state = BUTTON_STATE::PRESSED;
            }
        }
        
        switch (state) {
            case BUTTON_STATE::DEFAULT:
                text.setFillColor(default_text_color);
                shape.setFillColor(default_bg_color);
                break;

            case BUTTON_STATE::HOVER:
                text.setFillColor(hover_text_color);
                shape.setFillColor(hover_bg_color);
                break;

            case BUTTON_STATE::PRESSED:
                text.setFillColor(pressed_text_color);
                shape.setFillColor(pressed_bg_color);
                break;
        }

    } 

    bool Button::is_pressed() const {
        return state == BUTTON_STATE::PRESSED;
    }


}