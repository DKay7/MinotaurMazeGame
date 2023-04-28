#pragma once
#include "Managers/StateManager.hpp"
#include "Managers/AssetManager.hpp"
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>

namespace game {
    class Context final {

    public:
        Context();
        std::unique_ptr<engine::StateManager> state_manager;
        std::unique_ptr<sf::RenderWindow> window;
        std::unique_ptr<AssetManager> asset_manager;
    };

} // namespace game 
