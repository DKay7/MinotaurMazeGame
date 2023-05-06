#include "Context.hpp"
#include "Managers/AssetManager.hpp"

namespace game_engine {
    Context::Context() {
        state_manager = std::make_unique<managers::StateManager>();
        window = std::make_unique<sf::RenderWindow>();
        asset_manager = std::make_unique<managers::AssetManager>();
    }
} // namecpace game