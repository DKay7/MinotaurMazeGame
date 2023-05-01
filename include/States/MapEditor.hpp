#pragma once

#include "Context.hpp"
#include "GUIElements/Menu.hpp"
#include "Map/TileMap.hpp"
#include "States/State.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>


namespace game {
    class MapEditor final: public engine::State {
    public:
        MapEditor(Context* context);

        void process_input(sf::Event& event) override;
        void update(const float delta_time) override;
        void draw() override;
        void pause() override;
        void start() override;

        #ifndef NDEBUG
            std::string get_state_name() const override;
        #endif
        
    private:
        void update_mouse_selector();
        void process_editor_input(sf::Event& event);

        sf::RectangleShape mouse_selector_shape;
        sf::Vector2u mouse_pos_grid;

        TileMap tile_map;
        std::unique_ptr<gui::Menu> menu;
                
        Context* context;
    };
}