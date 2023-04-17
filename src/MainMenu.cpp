#include "MainMenu.hpp"
#include "Constants.hpp"
#include <SFML/Graphics.hpp>
#include <assert.h>
#include <iostream>

namespace game
{
    MainMenu::MainMenu(std::shared_ptr<Context>& context_): context(context_)
    {} 

    void MainMenu::init() {
        auto result = context->asset_manager->add_font(FONT_ID::MAIN_FONT, "../assets/fonts/RubikMonoOne-Regular.ttf");
        
        assert(result and "Can not load font :(");

        game_title.setFont(context->asset_manager->get_font(FONT_ID::MAIN_FONT));
        game_title.setString(Constants::main_menu_title); 

        auto text_bounds = game_title.getLocalBounds();
        game_title.setOrigin(text_bounds.width / 2, text_bounds.height / 2);
        game_title.setPosition({Constants::window_width / 2 , Constants::window_height / 2});

    }

    void MainMenu::process_input(sf::Event& event) {
        if (event.type == sf::Event::KeyPressed) {
            
            std::cout << event.key.code << std::endl;
        }
    }

    void MainMenu::update() {

    }

    void MainMenu::draw() {
        context->window->clear();
        context->window->draw(game_title);
        context->window->display();
    }

} // namespace game

