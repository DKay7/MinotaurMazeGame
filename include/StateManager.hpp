#pragma once
#include <vector>
#include <memory>
#include <State.hpp>

namespace engine {
    class StateManager final {
    private:
        std::vector<std::unique_ptr<State>> states_vector;
        std::unique_ptr<State> next_state;  // we need this because we don't want to 
                                            // push new state until current state is complete

        bool should_add     = false;
        bool should_remove  = false;
        bool should_replace = false;

        
    public:
        StateManager();
        
        void add_state(std::unique_ptr<State> new_state, bool replace_current_state = false);
        void pop_state();
        void process_state();
        std::unique_ptr<State>& get_current_state(); 
    };

} // namespace engine