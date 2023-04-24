#include "States/MainMenu.hpp"
#include "Managers/AssetManager.hpp"
#include "Constants.hpp"
#include "GUIElements/Button.hpp"
#include "States/GamePlay.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <assert.h>
#include <iostream>
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
        
        background.setColor({255, 255, 255, 50});
        background.setTexture(context->asset_manager->get_texture(TEXTURE_ID::MAIN_MENU_BG));

        const auto& main_font = context->asset_manager->get_font(FONT_ID::MAIN_FONT);
        game_title.setFont(main_font);
        game_title.setString(Constants::main_menu_title); 

        auto text_bounds = game_title.getLocalBounds();
        game_title.setOrigin(text_bounds.width / 2, text_bounds.height / 2);
        auto center_pos = sf::Vector2f({Constants::window_width / 2.f , Constants::window_height / 2.});
        game_title.setPosition(center_pos);

        // TODO unique pointers
        center_pos.y += 75;
        game_btn = std::make_unique<Button>(center_pos, sf::Vector2f(75, 35), main_font, "Play",
                              sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, 
                              sf::Color::White, sf::Color(100, 107, 99), sf::Color(46, 139, 87));
        
        center_pos.y += 35;
        exit_btn = std::make_unique<Button>(center_pos, sf::Vector2f(75, 35), main_font, "Exit",
                              sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, 
                              sf::Color::White, sf::Color(100, 107, 99), sf::Color(46, 139, 87));
    }

    void MainMenu::process_input(sf::Event& event) {
    
        if (game_btn->is_pressed())
            context->state_manager->add_state(std::make_unique<GamePlay>(context), true);

        if (exit_btn->is_pressed()) 
            context->window->close();
    }

    void MainMenu::update(const float delta_time) {
        auto mouse_pos = context->window->mapPixelToCoords(sf::Mouse::getPosition(*context->window.get()));
        game_btn->update(mouse_pos);
        exit_btn->update(mouse_pos);
    }

    void MainMenu::draw() {
            auto& window = context->window;

            window->clear();
            window->draw(background);

            game_btn->draw(*window.get());
            exit_btn->draw(*window.get());
            window->draw(game_title);
            window->display();

    }
} // namespace game

