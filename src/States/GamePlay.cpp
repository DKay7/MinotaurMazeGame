#include "States/GamePlay.hpp"
#include "Managers/AssetManager.hpp"
#include "Constants.hpp"
#include "States/GamePause.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <exception>
#include <memory>
#include <stdexcept>

namespace game {
    GamePlay::GamePlay(Context* context_) : context(context_), map() {

        auto& ass_mgr = context->asset_manager;
        auto texture_added = ass_mgr->add_texture(TEXTURE_ID::PLAYER_SHEET, Constants::player_sheet_texture_path);
        player = std::make_unique<Player>(sf::Vector2f(0, 0), ass_mgr->get_texture(TEXTURE_ID::PLAYER_SHEET));
    }

    void GamePlay::process_input(sf::Event& event) { 
        using kb = sf::Keyboard;
        
        if (event.type == sf::Event::KeyPressed and event.key.code == kb::Escape)
            context->state_manager->add_state(std::make_unique<GamePause>(context));

    }

    void GamePlay::update(const float delta_time) {
        using kb = sf::Keyboard;
            
        if (kb::isKeyPressed(kb::W))
            player->move(delta_time, {0, -1});

        if (kb::isKeyPressed(kb::S))
            player->move(delta_time, {0, 1});
        
        if (kb::isKeyPressed(kb::D))
            player->move(delta_time, {1, 0});

        if (kb::isKeyPressed(kb::A))
            player->move(delta_time, {-1, 0});

        player->update(delta_time);
    }

    void GamePlay::draw() {
        
        auto &window = context->window;
        window->clear();
        window->draw(map);
        window->draw(*player);
        window->display();
    }

    void GamePlay::pause() {
    }

    void GamePlay::start() {
    }

    #ifndef NDEBUG
        std::string GamePlay::get_state_name() const {
            return "GamePlay";
        }
    #endif

} // namespace game

