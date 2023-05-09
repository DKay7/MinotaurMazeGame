#include "States/MapEditor.hpp"
#include "Constants.hpp"
#include "Context.hpp"
#include "GUIElements/Menu.hpp"
#include "GUIElements/TextureSelector.hpp"
#include "Managers/KeybindsManager.hpp"
#include "Map/Tile.hpp"
#include "Map/TileMap.hpp"
#include "States/PauseState.hpp"
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
#include <algorithm>
#include <ios>
#include <memory>
#include <sstream>
#include <string>
#include <utility>

namespace game {
    MapEditor::MapEditor(game_engine::Context *context_, std::unique_ptr<map::TileMap> tile_map_) : context(context_) {

        context->asset_manager->add_texture(TEXTURE_ID::TILE_SHEET, Constants::tile_sheet_texture_path);

        if (tile_map_)
            tile_map = std::move(tile_map_);
        else
            tile_map = std::make_unique<map::TileMap>(
                TEXTURE_ID::TILE_SHEET, context,
                Constants::map_size, Constants::layers_num, Constants::grid_size
            );

        tile_texture_rect =
            sf::IntRect(0, 0, tile_map->get_grid_size(), tile_map->get_grid_size());
        
        mouse_coords_text.setFont(context->asset_manager->get_font(FONT_ID::MAIN_FONT));
        mouse_coords_text.setCharacterSize(Constants::mouse_text_size);

        init_texture_selector_gui();
    }

//----------------------------------------INIT METHODS----------------------------------------
    
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

//----------------------------------------INPUT PROCESSING----------------------------------------

    void MapEditor::process_input(sf::Event &event) {
        using kb = sf::Keyboard;

        auto mouse_pos = utils::get_mouse_position(*context->window);
        auto grid_size = tile_map->get_grid_size();
        
        if (event.type == sf::Event::KeyPressed and event.key.code == kb::Escape)
            context->state_manager->add_state(std::make_unique<GamePause>(context));
             
        process_editor_input(event);
        process_view_move_input(event);
    }

    void MapEditor::process_editor_input(sf::Event &event) {
        using mouse = sf::Mouse;

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == mouse::Left) {

                if (texture_selector->active())
                    tile_texture_rect = texture_selector->get_texture_rect();
                else if (mouse_picker_active)
                    tile_map->add_tile(mouse_pos_grid.x, mouse_pos_grid.y, 0,
                                       tile_texture_rect, tile_collidable);
            }

            if (!texture_selector->active() and mouse_picker_active) {
                if (event.mouseButton.button == mouse::Right)
                    tile_map->remove_tile(mouse_pos_grid.x, mouse_pos_grid.y, 0);

                if (event.mouseButton.button == mouse::Middle)
                    tile_collidable = !tile_collidable;
            }

        }

        using kb = sf::Keyboard;

        if (event.type == sf::Event::KeyPressed and event.key.code == kb::Tab)
            texture_selector->change_shown();
    }

//----------------------------------------UPDATING----------------------------------------

    void MapEditor::update(const float delta_time) {
        auto mouse_global_pos = sf::Mouse::getPosition(*context->window);
        texture_selector->update(mouse_global_pos);
        tile_map->update(delta_time);

        update_mouse_rectangle();
        update_mouse_text();
        update_view(delta_time);
    }

    void MapEditor::update_mouse_rectangle() {
        context->window->setView(view);
        auto mouse_pos_view = utils::get_mouse_position(*context->window);
        context->window->setView(context->window->getDefaultView());
        
        auto grid_size = tile_map->get_grid_size();
        
        // checks that mouse rectangle inside the actual tilemap
        // if not, mouse rectangle is not updated
        // we can't use "contains" method here because of 
        // strict less sign (<) in last two lines (contains uses non-strict (<=) ones)

        mouse_picker_active = 
            mouse_pos_view.x >= 0 and
            mouse_pos_view.y >= 0 and
            mouse_pos_view.x < tile_map->get_map_size().x * grid_size and
            mouse_pos_view.y < tile_map->get_map_size().y * grid_size;

        if (mouse_picker_active) {
            mouse_pos_grid = utils::get_gridded_mouse(mouse_pos_view, grid_size);
            mouse_rectangle.setPosition(mouse_pos_grid.x * grid_size, mouse_pos_grid.y * grid_size);
            mouse_rectangle.setTextureRect(tile_texture_rect);
        }
    }

    void MapEditor::update_mouse_text() {
        context->window->setView(view);
        auto mouse_pos_view = utils::get_mouse_position(*context->window);
        context->window->setView(context->window->getDefaultView());
        auto mouse_pos = utils::get_mouse_position(*context->window);

        std::stringstream mouse_text_ss;
        mouse_text_ss << mouse_pos.x << ", " << mouse_pos.y 
                      << " {" << mouse_pos_view.x << ":" << mouse_pos_view.y  << "}" 
                      << " [" << mouse_pos_grid.x << ":" << mouse_pos_grid.y  << "]"
                      << " collision: [" << std::boolalpha << tile_collidable << "]";
        mouse_coords_text.setString(mouse_text_ss.str());

        mouse_coords_text.setPosition({
            mouse_pos.x + Constants::mouse_text_indent, mouse_pos.y - Constants::mouse_text_indent
        });
    }

//----------------------------------------DRAWING----------------------------------------

    void MapEditor::draw() {
        auto &window = context->window;
        window->clear();

        window->setView(view);
        window->draw(*tile_map);

        if (!texture_selector->active())
            window->draw(mouse_rectangle);

        window->setView(window->getDefaultView());
        window->draw(*texture_selector);
        window->draw(mouse_coords_text);

        window->display();
    }
    
//----------------------------------------PAUSE----------------------------------------
    
    void MapEditor::pause() {
        context->window->setView(context->window->getDefaultView());
    }

    void MapEditor::start() {
        
    }

//----------------------------------------SERIALIZATION----------------------------------------

    std::string MapEditor::serialize() const {
        return tile_map->serialize();
    }

    void MapEditor::deserialize(std::stringstream file_content) {
        tile_map.reset();
        
        tile_map = std::make_unique<map::TileMap>(
            map::TileMap::deserialize(std::move(file_content), context)
        );

    }

//----------------------------------------DEBUG----------------------------------------

    #ifndef NDEBUG
        std::string MapEditor::get_state_name() const { return "MapEditor"; }
    #endif
} // namespace game