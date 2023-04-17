#pragma once
#include <SFML/Graphics.hpp>

namespace engine
{
   class Button final {
    public:
        Button();
        void draw(sf::RenderTarget* target);
    private:
        sf::RectangleShape shape;
        sf::Font* font;
        sf::Text text;

        sf::Color active_color;
        sf::Color hover_color;
        sf::Color idle_color;
    }; 
} // namespace engine

