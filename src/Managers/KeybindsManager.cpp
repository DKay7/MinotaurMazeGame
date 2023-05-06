#include "Managers/KeybindsManager.hpp"
#include <SFML/Window/Keyboard.hpp>

namespace managers {
    
    sf::Keyboard::Key get_keybind(KEYBINDS key) {
        return static_cast<sf::Keyboard::Key>(key);
    }

}