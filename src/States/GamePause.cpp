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

        background.setColor({255, 255, 255, 50});
        background.setTexture(context->asset_manager->get_texture(TEXTURE_ID::MAIN_MENU_BG));
        
        pause_text.setFont(context->asset_manager->get_font(FONT_ID::MAIN_FONT));
        pause_text.setString("PAUSED");
        pause_text.setCharacterSize(40);

        utils::center_text_on_window(pause_text);
    }
    
    
    void GamePause::process_input(sf::Event& event) {
        using kb = sf::Keyboard;

        if (event.type == sf::Event::KeyPressed and event.key.code == kb::Escape)
            end_pause = true;
    }

    void GamePause::update(const float delta_time) {
        if(end_pause)
            context->state_manager->pop_state();
    }

    void GamePause::draw() {
        auto &window = context->window;
        
        window->clear();
        window->draw(background); 
        window->draw(pause_text);
        window->display();
    }

}
