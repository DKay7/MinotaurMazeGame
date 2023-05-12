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
#include <SFML/Graphics/Sprite.hpp>
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
        void update_view(const float delta_time) override;
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
        #ifndef NDEBUG
            sf::Text mouse_coords_text; // text for debug 
        #endif

        sf::Sprite background;
        std::unique_ptr<map::TileMap> map;
        std::unique_ptr<entities::Player> player;
        game_engine::Context *context;
    };


} // namespace game
