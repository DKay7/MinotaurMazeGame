#include "States/PauseState.hpp"
#include "Settings/WindowParameters.hpp"
#include "Settings/PauseMenu.hpp"
#include "GUIElements/Menu.hpp"
#include "States/MainMenu.hpp"
#include "Interfaces/SaveableInterface.hpp"
#include "States/SaveableLoadableState.hpp"
#include "Utils/Utils.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <functional>

#ifndef NDEBUG
    #include <iostream>
#endif

#include <memory>
#include <string>
#include <type_traits>

namespace game {
    GamePause::GamePause(game_engine::Context *context_):context(context_) {

        render_texture.create(settings::window_width, settings::window_height);

        menu = std::make_unique<gui::Menu>(
            context->asset_manager->get_font(FONT_ID::MAIN_FONT),
            settings::pause_menu_title);

        menu->add_button(settings::pause_menu_resume_bt_text, [&]() {
            auto &state_mgr = context->state_manager;
            state_mgr->pop_state();
        });

        // Because we are in constructor of the pause state
        // pause state is not currently in states vector,
        // therefore, current state = state where pause state was called from
        const auto& caller_state = context->state_manager->get_current_state();

        // FIXME Sorry I don't know how to do it without dynamic_cast ;C
        // checks if state is saveable to add "save" and "load" buttons
        if (dynamic_cast<states_engine::SaveableLoadableState*>(caller_state.get())) {
            menu->add_button(settings::pause_menu_save_bt_text, [&]() {
                auto &state_mgr = context->state_manager;   
                const auto& states_vec = state_mgr->get_states_vector();
                const auto& prev_state = states_vec.rbegin()[1]; // getting previous state
                dynamic_cast<states_engine::SaveableLoadableState*>(prev_state.get())->save_state("../assets/map/aboba.map"); // TODO
            });

            menu->add_button(settings::pause_menu_load_bt_text, [&]() {
                auto &state_mgr = context->state_manager;
                const auto& states_vec = state_mgr->get_states_vector();
                const auto& prev_state = states_vec.rbegin()[1]; // getting previous state

                dynamic_cast<states_engine::SaveableLoadableState*>(prev_state.get())->load_state("../assets/map/aboba.map"); // TODO
            });
        }
        
        menu->add_button(settings::pause_menu_back_bt_text, [&]() {
            auto &state_mgr = context->state_manager;
            state_mgr->pop_state(); // popping pause state
            state_mgr->pop_state(); // popping previous state
            state_mgr->add_state(std::make_unique<MainMenu>(context));
        });
    }

    void GamePause::process_input(sf::Event &event) {
        using kb = sf::Keyboard;
        auto &state_mgr = context->state_manager;

        if (event.type == sf::Event::KeyPressed and event.key.code == kb::Escape)
            state_mgr->pop_state();

        auto mouse_position = utils::get_mouse_position(*context->window);
        menu->process_input(event, mouse_position);
    }

    void GamePause::update(const float delta_time) {
        menu->update(delta_time);
    }

    void GamePause::draw() {
        auto &window = context->window;

        render_texture.clear(sf::Color::Transparent);
        render_texture.draw(*menu);

        render_texture.display();

        const sf::Texture &texture = render_texture.getTexture();
        bg_sprite.setTexture(texture);

        window->draw(bg_sprite);
        window->display();
    }

    #ifndef NDEBUG
        std::string GamePause::get_state_name() const { return "GamePause"; }
    #endif
} // namespace game
