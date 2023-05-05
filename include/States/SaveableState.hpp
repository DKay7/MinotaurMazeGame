#pragma once

#include "States/State.hpp"

namespace engine {
    class SaveableState: public State {
        public:
            SaveableState() { }
            virtual ~SaveableState() = default;
            virtual void save() = 0;
    };
}