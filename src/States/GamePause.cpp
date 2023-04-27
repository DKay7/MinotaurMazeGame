#include "States/GamePause.hpp"
#include "Constants.hpp"
#include "States/MainMenu.hpp"
#include "Utils/Utils.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>

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
        resume_btn = std::make_unique<Button>(center_pos, Constants::button_size, main_font, "Resume", 
                              Constants::button_text_idle, Constants::button_text_hover, Constants::button_text_active);

        center_pos.y += 35;
        back_to_menu_btn = std::make_unique<Button>(center_pos, Constants::button_size, main_font, "Back to menu",
                              Constants::button_text_idle, Constants::button_text_hover, Constants::button_text_active);
    }
    
    
    void GamePause::process_input(sf::Event& event) {
        using kb = sf::Keyboard;
        auto &state_mgr = context->state_manager;

        if (event.type == sf::Event::KeyPressed and event.key.code == kb::Escape)
            state_mgr->pop_state();

        if (resume_btn->is_pressed())
            state_mgr->pop_state();
        
        else if (back_to_menu_btn->is_pressed()) {
            state_mgr->pop_state(); // popping pause state
            state_mgr->pop_state(); // popping gameplay state
            state_mgr->add_state(std::make_unique<MainMenu>(context));
        }
    }

    void GamePause::update(const float delta_time) {
        auto mouse_position = utils::get_mouse_position(*context->window);
        resume_btn->update(mouse_position);
        back_to_menu_btn->update(mouse_position); 
    }   

    void GamePause::draw() {
        auto &window = context->window;
        
        background.clear(sf::Color::Transparent);
        background.draw(pause_text);
        background.draw(*resume_btn);
        background.draw(*back_to_menu_btn);

        background.display();
        
        const sf::Texture& texture = background.getTexture();
        bg_sprite.setTexture(texture);

        window->draw(bg_sprite);
        window->display();
    }

    #ifndef NDEBUG
        std::string GamePause::get_state_name() const {
            return "GamePause";
        }
    #endif
}
