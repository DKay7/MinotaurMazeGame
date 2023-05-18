#pragma once 

#include "Context.hpp"
#include "GUIElements/Menu.hpp"
#include "States/State.hpp"
#include <memory>

namespace game {
    class GameWin final: public states_engine::State {

        public:
            GameWin(game_engine::Context* context);
            void process_input(sf::Event& event) override;
            void update(const float delta_time) override;
            void draw() override;

        private:
            game_engine::Context* context;
            std::unique_ptr<gui::Menu> menu;
    };
}
