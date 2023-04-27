#include "Game.hpp"
#include "States/MainMenu.hpp"
#include "Constants.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <memory>
#include <vector>
#include <numeric>

namespace game {
    Game::Game() {
        context = std::make_unique<Context>();
        context->window->create(sf::VideoMode(Constants::window_width, Constants::window_height), Constants::game_title, sf::Style::Close);
        context->window->setFramerateLimit(Constants::frame_limit);
        context->state_manager->add_state(std::make_unique<MainMenu>(context.get()));
    
    }   

    void Game::run() {
        sf::Clock clock;


        while (context->window->isOpen()) {
            engine::StateManager &mgr = *context->state_manager;
            mgr.process_state_change();
            engine::State &state = *mgr.get_current_state();


            sf::Event event;
            while(context->window->pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    context->window->close();
                else
                    state.process_input(event);
            }

            
            const float delta_time = clock.restart().asSeconds();
            
            state.update(delta_time);
            state.draw();
        }
    }

} // namespace game