#include "States/GamePlay.hpp"
#include "Managers/AssetManager.hpp"
#include "Constants/AssetParamentes.hpp"
#include "Constants/GamePlayState.hpp"
#include "Managers/KeybindsManager.hpp"
#include "Map/Tile.hpp"
#include "Map/TileMap.hpp"
#include "States/PauseState.hpp"
#include "Utils/Utils.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <exception>
#include <iterator>

#ifndef NDEBUG
    #include <iostream>
#endif

#include <memory>
#include <stdexcept>
#include <utility>

namespace game {
    GamePlay::GamePlay(game_engine::Context* context_) : context(context_) {

        init_textures();
        init_background();
        init_shaders();

        map = std::make_unique<map::TileMap>(TEXTURE_ID::TILE_SHEET, context, Constants::map_size, 
                                             Constants::layers_num, Constants::grid_size);

        init_player(map->get_spawn_points_coords());
    }

//-------------------------------------INIT METHODS-------------------------------------------
    void GamePlay::init_player(std::set<map::TileMap::coord_t> spawn_points) {
        sf::Vector2f spawn_coords;

        if (!spawn_points.empty()) {
            srand(time(NULL));
            int spawn_point_idx = rand() % spawn_points.size();
            auto spawn_point_it = spawn_points.begin();
            std::advance(spawn_point_it, spawn_point_idx);
            spawn_coords = sf::Vector2f {
                std::get<0>(*spawn_point_it), 
                std::get<1>(*spawn_point_it)
            };
        }
        else
            spawn_coords = {600, 600};

        auto& ass_mgr = context->asset_manager;
        player = std::make_unique<entities::Player>(spawn_coords, ass_mgr->get_texture(TEXTURE_ID::PLAYER_SHEET));
    }

    void GamePlay::init_shaders() {
        auto& ass_mgr = context->asset_manager;
        ass_mgr->add_shader(SHADER_ID::BG_MOVING, sf::Shader::Vertex, Constants::bg_shader_path);
        ass_mgr->add_shader(SHADER_ID::BG_BLACKOUTING, sf::Shader::Fragment, "../assets/shaders/bg_blackout.frag");

        // auto blackout_shader = ass_mgr->get_shader_ptr(SHADER_ID::BG_BLACKOUTING); // TODO use shaders!
        // blackout_shader->setUniform("u_radius", 10);
    }

    void GamePlay::init_textures() {
        auto& ass_mgr = context->asset_manager;

        ass_mgr->add_texture(TEXTURE_ID::TILE_SHEET, Constants::tile_sheet_texture_path);
        ass_mgr->add_texture(TEXTURE_ID::GAME_FOG_BACK,  Constants::game_fog_back_texture_path );
        ass_mgr->add_texture(TEXTURE_ID::GAME_FOG_FRONT, Constants::game_fog_front_texture_path);
        ass_mgr->add_texture(TEXTURE_ID::PLAYER_SHEET, Constants::player_sheet_texture_path);
        ass_mgr->add_texture(TEXTURE_ID::GAME_BLACKOUT, Constants::game_blackout_texture_path);

        ass_mgr->get_texture_ptr(TEXTURE_ID::GAME_FOG_BACK)->setRepeated(true);
        ass_mgr->get_texture_ptr(TEXTURE_ID::GAME_FOG_FRONT)->setRepeated(true);
        
    }

    void GamePlay::init_background() {
        auto& ass_mgr = context->asset_manager;

        background_back.setTexture(ass_mgr->get_texture(TEXTURE_ID::GAME_FOG_BACK));
        background_front.setTexture(ass_mgr->get_texture(TEXTURE_ID::GAME_FOG_FRONT));

        background_back.setTextureRect({0, 0, Constants::window_width, Constants::window_height});
        background_front.setTextureRect({0, 0, Constants::window_width, Constants::window_height});

        background_back.setColor(Constants::game_bg_back_color);
        background_front.setColor(Constants::game_bg_front_color);

        background_blackout.setTextureRect({0, 0, Constants::window_width, Constants::window_height});
        background_blackout.setTexture(ass_mgr->get_texture(TEXTURE_ID::GAME_BLACKOUT));
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
        update_shaders(delta_time);
    }

    void GamePlay::update_shaders(const float delta_time) {
        auto movement_component = player->get_movement_component();

        bg_back_offset  += movement_component->get_velocity() * delta_time / Constants::bg_back_offset_coef;
        bg_front_offset += movement_component->get_velocity() * delta_time / Constants::bg_front_offset_coef;
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
                    mouse_pos.x + Constants::game_debug_mouse_text_indent,
                    mouse_pos.y - Constants::game_debug_mouse_text_indent
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
        auto& ass_mgr = context->asset_manager;
        auto bg_shader = ass_mgr->get_shader_ptr(SHADER_ID::BG_MOVING);
        // auto blackout_shader = ass_mgr->get_shader_ptr(SHADER_ID::BG_BLACKOUTING); // TODO use shaders!

        window->clear();
        bg_shader->setUniform("offset", bg_back_offset);
        window->draw(background_back, bg_shader);

        bg_shader->setUniform("offset", bg_front_offset);
        window->draw(background_front, bg_shader);

        window->setView(view);
        map->draw_fogged_at_position(*window, player->get_position());
        window->draw(*player);

        #ifndef NDEBUG
            window->setView(window->getDefaultView());
            window->draw(mouse_coords_text);
        #endif

        // re-sets default view only if it's not debug mode,
        // 'cuz in debug mode, default view has been already set
        // several lines above
        #ifdef NDEBUG
        window->setView(window->getDefaultView());
        #endif
        // blackout_shader->setUniform("u_lightPosition", static_cast<sf::Glsl::Vec2>(player->get_position())); // TODO use shaders!
        window->draw(background_blackout);

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

        player.reset();
        init_player(map->get_spawn_points_coords());
    }

//-------------------------------------DEBUG-------------------------------------------

    #ifndef NDEBUG
        std::string GamePlay::get_state_name() const {
            return "GamePlay";
        }
    #endif

} // namespace game

