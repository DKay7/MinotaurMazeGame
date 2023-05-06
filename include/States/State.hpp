#pragma once
#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>

namespace states_engine {
    class State {
    public:
        State() {}
        virtual ~State() = default;

        virtual void process_input(sf::Event& event) = 0;
        virtual void update(const float delta_time) = 0;
        virtual void draw() = 0;

        virtual void pause() {}
        virtual void start() {}
        
        #ifndef NDEBUG
            virtual std::string get_state_name() const = 0;
        #endif
    };

} // namespace engine