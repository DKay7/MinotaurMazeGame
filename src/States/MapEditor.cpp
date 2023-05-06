#include "States/MapEditor.hpp"
#include "Constants.hpp"
#include "Context.hpp"
#include "GUIElements/Menu.hpp"
#include "GUIElements/TextureSelector.hpp"
#include "Map/Tile.hpp"
#include "Map/TileMap.hpp"
#include "States/GamePause.hpp"
#include "States/MainMenu.hpp"
#include "Utils/Utils.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>
#include <iostream>
#include <memory>
#include <string>

namespace game {
    MapEditor::MapEditor(Context *context_) : context(context_) {

        context->asset_manager->add_texture(TEXTURE_ID::TILE_SHEET, Constants::tile_sheet_texture_path);

        init_size_menu();

        // tile_map = load_map_from_file("aboba.map", context);
        tile_map = std::make_unique<TileMap>(
            TEXTURE_ID::TILE_SHEET, context,
            sf::Vector2f(0, 0), Constants::map_size, Constants::layers_num,
            Constants::grid_size
        );

        tile_texture_rect =
            sf::IntRect(0, 0, tile_map->get_grid_size(), tile_map->get_grid_size());
        
        init_texture_selector_gui();
    }

    void MapEditor::init_size_menu() {
        sidebar_menu = 
            std::make_unique<gui::Menu>(
                context->asset_manager->get_font(FONT_ID::MAIN_FONT),
                Constants::map_editor_menu_title, Constants::map_editor_menu_bg_color,
                Constants::map_editor_menu_size, Constants::map_editor_menu_position,
                Constants::menu_button_indent,
                false
            );

        sidebar_menu->add_button(Constants::map_editor_menu_save_bt_text, [&](){
            save();
        }, false);

        sidebar_menu->add_button(Constants::map_editor_menu_load_bt_text, [&](){
            tile_map.reset();
            tile_map = load_map_from_file("aboba.map", context); // TODO
        }, false);

        sidebar_menu->add_button(Constants::map_editor_menu_exit_bt_text, [&](){
            auto &state_mgr = context->state_manager;
            state_mgr->pop_state();
            state_mgr->add_state(std::make_unique<MainMenu>(context));
        }, false);
    }

    void MapEditor::init_texture_selector_gui() {
        texture_selector = std::make_unique<gui::TextureSelector>(
            Constants::selector_gui_pos, tile_map->get_texture_sheet(),
            tile_map->get_grid_size()
        );

        auto grid_size = tile_map->get_grid_size();
        mouse_rectangle.setSize({grid_size, grid_size});
        mouse_rectangle.setFillColor(Constants::mouse_rect_bg_color);
        mouse_rectangle.setOutlineColor(Constants::mouse_rect_outline_color);
        mouse_rectangle.setOutlineThickness(Constants::texture_selector_outline_thick);

        mouse_rectangle.setTexture(&tile_map->get_texture_sheet());
        mouse_rectangle.setTextureRect(tile_texture_rect);
    }

    void MapEditor::process_input(sf::Event &event) {
        using kb = sf::Keyboard;

        auto mouse_pos = utils::get_mouse_position(*context->window);
        auto grid_size = tile_map->get_grid_size();
        
        if (event.type == sf::Event::KeyPressed and event.key.code == kb::Escape)
            context->state_manager->add_state(std::make_unique<GamePause>(context));
             
        process_editor_input(event);
        sidebar_menu->process_input(event, mouse_pos);
    }

    void MapEditor::process_editor_input(sf::Event &event) {
        using mouse = sf::Mouse;

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == mouse::Left) {

                if (texture_selector->active())
                    tile_texture_rect = texture_selector->get_texture_rect();
                else if (mouse_rect_active)
                    tile_map->add_tile(mouse_pos_grid.x, mouse_pos_grid.y, 0,
                                    tile_texture_rect);
            }

            if (event.mouseButton.button == mouse::Right and !texture_selector->active() and mouse_rect_active)
                tile_map->remove_tile(mouse_pos_grid.x, mouse_pos_grid.y, 0);
        }

        using kb = sf::Keyboard;

        if (event.type == sf::Event::KeyPressed and event.key.code == kb::Tab)
            texture_selector->change_shown();
    }

    void MapEditor::update_mouse_rectangle() {
        auto mouse_pos = utils::get_mouse_position(*context->window);
       
        mouse_rect_active = true;
        if (sidebar_menu->get_bounds().contains(mouse_pos)) {
            mouse_rect_active = false;
            return;
        }

        auto grid_size = tile_map->get_grid_size();
        mouse_pos_grid = utils::get_gridded_mouse(mouse_pos, grid_size);

        mouse_rectangle.setPosition(mouse_pos_grid.x * grid_size, mouse_pos_grid.y * grid_size);
        mouse_rectangle.setTextureRect(tile_texture_rect);
    }

    void MapEditor::update(const float delta_time) {
        sidebar_menu->update(delta_time);

        auto mouse_global_pos = sf::Mouse::getPosition(*context->window);
        texture_selector->update(mouse_global_pos);
        tile_map->update(delta_time);

        update_mouse_rectangle();
    }

    void MapEditor::draw() {
        auto &window = context->window;
        window->clear();

        window->draw(*tile_map);

        if (!texture_selector->active())
            window->draw(mouse_rectangle);

        window->draw(*sidebar_menu);
        window->draw(*texture_selector);

        window->display();
    }
    
    void MapEditor::pause() {}

    void MapEditor::start() {}

    void MapEditor::save() {
        tile_map->save_map_to_file();
    }
    
    #ifndef NDEBUG
        std::string MapEditor::get_state_name() const { return "MapEditor"; }
    #endif
} // namespace game