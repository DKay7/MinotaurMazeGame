#include "Utils/Utils.hpp"
#include "Constants.hpp"

namespace utils {

    void center_text_on_window(sf::Text& text) {
        auto text_bounds = text.getLocalBounds();
        text.setOrigin(text_bounds.width / 2, text_bounds.height / 2);
        auto center_pos = sf::Vector2f({game::Constants::window_width / 2.f, game::Constants::window_height / 2.});
        text.setPosition(center_pos);
    }
}