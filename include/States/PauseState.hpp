#pragma once

#include "Context.hpp"
#include "GUIElements/Button.hpp"
#include "GUIElements/Menu.hpp"
#include "Interfaces/SaveableInterface.hpp"
#include "States/State.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>

namespace game {
    class GamePause final: public states_engine::State {
    public:
        GamePause(game_engine::Context *context_);
        void process_input(sf::Event &event) override;
        void update(const float delta_time) override;
        void draw() override;

        #ifndef NDEBUG
            std::string get_state_name() const override;
        #endif
    private:
        std::unique_ptr<gui::Menu> menu;
        
        std::function<void()> save_function;

        sf::Sprite bg_sprite;
        sf::RenderTexture render_texture;
        game_engine::Context *context;
    };
} // namespace game