#include "States/MapEditor.hpp"
#include "Context.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <memory>

namespace game {
    MapEditor::MapEditor(Context* context): context(context) { }

    void MapEditor::process_input(sf::Event& event) {

    }

    void MapEditor::update(const float delta_time) {

    }

    void MapEditor::draw() {
        
    }

    #ifndef NDEBUG
        std::string MapEditor::get_state_name() const {
            return "MapEditor";
        }
    #endif
}