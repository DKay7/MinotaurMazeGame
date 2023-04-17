#include "GamePlay.hpp"
#include "AssetManager.hpp"
#include "Constants.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

namespace game {
    GamePlay::GamePlay(std::shared_ptr<Context>& context) : cntx(context) {
    }

    void GamePlay::process_input(sf::Event& event) {
    }

    void GamePlay::update() {
    }

    void GamePlay::draw() {
        
        auto context = cntx.lock();
        auto &window = context->window;
        
        window->clear(); 
        auto circle = sf::CircleShape(100);
        auto circ_box = circle.getLocalBounds();
        circle.setOrigin(circ_box.width / 2., circ_box.height / 2.);
        circle.setPosition(Constants::window_width / 2.f, Constants::window_height / 2.f);
        window->draw(circle);
        // window->draw(textBox);
        window->display();

    }

    void GamePlay::pause() {

    }

    void GamePlay::start() {

    }


} // namespace game

