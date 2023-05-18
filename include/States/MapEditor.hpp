#pragma once

#include "Settings/Enums.hpp"
#include "Context.hpp"
#include "GUIElements/Menu.hpp"
#include "GUIElements/TextureSelector.hpp"
#include "Interfaces/LoadableInterface.hpp"
#include "Map/TileMap.hpp"
#include "Interfaces/SaveableInterface.hpp"
#include "States/CameraState.hpp"
#include "States/SaveableLoadableState.hpp"
#include "States/State.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>
#include <sstream>
#include <string>

namespace game {
    class MapEditor final : public states_engine::SaveableLoadableState,
                            public states_engine::CameraState {

    public:
        MapEditor(game_engine::Context *context, std::unique_ptr<map::TileMap> tile_map=nullptr);

        void process_input(sf::Event &event) override;
        void update(const float delta_time) override;
        void draw() override;
        void pause() override;
        void start() override;

        // staticly inherited from Saveable and Loadable CRTP classes
        std::string serialize() const override;
        void deserialize(std::stringstream file_content) override; 

        #ifndef NDEBUG
        std::string get_state_name() const override;
        #endif

    private:
        void init_texture_selector_gui();

        void update_mouse_rectangle();
        void update_mouse_text();

        void process_editor_input(sf::Event &event);

        sf::Text mouse_coords_text;
        sf::RectangleShape mouse_rectangle;
        sf::IntRect tile_texture_rect;
        sf::Vector2i mouse_pos_grid;
        bool mouse_picker_active = true;
        int current_tile_type = TILE_TYPES_ID::DEFAULT;

        std::unique_ptr<map::TileMap> tile_map;
        std::unique_ptr<gui::TextureSelector> texture_selector;

        game_engine::Context *context;
    };
} // namespace game