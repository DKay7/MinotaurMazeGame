#include "GUIElements/Menu.hpp"
#include "Constants.hpp"
#include "GUIElements/Button.hpp"
#include "Utils/Utils.hpp"
#include "Context.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <string>

namespace gui {
    Menu::Menu(const sf::Font& font, const std::string titile_text, sf::Color bg_color, 
               sf::Vector2f size, sf::Vector2f position_,
               const float button_indent, bool centering):
        position(position_), font(font), button_indent(button_indent)    
    {
        title.setString(titile_text);
        title.setFont(font);
        
        background.setSize({size.x, size.y + Constants::menu_bg_indent});
        background.setFillColor(bg_color);
        
        if (centering)
            utils::center_text_on_window(title, position);
        else
            title.setPosition(position);

        if (title.getGlobalBounds().width > background.getGlobalBounds().width) {
            std::cout << "RESIZED\n";
            background.setSize({title.getGlobalBounds().width + Constants::menu_bg_indent, background.getSize().y});
        }

        if (centering)
            background.setPosition({
                title.getGlobalBounds().left + title.getGlobalBounds().width / 2 - background.getSize().x / 2.f, 
                position.y - Constants::menu_bg_indent
            });
        else
            background.setPosition({
                position.x,
                position.y
            });

        position.y += title.getGlobalBounds().height + Constants::menu_bg_indent + 2 * button_indent;
    }

    void Menu::add_button(const std::string button_text, callback_t callback, bool centering) {
        auto button = utils::create_default_button(position, font, button_text, centering);
        position.y += button.get_shape().getSize().y + button_indent;

        if (button.get_shape().getSize().x > background.getSize().x) {
            background.setSize({button.get_shape().getSize().x,  background.getSize().x});
        }

        buttons.emplace_back(std::move(button), callback);

        if (position.y > background.getSize().y)
            background.setSize({background.getSize().x, position.y - title.getPosition().y + Constants::menu_bg_indent});
        
    } 

    void Menu::process_input(sf::Event& event, sf::Vector2f mouse_pos) {
        for (auto& [button, callback] : buttons) {
            button.process_input(event, mouse_pos);
        }
    }

    const sf::Vector2f& Menu::get_size() const {
        return background.getSize();
    }

    const sf::FloatRect Menu::get_bounds() const {
        return background.getGlobalBounds();
    }

    void Menu::update(const float delta_time) {
        for (auto& [button, callback] : buttons) {
            button.update();
            if (button.is_pressed())
                callback();
        }
    }

    void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        
        target.draw(background, states);

        target.draw(title, states);
        
        for (auto& [button, callback] : buttons)
            target.draw(button, states);

    }
}