#include "Managers/StateManager.hpp"
#include <algorithm>
#ifdef DEBUG_STATE_MANAGER
#include <iostream>
#endif
#include <stdexcept>

namespace engine {
    StateManager::StateManager() {
        states_vector.reserve(5);
        next_states.reserve(2);
    }

    void StateManager::add_state(std::unique_ptr<State> new_state) {
        next_states.push_back(std::move(new_state));
    }

    void StateManager::pop_state() { ++pop_counter; }

    void StateManager::process_state_change() {
        #ifdef DEBUG_STATE_MANAGER
            std::cout << "\nBEGINING OF PROCESS CHANGE\n";
            print_states();
        #endif

        while (pop_counter != 0 and !states_vector.empty()) {
            states_vector.pop_back();
            --pop_counter;
        }

        if (!states_vector.empty())
            states_vector.back()->pause();

        while (!next_states.empty()) {
            states_vector.push_back(std::move(next_states.back()));
            next_states.pop_back();
        }

        #ifdef DEBUG_STATE_MANAGER
            std::cout << "\nENDING OF PROCESS CHANGE\n";
            print_states();
        #endif

        if (!states_vector.empty())
            states_vector.back()->start();
    }

    const std::unique_ptr<State> &StateManager::get_current_state() const {
        if (states_vector.empty())
            throw std::runtime_error("States vector is empty while you're trying to get current state");

        return states_vector.back();
    }

    const StateManager::state_vec_t &StateManager::get_states_vector() const {
        return states_vector;
    }


    #ifdef DEBUG_STATE_MANAGER
        void StateManager::print_states() const {
            std::cout << "\n------------------------------------\n";
            std::cout << "CURRENT STATES:\n";
            for (auto state_it = states_vector.rbegin(), state_et = states_vector.rend();
                state_it != state_et; ++state_it) {
                std::cout << "\t\t-> " << state_it->get()->get_state_name() << " ["
                          << reinterpret_cast<void *>(state_it->get()) << "]\n";
            }
        }
    #endif
} // namespace engine
