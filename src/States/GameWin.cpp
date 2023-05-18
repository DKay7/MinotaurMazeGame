#include "States/GameWin.hpp"
#include "Constants/Enums.hpp"
#include "Constants/GameWinState.hpp"
#include "GUIElements/Menu.hpp"
#include "States/MainMenu.hpp"
#include "Utils/Utils.hpp"
#include <memory>

namespace game {        
    GameWin::GameWin(game_engine::Context* context_): context(context_) {
        menu = std::make_unique<gui::Menu>(context->asset_manager->get_font(FONT_ID::MAIN_FONT), Constants::game_win_title);

        menu->add_button(Constants::game_win_get_home_btn_text, [&] {
            context->state_manager->add_state(std::make_unique<MainMenu>(context));
        });

        menu->add_button(Constants::game_win_continue_btn_text, [&] {
            auto& state_manager = context->state_manager;
            state_manager->pop_state(); // popping game win state;
            state_manager->pop_state(); // popping game play state;
            context->state_manager->add_state(std::make_unique<MainMenu>(context));
        });
    }

    void GameWin::process_input(sf::Event& event) {
        auto mouse_pos = utils::get_mouse_position(*context->window);
        menu->process_input(event, mouse_pos);
    }

    void GameWin::update(const float delta_time) { 
        menu->update(delta_time);
    }

    void GameWin::draw() {
        auto &window = context->window;
        window->clear(); 
        window->draw(*menu);
        window->display();
    }

    //-------------------------------------DEBUG-------------------------------------------

    #ifndef NDEBUG
        std::string GameWin::get_state_name() const {
            return "GameWin";
        }
    #endif
}