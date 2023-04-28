#include "States/MainMenu.hpp"
#include "Managers/AssetManager.hpp"
#include "Constants.hpp"
#include "GUIElements/Button.hpp"
#include "States/GamePlay.hpp"
#include "States/MapEditor.hpp"
#include "Utils/Utils.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <memory>
#include <stdexcept>

namespace game
{
    MainMenu::MainMenu(Context* context_): context(context_)
    {
        auto font_load_result = context->asset_manager->add_font(FONT_ID::MAIN_FONT, Constants::main_font_path);
        
        if (!font_load_result)
            throw std::runtime_error("Can not find font file '" + Constants::main_font_path + "'");

        auto texture_load_result = context->asset_manager->add_texture(TEXTURE_ID::MAIN_MENU_BG, Constants::main_menu_bg_image_path);
        
        if (!texture_load_result)
            throw std::runtime_error("Can not find image file '" + Constants::main_menu_bg_image_path + "'");
        
        background.setColor(Constants::bg_sprite_color);
        background.setTexture(context->asset_manager->get_texture(TEXTURE_ID::MAIN_MENU_BG));

        
        // const auto& main_font = context->asset_manager->get_font(FONT_ID::MAIN_FONT);
        // game_title.setFont(main_font);
        // game_title.setString(Constants::main_menu_title); 
        // utils::center_text_on_window(game_title);

        // auto center_pos = sf::Vector2f({Constants::window_width / 2.f , Constants::window_height / 2.});

        // center_pos.y += Constants::button_size.y * 2;
        // game_btn = utils::create_default_button(center_pos, main_font, Constants::main_menu_play_bt_text);

        // center_pos.y += Constants::button_size.y;
        // edit_btn = utils::create_default_button(center_pos, main_font, Constants::main_menu_editor_bt_text);

        // center_pos.y += Constants::button_size.y;
        // exit_btn = utils::create_default_button(center_pos, main_font, Constants::main_menu_exit_bt_text);

    }

    void MainMenu::process_input(sf::Event& event) {
        auto &state_mgr = context->state_manager;

        if (game_btn->is_pressed()) {
            state_mgr->pop_state();
            state_mgr->add_state(std::make_unique<GamePlay>(context));
        }

        else if (edit_btn->is_pressed()) {
            state_mgr->pop_state();
            state_mgr->add_state(std::make_unique<MapEditor>(context));
        }

        else if (exit_btn->is_pressed())
            context->window->close();
    }

    void MainMenu::update(const float delta_time) {
        auto mouse_pos = utils::get_mouse_position(*context->window);
        game_btn->update(mouse_pos);
        edit_btn->update(mouse_pos);
        exit_btn->update(mouse_pos);
    }

    void MainMenu::draw() {
            auto& window = context->window;

            window->clear();
            window->draw(background);

            window->draw(*game_btn);
            window->draw(*edit_btn);
            window->draw(*exit_btn);

            window->draw(game_title);
            window->display();
    }

    #ifndef NDEBUG
        std::string MainMenu::get_state_name() const {
            return "MainMenu";
        }
    #endif
} // namespace game

