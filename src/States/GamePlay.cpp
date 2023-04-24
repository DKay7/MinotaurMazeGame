#include "States/GamePlay.hpp"
#include "Managers/AssetManager.hpp"
#include "Constants.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <exception>
#include <memory>
#include <stdexcept>

namespace game {
    GamePlay::GamePlay(Context* context_) : context(context_) {

        auto& ass_mgr = context->asset_manager;
        auto texture_added = ass_mgr->add_texture(TEXTURE_ID::PLAYER_SHEET, Constants::player_sheet_texture_path);
        
        if (!texture_added)
            throw std::runtime_error("Can not load texture '" + Constants::player_sheet_texture_path + "'");
        
        player = std::make_unique<Player>(sf::Vector2f(0, 0), ass_mgr->get_texture(TEXTURE_ID::PLAYER_SHEET));
        
    }

    void GamePlay::process_input(sf::Event& event) {
    }

    void GamePlay::update(const float delta_time) {
        player->update(delta_time);
    }

    void GamePlay::draw() {
        auto &window = context->window;
        window->clear(); 

        player->draw(*window.get());
        window->display();
    }

    void GamePlay::pause() {

    }

    void GamePlay::start() {

    }


} // namespace game

