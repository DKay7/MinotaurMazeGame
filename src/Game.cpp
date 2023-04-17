#include "Game.hpp"
#include "MainMenu.hpp"
#include "Constants.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace game {
    Game::Game() {
        context = std::make_shared<Context>();
        context->window->create(sf::VideoMode(Constants::window_width, Constants::window_height), Constants::game_title, sf::Style::Close);
        
        context->state_manager->add_state(std::make_unique<MainMenu>(context));
    }   

    void Game::run() {
        while (context->window->isOpen()) {

            engine::StateManager &mgr = *context->state_manager;

            mgr.process_state();

            engine::State &state = *mgr.get_current_state();

            sf::Event event;
            

            while(context->window->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    std::cout << "1";
                    context->window->close();
                }
                else
                    state.process_input(event);

            }

            state.update();
            state.draw();
        }
    }
} // namespace game