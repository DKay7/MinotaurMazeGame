#pragma once

#include "Constants.hpp"
#include "Context.hpp"
#include "GUIElements/Button.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <functional>
#include <memory>
#include <vector>

namespace gui {
    class Menu final: public sf::Drawable {
    public:
        using callback_t = std::function<void()>;

        Menu(const sf::Font& font, const std::string titile_text="",
             sf::Color bg_color=sf::Color::Transparent,
             sf::Vector2f size = sf::Vector2f({Constants::window_width / 4.f , Constants::window_height / 4.}),
             sf::Vector2f position = sf::Vector2f({Constants::window_width / 2.f , Constants::window_height / 2.}),
             const float button_indent=Constants::menu_button_indent, 
             bool centering = true);


        void add_button(const std::string button_text, callback_t callback, bool centering=true);
        
        void process_input(sf::Event& event, sf::Vector2f mouse_pos);
        void update(const float delta_time);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
        const sf::Vector2f& get_size() const;
        const sf::FloatRect get_bounds() const;

    private:
        using btn_container = std::pair<std::unique_ptr<Button>, callback_t>;

    
        const sf::Font& font;
        sf::Text title;

        sf::RectangleShape background;

        const float button_indent;
        sf::Vector2f position;
        std::vector<std::pair<Button, callback_t>> buttons;

    };
}