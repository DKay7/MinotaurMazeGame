#pragma once
#include <memory>
#include "Context.hpp"

namespace game {
    class Game {
    public:
        Game();
        void run();
    
    private:
        std::shared_ptr<Context> context;

    };
}