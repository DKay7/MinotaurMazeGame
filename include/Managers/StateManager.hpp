#pragma once
#include <cstdint>
#include <vector>
#include <memory>
#include "../States/State.hpp"

namespace engine {
    class StateManager final {
    private:
        std::vector<std::unique_ptr<State>> states_vector;
        std::unique_ptr<State> next_state;  // we need this because we don't want to 
                                            // push new state until current state is complete
        
        uint32_t pop_counter = 0;
        std::vector<std::unique_ptr<State>> next_states;
        
    public:
        StateManager();
        
        #ifndef NDEBUG
            void print_states() const;
        #endif

        void add_state(std::unique_ptr<State> new_state);
        void pop_state();
        void process_state_change();
        std::unique_ptr<State>& get_current_state(); 
    };

} // namespace engine