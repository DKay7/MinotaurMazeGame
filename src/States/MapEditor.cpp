#include "States/MapEditor.hpp"
#include "Constants.hpp"
#include "Context.hpp"
#include "States/GamePause.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Window.hpp>
#include <memory>

namespace game {
    MapEditor::MapEditor(Context* context): context(context) { }

    void MapEditor::process_input(sf::Event& event) {
        using kb = sf::Keyboard;

        if (event.type == sf::Event::KeyPressed and event.key.code == kb::Escape)
            context->state_manager->add_state(std::make_unique<GamePause>(context));
    }

    void MapEditor::update(const float delta_time) {

    }

    void MapEditor::draw() {
        auto &window = context->window;
        window->clear();
        sf::RectangleShape rect;
        rect.setSize({500, Constants::window_height});
        rect.setFillColor(sf::Color(9, 53, 54));
        window->draw(rect);
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