#pragma once
#include <TGUI/Backends/SFML.hpp>
#include <memory>
#include "Context.hpp"

namespace game {
    class Game final{
    public:
        Game();
        void run();
    
    private:
        std::unique_ptr<Context> context;

    };
}