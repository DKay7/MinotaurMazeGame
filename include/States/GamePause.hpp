#pragma once

#include "Context.hpp"
#include "States/State.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>


namespace game {
    class GamePause: public engine::State {
        public:
            GamePause(Context* context_);
            void process_input(sf::Event& event) override;
            void update(const float delta_time) override;
            void draw() override;

        private:
            
            bool end_pause = false;
            sf::RenderTexture background;
            sf::Text pause_text;
            Context* context; // TODO maybe move context to State class 
    };


}