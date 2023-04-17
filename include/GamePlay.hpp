#pragma once

#include "Context.hpp"
#include "State.hpp"
#include "TextBox.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <array>
#include <memory>


namespace game {
    class GamePlay: public engine::State {
    public:
        GamePlay(std::shared_ptr<Context>& context);
        void process_input(sf::Event& event) override;
        void update() override;
        void draw() override;
        void pause() override;
        void start() override;

    private:
        TextBox textBox;
        std::weak_ptr<Context> cntx;
        std::array<sf::Sprite, 15 * 15> game_map;
    };


} // namespace game
