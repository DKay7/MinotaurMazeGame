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
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>

namespace game {
    GamePlay::GamePlay(game_engine::Context* context_) : context(context_){
        context->asset_manager->add_texture(TEXTURE_ID::TILE_SHEET, Constants::tile_sheet_texture_path);
        map = std::make_unique<map::TileMap>(TEXTURE_ID::TILE_SHEET, context, sf::Vector2f(0, 0), 
                                             Constants::map_size, Constants::layers_num, Constants::grid_size);


        auto& ass_mgr = context->asset_manager;
        auto texture_added = ass_mgr->add_texture(TEXTURE_ID::PLAYER_SHEET, Constants::player_sheet_texture_path);
        player = std::make_unique<Player>(sf::Vector2f(0, 0), ass_mgr->get_texture(TEXTURE_ID::PLAYER_SHEET));
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
        using kb = sf::Keyboard;
        using managers::get_keybind;

        #define move_player(key_code, direction_x, direction_y)                                     \
            if (kb::isKeyPressed(get_keybind(KEYBINDS::key_code)) and                               \
                utils::is_movement_allowed(player->get_position(), map.get(), {direction_x, direction_y}))    \
                player->move(delta_time, {direction_x, direction_y});
        
        move_player(MOVE_UP,    0, -1)
        move_player(MOVE_DOWN,  0,  1)
        move_player(MOVE_RIGHT, 1,  0)
        move_player(MOVE_LEFT, -1,  0)

        // if (kb::isKeyPressed(get_keybind(KEYBINDS::MOVE_UP)))
        //     player->move(delta_time, {0, -1});

        // if (kb::isKeyPressed(get_keybind(KEYBINDS::MOVE_DOWN)))
        //     player->move(delta_time, {0, 1});
        
        // if (kb::isKeyPressed(get_keybind(KEYBINDS::MOVE_RIGHT)))
        //     player->move(delta_time, {1, 0});

        // if (kb::isKeyPressed(get_keybind(KEYBINDS::MOVE_LEFT)))
        //     player->move(delta_time, {-1, 0});

        player->update(delta_time);
        map->update(delta_time);
        update_view(delta_time);
    }

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
        window->display();
    }

//-------------------------------------PAUSE-------------------------------------------

    void GamePlay::pause() {
        context->window->setView(context->window->getDefaultView());
    }

    void GamePlay::start() { }

//-------------------------------------SERIALIZATION-------------------------------------------

    std::string GamePlay::serialize() const {
        std::cout << "GAME SAVED\n";
        return map->serialize();
    }

    void GamePlay::deserialize(std::stringstream file_content) {
        std::cout << "GAME LOADED\n";
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

