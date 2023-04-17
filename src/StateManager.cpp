#include "StateManager.hpp"

namespace engine {
    StateManager::StateManager() {

    }

    void StateManager::add_state(std::unique_ptr<State> new_state, bool should_replace_current_state) {
        should_add = true;
        next_state = std::move(new_state);
        should_replace = should_replace_current_state;
    }

    void StateManager::pop_state() {
        should_remove = true;
    }

    void StateManager::process_state_change() {
        if (should_remove and !states_vector.empty()) {
            states_vector.pop_back();

            if (!states_vector.empty())
                states_vector.back()->start();

            should_remove = false;
        }

        if (should_add) {
            if (should_replace and !states_vector.empty()) {
                states_vector.pop_back();
                should_replace = false;
            }

            if (!states_vector.empty())
                states_vector.back()->pause();

            states_vector.push_back(std::move(next_state));
            should_add = false;

            states_vector.back()->start();
        }
    }

    std::unique_ptr<State>& StateManager::get_current_state() {
        return states_vector.back();
    } 

}
