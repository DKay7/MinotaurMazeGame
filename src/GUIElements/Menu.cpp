#include "GUIElements/Menu.hpp"
#include "Constants.hpp"
#include "GUIElements/Button.hpp"
#include "Utils/Utils.hpp"
#include <string>

namespace gui {
    Menu::Menu(sf::Vector2f position, const sf::Font& font, const std::string titile_text, const float button_indent):
        position(position), font(font), button_indent(button_indent)    
    {
        titile.setString(titile_text);
        titile.setFont(font);
        titile.setPosition(position);

        position.y += 1.5 * button_indent;
    }


    void Menu::add_button(const std::string button_text, callback_t callback) {
        auto button = utils::create_default_button(position, font, button_text);
        position.y += button_indent;

        buttons.push_back({std::move(button), callback});
    } 

    void Menu::update(const float delta_time) {
        for (auto& [button, callback] : buttons) {
            if (button->is_pressed())
                callback();
        }
    }

    void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.clear();

        target.draw(titile, states);
        for (auto& [button, callback] : buttons)
            target.draw(*button, states);

    }
}