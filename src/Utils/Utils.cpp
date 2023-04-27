#include "Utils/Utils.hpp"
#include "Constants.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

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
}