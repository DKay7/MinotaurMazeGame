#include "GUIElements/Menu.hpp"
#include "Constants.hpp"
#include "GUIElements/Button.hpp"
#include "Utils/Utils.hpp"
#include "Context.hpp"
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

namespace gui {
    Menu::Menu(const sf::Font& font, const std::string titile_text, const float button_indent, sf::Vector2f position_):
        position(position_), font(font), button_indent(button_indent)    
    {
        title.setString(titile_text);
        title.setFont(font);
        utils::center_text_on_window(title, position);

        position.y += 1.5 * button_indent;
    }


    void Menu::add_button(const std::string button_text, callback_t callback) {
        auto button = utils::create_default_button(position, font, button_text);
        position.y += button_indent;

        buttons.emplace_back(std::move(button), callback);
    } 

    void Menu::process_input(sf::Event& event, sf::Vector2f mouse_pos) {
        for (auto& [button, callback] : buttons) {
            button.process_input(event, mouse_pos);
        }
    }

    void Menu::update(const float delta_time) {
        for (auto& [button, callback] : buttons) {
            button.update();
            if (button.is_pressed()) {
                callback();
            }
        }
    }

    void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        
        target.draw(title, states);
        
        for (auto& [button, callback] : buttons)
            target.draw(button, states);

    }
}