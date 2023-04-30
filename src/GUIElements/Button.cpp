#include "GUIElements/Button.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include "Constants.hpp"

namespace gui {

    Button::Button(sf::Vector2f position, sf::Vector2f size, 
                   const sf::Font& font, std::string button_text, 
                   sf::Color default_text_color, sf::Color hover_text_color, 
                   sf::Color pressed_text_color, bool centering,  
                   sf::Color default_bg_color_, sf::Color hover_bg_color_, 
                   sf::Color pressed_bg_color_)
               : default_bg_color(default_bg_color_)
               , hover_bg_color(hover_bg_color_)
               , pressed_bg_color(pressed_bg_color_)
               , default_text_color(default_text_color)
               , hover_text_color(hover_text_color)
               , pressed_text_color(pressed_text_color)
               
    {   
        shape.setSize(size);

        if (centering) {
            auto shape_bounds = shape.getLocalBounds();
            shape.setOrigin(shape_bounds.width / 2, shape_bounds.height / 2);
        }

        shape.setPosition(position);
        shape.setFillColor(default_bg_color);

        text.setFont(font);
        text.setString(button_text);
        text.setCharacterSize(game::Constants::default_bt_text_size);
        text.setFillColor(default_text_color);

        if (centering) {
            auto text_bounds = text.getLocalBounds();
            text.setOrigin(text_bounds.width / 2, text_bounds.height / 2);
        }
        
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

    void Button::process_input(sf::Event& event, sf::Vector2f mouse_position) {
        state = BUTTON_STATE::DEFAULT;

        if (shape.getGlobalBounds().contains(mouse_position)) {
            state = BUTTON_STATE::HOVER;

        if (event.type == sf::Event::MouseButtonReleased and event.mouseButton.button == sf::Mouse::Left)
            state = BUTTON_STATE::PRESSED;
        }
    }

    void Button::update() {
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