#pragma once

#include "Context.hpp"
#include "Entities/Entity.hpp"
#include "Entities/Player.hpp"
#include "Map/TileMap.hpp"
#include "States/SaveableState.hpp"
#include "States/State.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <array>
#include <memory>


namespace game {
    class GamePlay final: public states_engine::SaveableState {
    public:
        GamePlay(game_engine::Context* context_);
        void process_input(sf::Event& event) override;
        void update(const float delta_time) override;
        void draw() override;
        void pause() override;
        void start() override;
        void save() override;
        void load() override;
        
        #ifndef NDEBUG
            std::string get_state_name() const override;
        #endif 

    private:
        std::unique_ptr<map::TileMap> map;
        std::unique_ptr<Player> player;
        game_engine::Context* context;
    };


} // namespace game
