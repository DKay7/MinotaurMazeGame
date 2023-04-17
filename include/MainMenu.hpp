#pragma once
#include "State.hpp"
#include "Context.hpp"
#include "Button.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <SFML/Graphics/Text.hpp>

namespace game
{
    class MainMenu: public engine::State {
    public:
        MainMenu(std::shared_ptr<Context>& context_);

        void process_input(sf::Event& event) override;
        void update() override;
        void draw() override;

    private:
        std::unique_ptr<Button> game_btn;
        std::unique_ptr<Button> exit_btn;
        sf::Text game_title;

        sf::Sprite background;

        std::weak_ptr<Context> cntx;

    };
} // namespace game

