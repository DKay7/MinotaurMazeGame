#pragma once
#include "State.hpp"
#include "../Context.hpp"
#include "../GUIElements/Button.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <SFML/Graphics/Text.hpp>

namespace game
{
    class MainMenu final: public engine::State {
    public:
        MainMenu(Context* context_);

        void process_input(sf::Event& event) override;
        void update(const float delta_time) override;
        void draw() override;

    private:
        std::unique_ptr<Button> game_btn;
        std::unique_ptr<Button> edit_btn;
        std::unique_ptr<Button> exit_btn;
        
        sf::Text game_title;

        sf::Sprite background;

        Context* context;

    };
} // namespace game

