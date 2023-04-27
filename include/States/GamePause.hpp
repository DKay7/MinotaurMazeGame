#pragma once

#include "Context.hpp"
#include "GUIElements/Button.hpp"
#include "States/State.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>


namespace game {
    class GamePause: public engine::State {
        public:
            GamePause(Context* context_);
            void process_input(sf::Event& event) override;
            void update(const float delta_time) override;
            void draw() override;
            
            #ifndef NDEBUG
                std::string get_state_name() const override;
            #endif
        private:
            
            std::unique_ptr<Button> resume_btn;
            std::unique_ptr<Button> back_to_menu_btn;

            bool end_pause = false;

            sf::Sprite bg_sprite;
            sf::RenderTexture background;
            sf::Text pause_text;
            Context* context;
    };
}