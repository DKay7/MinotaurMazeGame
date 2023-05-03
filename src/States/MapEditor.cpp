#include "States/MapEditor.hpp"
#include "Constants.hpp"
#include "Context.hpp"
#include "GUIElements/Menu.hpp"
#include "GUIElements/TextureSelector.hpp"
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

namespace game {
    MapEditor::MapEditor(Context* context_): context(context_) { 
        
        context->asset_manager->add_texture(TEXTURE_ID::TILE_SHEET, Constants::tile_sheet_texture_path);
        tile_map = std::make_unique<TileMap>(context->asset_manager->get_texture(TEXTURE_ID::TILE_SHEET), sf::Vector2f(0, 0), 
                                            Constants::map_size, Constants::layers_num, Constants::grid_size);


        // menu = std::make_unique<gui::Menu>(context->asset_manager->get_font(FONT_ID::MAIN_FONT), "Map Editor", Constants::button_size.y, sf::Vector2f(0, 0), false);
        // menu->add_button("exit", [&](){
        //     auto &state_mgr = context->state_manager;
        //     state_mgr->pop_state();
        //     state_mgr->add_state(std::make_unique<MainMenu>(context));
        // }, false); // TODO Remove
        
        tile_texture_rect = {0, 0, 64, 64}; // TODO remove;
        init_selector();

    }

    void MapEditor::init_selector() {
        texture_selector = std::make_unique<gui::TextureSelector>(sf::Vector2f(20, 20), sf::Vector2f(500, 500), tile_map->get_texture_sheet(), tile_map->get_grid_size()); // TODO remove constants
        
        auto grid_size = tile_map->get_grid_size();
        mouse_selector_shape.setSize({grid_size, grid_size});
        mouse_selector_shape.setFillColor({255, 255, 255, 150});
        mouse_selector_shape.setOutlineColor(sf::Color::Cyan);
        mouse_selector_shape.setOutlineThickness(1.f); //TODO remove

        mouse_selector_shape.setTexture(&tile_map->get_texture_sheet());
        mouse_selector_shape.setTextureRect(tile_texture_rect);
    }

    void MapEditor::process_input(sf::Event& event) {
        using kb = sf::Keyboard;
        
        auto mouse_pos = utils::get_mouse_position(*context->window);
        auto grid_size = tile_map->get_grid_size();

        // menu->process_input(event, mouse_pos);

        if (event.type == sf::Event::KeyPressed and event.key.code == kb::Escape)
            context->state_manager->add_state(std::make_unique<GamePause>(context));
        
        process_editor_input(event);
    }

    void MapEditor::process_editor_input(sf::Event& event) {
        if (event.type == sf::Event::MouseButtonPressed) {
            
            switch (event.mouseButton.button) {
                
                case sf::Mouse::Left:
                    tile_map->add_tile(mouse_pos_grid.x, mouse_pos_grid.y, 0, tile_texture_rect);
                    break;
                
                case sf::Mouse::Right:
                    tile_map->remove_tile(mouse_pos_grid.x, mouse_pos_grid.y, 0);
                    break;

                default:
                    break;
            }
        }

        using kb = sf::Keyboard;

        if (event.type == sf::Event::KeyPressed) {
            auto texture_size = tile_map->get_texture_sheet().getSize();

            switch (event.key.code) {
                case kb::R:
                    tile_texture_rect.left = (tile_texture_rect.left + 64) % texture_size.x; // TODO REMOVE THIS CRINGE!!
                    break;
                
                case kb::E:
                    tile_texture_rect.left -= 64;
                    tile_texture_rect.left = tile_texture_rect.left >= 0 ?  tile_texture_rect.left : (texture_size.x - 64);

                    break;
                
                default:
                    break;
            }
        }
    }

    void MapEditor::update_mouse_selector() {
        auto mouse_pos = utils::get_mouse_position(*context->window);
        auto grid_size = tile_map->get_grid_size();
        mouse_pos_grid = utils::get_gridded_mouse(mouse_pos, grid_size);

        mouse_selector_shape.setPosition(mouse_pos_grid.x * grid_size, mouse_pos_grid.y * grid_size);
        mouse_selector_shape.setTextureRect(tile_texture_rect);
    }

    void MapEditor::update(const float delta_time) {
        // menu->update(delta_time);
        tile_map->update(delta_time);
        update_mouse_selector();
    }

    void MapEditor::draw() {
        auto &window = context->window;
        window->clear();
        
        // sf::RectangleShape rect; // TODO remove
        // rect.setSize({7 * tile_map->get_grid_size(), Constants::window_height});
        // rect.setFillColor(sf::Color(9, 53, 54));

        // window->draw(rect);
        // window->draw(*menu);
        
        window->draw(*tile_map);   
        
        window->draw(mouse_selector_shape);
        window->draw(*texture_selector);
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