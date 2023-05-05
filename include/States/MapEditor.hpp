#pragma once

#include "Context.hpp"
#include "GUIElements/Menu.hpp"
#include "GUIElements/TextureSelector.hpp"
#include "Map/TileMap.hpp"
#include "States/SaveableState.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

namespace game {
    class MapEditor final : public engine::SaveableState {
    public:
        MapEditor(Context *context);

        void process_input(sf::Event &event) override;
        void update(const float delta_time) override;
        void draw() override;
        void pause() override;
        void start() override;
        void save() override;
        
        #ifndef NDEBUG
        std::string get_state_name() const override;
        #endif

    private:
        void init_texture_selector_gui();

        void update_mouse_rectangle();
    void process_editor_input(sf::Event &event);

        sf::RectangleShape mouse_rectangle;
        sf::IntRect tile_texture_rect;
        sf::Vector2u mouse_pos_grid;

        std::unique_ptr<TileMap> tile_map;
        std::unique_ptr<gui::Menu> menu;
        std::unique_ptr<gui::TextureSelector> texture_selector;

        Context *context;
    };
} // namespace game