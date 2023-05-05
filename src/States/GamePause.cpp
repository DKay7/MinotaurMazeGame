#include "States/GamePause.hpp"
#include "Constants.hpp"
#include "GUIElements/Menu.hpp"
#include "States/MainMenu.hpp"
#include "States/SaveableState.hpp"
#include "Utils/Utils.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <functional>
#include <memory>
#include <string>

namespace game {
    GamePause::GamePause(Context *context_):context(context_) {

        render_texture.create(Constants::window_width, Constants::window_height);

        menu = std::make_unique<gui::Menu>(
            context->asset_manager->get_font(FONT_ID::MAIN_FONT),
            Constants::pause_menu_title, Constants::button_size.y);

        menu->add_button(Constants::pause_menu_resume_bt_text, [&]() {
            auto &state_mgr = context->state_manager;
            state_mgr->pop_state();
        });
        
        menu->add_button(Constants::pause_menu_save_bt_text, [&]() {
            auto &state_mgr = context->state_manager;
            const auto& states_vec = state_mgr->get_states_vector();
            const auto& prev_state = states_vec.rbegin()[1];
            static_cast<engine::SaveableState*>(prev_state.get())->save();
        });

        menu->add_button(Constants::pause_menu_back_bt_text, [&]() {
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
