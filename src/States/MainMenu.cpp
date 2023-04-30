#include "States/MainMenu.hpp"
#include "Constants.hpp"
#include "GUIElements/Button.hpp"
#include "Managers/AssetManager.hpp"
#include "States/GamePlay.hpp"
#include "States/MapEditor.hpp"
#include "Utils/Utils.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <memory>
#include <stdexcept>


namespace game {
    MainMenu::MainMenu(Context *context_) : context(context_) {


        context->asset_manager->add_font(FONT_ID::MAIN_FONT, Constants::main_font_path);
        context->asset_manager->add_texture(TEXTURE_ID::MAIN_MENU_BG, Constants::main_menu_bg_image_path);

        background.setColor(Constants::bg_sprite_color);
        background.setTexture(context->asset_manager->get_texture(TEXTURE_ID::MAIN_MENU_BG));


        menu = std::make_unique<gui::Menu>(
            context->asset_manager->get_font(FONT_ID::MAIN_FONT),
            Constants::main_menu_title, Constants::button_size.y);

        menu->add_button(Constants::main_menu_play_bt_text, [&]() {
            auto &state_mgr = context->state_manager;
            state_mgr->pop_state();
            state_mgr->add_state(std::make_unique<GamePlay>(context));
        });

        menu->add_button(Constants::main_menu_editor_bt_text, [&]() {
            auto &state_mgr = context->state_manager;
            state_mgr->pop_state();
            state_mgr->add_state(std::make_unique<MapEditor>(context));
        });

        menu->add_button(Constants::main_menu_exit_bt_text, [&]() { 
            context->window->close(); 
        });
    }

    void MainMenu::process_input(sf::Event &event) {
        auto mouse_pos = utils::get_mouse_position(*context->window);
        menu->process_input(event, mouse_pos);
    }

    void MainMenu::update(const float delta_time) { 
        menu->update(delta_time); 
    }

    void MainMenu::draw() {
        auto &window = context->window;

        window->clear();
        window->draw(background);

        window->draw(*menu);
        window->display();
    }

    #ifndef NDEBUG
        std::string MainMenu::get_state_name() const { return "MainMenu"; }
    #endif
} // namespace game
