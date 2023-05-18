#include "Utils/Utils.hpp"
#include "Settings/Buttons.hpp"
#include "Settings/Enums.hpp"
#include "Entities/Entity.hpp"
#include "GUIElements/Button.hpp"
#include "Map/TileMap.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include <sstream>

namespace utils {

    void center_text_on_window(sf::Text& text, sf::Vector2f position) {
        auto text_bounds = text.getLocalBounds();
        text.setOrigin(text_bounds.width / 2, text_bounds.height / 2);
        text.setPosition(position);
    }

    const sf::Vector2f get_mouse_position(const sf::RenderWindow& window) {
        return window.mapPixelToCoords(sf::Mouse::getPosition(window));
    }

    gui::Button create_default_button(sf::Vector2f position, const sf::Font& font, std::string text, bool centering) {
        return gui::Button(position, settings::button_size, font, text, 
                           settings::button_text_idle, settings::button_text_hover, settings::button_text_active, centering);
    }

    sf::Vector2i get_gridded_mouse(const sf::Vector2f mouse_pos, const float grid_size) {
        return {
            static_cast<int>(mouse_pos.x) / static_cast<int>(grid_size),
            static_cast<int>(mouse_pos.y) / static_cast<int>(grid_size),
        };
    }

    std::string get_string_tile_types(const int tile_type) { 
        std::stringstream result;

        if (tile_type == TILE_TYPES_ID::DEFAULT)
            result << "\tdefault\n";

        if (tile_type & TILE_TYPES_ID::COLLIDABLE)
            result << "\tcollidable,\n";

        if (tile_type & TILE_TYPES_ID::SPAWN_POINT)
            result << "\tspawn point,\n";
        
        if (tile_type & TILE_TYPES_ID::WIN_POINT)
            result << "\twin point,\n";

        return result.str();
    }
}