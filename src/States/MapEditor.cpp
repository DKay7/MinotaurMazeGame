#include "States/MapEditor.hpp"
#include "Constants.hpp"
#include "Context.hpp"
#include "GUIElements/Menu.hpp"
#include "Map/TileMap.hpp"
#include "States/GamePause.hpp"
#include "States/MainMenu.hpp"
#include "Utils/Utils.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Window.hpp>
#include <memory>

namespace game {
    MapEditor::MapEditor(Context* context_): context(context_), tile_map({Constants::window_width / 4.f, 0}) { 
        
        menu = std::make_unique<gui::Menu>(context->asset_manager->get_font(FONT_ID::MAIN_FONT), "Map Editor", Constants::button_size.y, sf::Vector2f(0, 0), false);
        menu->add_button("exit", [&](){
            auto &state_mgr = context->state_manager;
            state_mgr->pop_state();
            state_mgr->add_state(std::make_unique<MainMenu>(context));
        }, false);
        
        mouse_selector_shape.setSize({Constants::grid_size, Constants::grid_size});
        mouse_selector_shape.setFillColor(sf::Color::Transparent);
        mouse_selector_shape.setOutlineColor(sf::Color::Cyan);
        mouse_selector_shape.setOutlineThickness(3.f); //TODO remove
    }

    void MapEditor::process_input(sf::Event& event) {
        using kb = sf::Keyboard;
        auto mouse_pos = utils::get_mouse_position(*context->window);
        
        mouse_selector_shape.setPosition(mouse_pos);

        menu->process_input(event, mouse_pos);

        if (event.type == sf::Event::KeyPressed and event.key.code == kb::Escape)
            context->state_manager->add_state(std::make_unique<GamePause>(context));
    }

    void MapEditor::update(const float delta_time) {
        menu->update(delta_time);
        tile_map.update(delta_time);
    }

    void MapEditor::draw() {
        auto &window = context->window;
        window->clear();
        sf::RectangleShape rect;
        rect.setSize({Constants::window_width / 4.f, Constants::window_height});
        rect.setFillColor(sf::Color(9, 53, 54));
        window->draw(rect);
        window->draw(*menu);
        window->draw(tile_map);   

        window->draw(mouse_selector_shape);

        window->display();
    }

    void MapEditor::pause() {
    
    } 

    void MapEditor::start() {

    } 

    #ifndef NDEBUG
        std::string MapEditor::get_state_name() const {
            return "MapEditor";
        }
    #endif
}