#include "Utils/Utils.hpp"
#include "Constants.hpp"
#include "GUIElements/Button.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <memory>

namespace utils {

    void center_text_on_window(sf::Text& text, sf::Vector2f position) {
        auto text_bounds = text.getLocalBounds();
        text.setOrigin(text_bounds.width / 2, text_bounds.height / 2);
        text.setPosition(position);
    }

    void center_shape_on_window(sf::Shape& shape, sf::Vector2f position) { // TODO maybe unused
        auto shape_bounds = shape.getLocalBounds();
        shape.setOrigin({shape_bounds.width / 2, shape_bounds.height / 2});
        shape.setPosition(position);
    }

    const sf::Vector2f get_mouse_position(const sf::RenderWindow& window) {
        return window.mapPixelToCoords(sf::Mouse::getPosition(window));
    }

    gui::Button create_default_button(sf::Vector2f position, const sf::Font& font, std::string text, bool centering) {
        return gui::Button(position, Constants::button_size, font, text, 
                           Constants::button_text_idle, Constants::button_text_hover, Constants::button_text_active, centering);
    }

    sf::Vector2u get_gridded_mouse(const sf::Vector2f mouse_pos, const float grid_size) {
        return {
            static_cast<unsigned>(mouse_pos.x) / static_cast<unsigned>(grid_size),
            static_cast<unsigned>(mouse_pos.y) / static_cast<unsigned>(grid_size),
        };
    }
}