#include "States/GamePause.hpp"
#include "Constants.hpp"
#include "Utils/Utils.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

namespace game {
    GamePause::GamePause(Context* context_): context(context_) {

        background.create(Constants::window_width, Constants::window_height);

        pause_text.setFont(context->asset_manager->get_font(FONT_ID::MAIN_FONT));
        pause_text.setString("PAUSED");
        pause_text.setCharacterSize(40);

        utils::center_text_on_window(pause_text);
        const auto& main_font = context->asset_manager->get_font(FONT_ID::MAIN_FONT);

        auto center_pos = sf::Vector2f({Constants::window_width / 2.f , Constants::window_height / 2.});
        center_pos.y += 75;
        // resume_btn = std::make_unique<Button>(center_pos, Constants::button_size, main_font, "Play", 
        //                       Constants::button_text_idle, Constants::button_text_hover, Constants::button_text_active);

        // center_pos.y += 35;
        // back_to_menu_btn = std::make_unique<Button>(center_pos, Constants::button_size, main_font, "Editor",
        //                       Constants::button_text_idle, Constants::button_text_hover, Constants::button_text_active);
    }
    
    
    void GamePause::process_input(sf::Event& event) {
        using kb = sf::Keyboard;

        if (event.type == sf::Event::KeyPressed and event.key.code == kb::Escape)
            context->state_manager->pop_state();
    }

    void GamePause::update(const float delta_time) {
            
    }

    void GamePause::draw() {
        auto &window = context->window;
        
        // window->clear();
        background.clear(sf::Color::Transparent);
        background.draw(pause_text);
        background.display();
        // window->draw(background);
        const sf::Texture& texture = background.getTexture();
        sf::Sprite bg_sprite(texture);

        window->draw(bg_sprite);
        window->display();
    }

}
