#include "Utils/Utils.hpp"
#include "Constants.hpp"
#include "GUIElements/Button.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <memory>

namespace utils {

    void center_text_on_window(sf::Text& text) {
        auto text_bounds = text.getLocalBounds();
        text.setOrigin(text_bounds.width / 2, text_bounds.height / 2);
        auto center_pos = sf::Vector2f({game::Constants::window_width / 2.f, game::Constants::window_height / 2.});
        text.setPosition(center_pos);
    }

    const sf::Vector2f get_mouse_position(const sf::RenderWindow& window) {
        return window.mapPixelToCoords(sf::Mouse::getPosition(window));
    }

    std::unique_ptr<game::Button> create_default_button(sf::Vector2f position, const sf::Font& font, std::string text) {
        using Constants = game::Constants;
        return std::make_unique<game::Button>(position, Constants::button_size, font, text, 
                                              Constants::button_text_idle, Constants::button_text_hover, Constants::button_text_active);
    }
}