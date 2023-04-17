#pragma once
#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>

namespace engine {
    class State {
    public:
        State() {}
        virtual ~State() = default;

        virtual void init() = 0;
        virtual void process_input(sf::Event& event) = 0;
        virtual void update() = 0;
        virtual void draw() = 0;

        virtual void pause() {}
        virtual void start() {}
    };

} // namespace engine