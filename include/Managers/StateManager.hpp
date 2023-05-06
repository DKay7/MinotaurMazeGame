#pragma once
#include <cstdint>
#include <vector>
#include <memory>
#include "States/State.hpp"

namespace managers {
    class StateManager final { 
    public:
        StateManager();
        
        using state_vec_t = std::vector<std::unique_ptr<states_engine::State>>;

        void add_state(std::unique_ptr<states_engine::State> new_state);
        void pop_state();
        void process_state_change();

        const std::unique_ptr<states_engine::State>& get_current_state() const;
        const state_vec_t& get_states_vector() const;
        
        #ifndef NDEBUG
            void print_states() const;
        #endif
    
    private:
        state_vec_t states_vector;
                
        /*
            states vector may be updated only in "update" method in game cycle,
            therefore, we need pop_counter and next_states to record future changes
        */
        uint32_t pop_counter = 0;
        state_vec_t next_states;
    };

} // namespace engine