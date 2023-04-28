#pragma once

#include "Context.hpp"
#include "Entities/Entity.hpp"
#include "Entities/Player.hpp"
#include "Map/TileMap.hpp"
#include "States/State.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <array>
#include <memory>


namespace game {
    class GamePlay final: public engine::State {
    public:
        GamePlay(Context* context_);
        void process_input(sf::Event& event) override;
        void update(const float delta_time) override;
        void draw() override;
        void pause() override;
        void start() override;
        
        #ifndef NDEBUG
            std::string get_state_name() const override;
        #endif 

    private:
        TileMap map;
        std::unique_ptr<Player> player;
        Context* context;
    };


} // namespace game
