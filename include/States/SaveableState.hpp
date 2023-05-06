#pragma once

#include "States/State.hpp"

namespace states_engine {
    class SaveableState: public State {
        public:
            SaveableState() { }
            virtual ~SaveableState() = default;
            virtual void save() = 0;
            virtual void load() = 0;
    };
}