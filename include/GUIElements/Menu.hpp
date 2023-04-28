#pragma once

#include "GUIElements/Button.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <functional>
#include <memory>
#include <vector>

namespace gui {
    class Menu final: sf::Drawable {
    public:
        using callback_t = std::function<void()>;

        Menu(sf::Vector2f position, const sf::Font& font, const std::string titile_text, const float button_indent);

        void add_button(const std::string button_text, callback_t callback); // acepts button and set correct indent to it

        void update(const float delta_time);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        using btn_container = std::pair<std::unique_ptr<Button>, callback_t>;

        const sf::Font& font;
        sf::Text titile;
        const float button_indent;
        sf::Vector2f position;
        std::vector<btn_container> buttons;

    };
}