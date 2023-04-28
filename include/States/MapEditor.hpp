#pragma once

#include "Context.hpp"
#include "States/State.hpp"
#include <memory>


namespace game {
    class MapEditor: public engine::State {
    public:
        MapEditor(Context* context);

        void process_input(sf::Event& event) override;
        void update(const float delta_time) override;
        void draw() override;
        void pause() override;
        void start() override;

        #ifndef NDEBUG
            std::string get_state_name() const override;
        #endif
        
    private:
        Context* context;
    };
}