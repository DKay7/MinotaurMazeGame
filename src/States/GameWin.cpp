#include "States/GameWin.hpp"
#include "Settings/AssetParamentes.hpp"
#include "Settings/Enums.hpp"
#include "Settings/GameWinState.hpp"
#include "GUIElements/Menu.hpp"
#include "Settings/MainMenu.hpp"
#include "States/MainMenu.hpp"
#include "Utils/Utils.hpp"
#include <memory>

namespace game {        
    GameWin::GameWin(game_engine::Context* context_): context(context_) {
        menu = std::make_unique<gui::Menu>(context->asset_manager->get_font(FONT_ID::MAIN_FONT), settings::game_win_title);

        menu->add_button(settings::game_win_get_home_btn_text, [&] {
            auto& state_manager = context->state_manager;
            state_manager->pop_state(); // popping game win state;
            state_manager->pop_state(); // popping game play state;
            state_manager->add_state(std::make_unique<MainMenu>(context));
        });

        menu->add_button(settings::game_win_continue_btn_text, [&] {
            auto& state_manager = context->state_manager;
            state_manager->pop_state(); // popping game win state;
        });

        context->asset_manager->add_texture(TEXTURE_ID::WINNER_BG, settings::winner_bg_image_path);
        bg_sprite.setTexture(context->asset_manager->get_texture(TEXTURE_ID::WINNER_BG));
        bg_sprite.setColor(settings::bg_sprite_color);

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
        window->draw(bg_sprite);
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