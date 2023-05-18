#pragma once

#include "Context.hpp"
#include "Entities/Entity.hpp"
#include "Entities/Player.hpp"
#include "Interfaces/LoadableInterface.hpp"
#include "Map/TileMap.hpp"
#include "Interfaces/SaveableInterface.hpp"
#include "States/CameraState.hpp"
#include "States/SaveableLoadableState.hpp"
#include "States/State.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <array>
#include <cmath>
#include <memory>
#include <string>


namespace game {
    class GamePlay final: public states_engine::SaveableLoadableState,
                          public states_engine::CameraState {
    public:
        GamePlay(game_engine::Context *context_);

        // event processing
        void process_input(sf::Event &event) override;
        void process_view_move_input(sf::Event &event) override;

        // updating
        void update(const float delta_time) override;
        #ifndef NDEBUG
            void update_debug_text();
        #endif

        // state methods
        void draw() override;
        void pause() override;
        void start() override;

        // saving
        std::string serialize() const override;
        void deserialize(std::stringstream file_content) override;

        // state debug info
        #ifndef NDEBUG
            std::string get_state_name() const override;
        #endif 

    private:
        // init
        void init_textures();
        void init_background();
        void init_shaders();
        void init_player(std::set<map::TileMap::coord_t> spawn_points);

        // updating
        void check_win_and_update();
        void update_shaders(const float delta_time); 
        void update_view(const float delta_time) override;

        std::set<map::TileMap::coord_t> win_points;  

        #ifndef NDEBUG
            sf::Text mouse_coords_text; // text for debug 
        #endif
        sf::Sprite background_back;
        sf::Sprite background_front;
        sf::Sprite background_blackout;

        sf::Vector2f bg_back_offset =  {0, 0};
        sf::Vector2f bg_front_offset = {0, 0};

        std::unique_ptr<map::TileMap> map;
        std::unique_ptr<entities::Player> player;
        bool exploring_mode = false;
        
        game_engine::Context *context;
    };


} // namespace game
