#pragma once
#include <memory>
#include "Context.hpp"

namespace game {
    class Game final {
    public:
        Game();
        void run();
    
    private:
        std::unique_ptr<game_engine::Context> context;

    };
}