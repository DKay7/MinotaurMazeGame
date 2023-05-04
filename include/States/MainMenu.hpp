#pragma once
#include "Context.hpp"
#include "GUIElements/Button.hpp"
#include "GUIElements/Menu.hpp"
#include "State.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>

namespace game {
    class MainMenu final : public engine::State {
    public:
        MainMenu(Context *context_);

        void process_input(sf::Event &event) override;
        void update(const float delta_time) override;
        void draw() override;

    #ifndef NDEBUG
        std::string get_state_name() const override;
    #endif

    private:
        std::unique_ptr<gui::Menu> menu;

        sf::Sprite background;

        Context *context;
    };
} // namespace game
