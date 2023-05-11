#include "States/GamePlay.hpp"
#include "Managers/AssetManager.hpp"
#include "Constants.hpp"
#include "Managers/KeybindsManager.hpp"
#include "Map/TileMap.hpp"
#include "States/PauseState.hpp"
#include "Utils/Utils.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <exception>

#ifndef NDEBUG
    #include <iostream>
#endif

#include <memory>
#include <stdexcept>
#include <utility>

namespace game {
    GamePlay::GamePlay(game_engine::Context* context_) : context(context_){
        context->asset_manager->add_texture(TEXTURE_ID::TILE_SHEET, Constants::tile_sheet_texture_path);
        map = std::make_unique<map::TileMap>(TEXTURE_ID::TILE_SHEET, context, Constants::map_size, 
                                             Constants::layers_num, Constants::grid_size);


        auto& ass_mgr = context->asset_manager;
        auto texture_added = ass_mgr->add_texture(TEXTURE_ID::PLAYER_SHEET, Constants::player_sheet_texture_path);
        player = std::make_unique<entities::Player>(sf::Vector2f(60, 60), ass_mgr->get_texture(TEXTURE_ID::PLAYER_SHEET));
    }

//-------------------------------------PROCESS INPUT-------------------------------------------

    void GamePlay::process_input(sf::Event &event) { 
        using kb = sf::Keyboard;
        
        if (event.type == sf::Event::KeyPressed and 
            event.key.code == managers::get_keybind(KEYBINDS::OPEN_PAUSE))
            
            context->state_manager->add_state(std::make_unique<GamePause>(context));

    }

    void GamePlay::process_view_move_input(sf::Event &event) { }

//-------------------------------------UPDATE-------------------------------------------

    void GamePlay::update(const float delta_time) {
        #ifndef NDEBUG
            update_debug_text();
        #endif

        using kb = sf::Keyboard;
        using managers::get_keybind;

        #define move_player(key_code, direction_x, direction_y)         \
            if (kb::isKeyPressed(get_keybind(KEYBINDS::key_code)))      \
                player->move(delta_time, {direction_x, direction_y});   \


        move_player(MOVE_UP,    0, -1)
        move_player(MOVE_DOWN,  0,  1)
        move_player(MOVE_RIGHT, 1,  0)
        move_player(MOVE_LEFT, -1,  0)
        
        player->update(delta_time);

        map->update_tiles_collision(*player, delta_time);
        map->update_world_bounds_collision(*player, delta_time);
        
        map->update(delta_time);
        update_view(delta_time);
    }

    #ifndef NDEBUG
    void GamePlay::update_debug_text() {
            context->window->setView(view);
            auto mouse_pos_view = utils::get_mouse_position(*context->window);
            context->window->setView(context->window->getDefaultView());
            auto mouse_pos = utils::get_mouse_position(*context->window);

            std::stringstream mouse_text_ss;
            mouse_text_ss << mouse_pos.x << ", " << mouse_pos.y 
                        << " {" << mouse_pos_view.x << ":" << mouse_pos_view.y  << "}";
            mouse_coords_text.setString(mouse_text_ss.str());

            mouse_coords_text.setPosition({
                mouse_pos.x + Constants::mouse_text_indent, mouse_pos.y - Constants::mouse_text_indent
            });
            mouse_coords_text.setFont(context->asset_manager->get_font(FONT_ID::MAIN_FONT));
            mouse_coords_text.setCharacterSize(12);
    }
    #endif

    void GamePlay::update_view(const float delta_time) {
        view.setCenter(player->get_position());
    }

//-------------------------------------DRAW-------------------------------------------

    void GamePlay::draw() {
        
        auto &window = context->window;
        window->clear();
        window->setView(view);
        window->draw(*map);
        window->draw(*player);

        #ifndef NDEBUG
            window->setView(window->getDefaultView());
            window->draw(mouse_coords_text);
        #endif

        window->display();
    }

//-------------------------------------PAUSE-------------------------------------------

    void GamePlay::pause() {
        context->window->setView(context->window->getDefaultView());
    }

    void GamePlay::start() { }

//-------------------------------------SERIALIZATION-------------------------------------------

    std::string GamePlay::serialize() const {
        #ifndef NDEBUG
            std::cout << "GAME SAVED\n";
        #endif
        return map->serialize();
    }

    void GamePlay::deserialize(std::stringstream file_content) {
        #ifndef NDEBUG
            std::cout << "GAME LOADED\n";
        #endif

        map.reset();
        map = std::make_unique<map::TileMap>(
            map::TileMap::deserialize(std::move(file_content), context)
        );
    }

//-------------------------------------DEBUG-------------------------------------------

    #ifndef NDEBUG
        std::string GamePlay::get_state_name() const {
            return "GamePlay";
        }
    #endif

} // namespace game

