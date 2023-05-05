#include "GUIElements/Button.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <string>
#include "Constants.hpp"
#include "Utils/Utils.hpp"

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
        
        text.setFont(font);
        text.setString(button_text);
        text.setCharacterSize(Constants::default_bt_text_size);
        text.setFillColor(default_text_color);
        
        if (centering) {
            utils::center_text_on_window(text, position);
        }
        
        if (text.getLocalBounds().width > shape.getSize().x) {
            shape.setSize({text.getGlobalBounds().width + Constants::button_bg_indent, shape.getSize().y});
        }

        shape.setPosition({
            position.x - shape.getSize().x / 2.f,
            position.y - shape.getSize().y / 2.f + text.getGlobalBounds().height / 2.f,
        });
    }

    void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(shape);
        target.draw(text);
    }

    void Button::process_input(sf::Event& event, sf::Vector2f mouse_position) {
        /*
            The only method which are allowed to change button state -- Button::update(),
            therefore, in here we just set flags for update method to proceed and change button state
            Actually, if we change button state here, we may catch an error that process_input method
            aren't called on each iteration of game cycle (so button state may not be changed on each iteration)
            while update method are. That's why only update
            method are allowed to change button state  
        */

        if (shape.getGlobalBounds().contains(mouse_position)) {
            was_hovered = true;

            if (event.type == sf::Event::MouseButtonReleased and event.mouseButton.button == sf::Mouse::Left)
                was_pressed = true;
        }

        else
            was_hovered = false;
    }

    void Button::update() {
        state = BUTTON_STATE::DEFAULT;
        
        if (was_hovered) 
            state = BUTTON_STATE::HOVER;

        if (was_pressed) {
            state = BUTTON_STATE::PRESSED;
            was_pressed = false;
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

    const sf::RectangleShape& Button::get_shape() const {
        return shape;
    }
}