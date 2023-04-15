#include <SFML/Graphics.hpp>

int main() {    

    sf::RenderWindow window(sf::VideoMode(800, 600), "Code flow game");

    while (window.isOpen()) {
        sf::Event event;
        
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }



    }
     
    return 0;
}