#include "Context.hpp"
#include "Managers/AssetManager.hpp"

namespace game {
    Context::Context() {
        state_manager = std::make_unique<engine::StateManager>();
        window = std::make_unique<sf::RenderWindow>();
        asset_manager = std::make_unique<AssetManager>();
    }
} // namecpace game