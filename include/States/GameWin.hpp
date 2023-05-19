#pragma once 

#include "Context.hpp"
#include "GUIElements/Menu.hpp"
#include "States/State.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <memory>

namespace game {
    class GameWin final: public states_engine::State {

        public:
            GameWin(game_engine::Context* context);
            void process_input(sf::Event& event) override;
            void update(const float delta_time) override;
            void draw() override;
        
            #ifndef NDEBUG
                std::string get_state_name() const override;
            #endif

        private:
            sf::Sprite bg_sprite;
            game_engine::Context* context;
            std::unique_ptr<gui::Menu> menu;
    };
}
