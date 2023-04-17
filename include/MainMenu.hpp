#pragma once
#include "State.hpp"
#include "Context.hpp"
#include <memory>
#include <SFML/Graphics/Text.hpp>

namespace game
{
    class MainMenu: public engine::State {
    public:
        MainMenu(std::shared_ptr<Context>& context_);

        void init() override;
        void process_input(sf::Event& event) override;
        void update() override;
        void draw() override;

    private:
        sf::Text game_title;
        std::shared_ptr<Context> context;


    };
} // namespace game

