#pragma once
#include <SFML/Window/Keyboard.hpp>

//--------------------------------------------------------------------------------

enum class TEXTURE_ID {
    MAIN_MENU_BG    = 0,
    PLAYER_SHEET    = 1,
    TILE_SHEET      = 2,
    GAME_FOG_BACK   = 3,
    GAME_FOG_FRONT  = 4,
    GAME_BLACKOUT   = 5,
};

//--------------------------------------------------------------------------------

enum class FONT_ID {
    MAIN_FONT = 0,
};

//--------------------------------------------------------------------------------
    
enum class ANIMATION_ID {
    PLAYER_IDLE             = 0,
    PLAYER_MOVE_LEFT        = 1,
    PLAYER_MOVE_RIGHT       = 2,
    PLAYER_MOVE_UP          = 3,
    PLAYER_MOVE_DOWN        = 4,
    PLAYER_MOVE_LEFT_UP     = 5,
    PLAYER_MOVE_LEFT_DOWN   = 6,
    PLAYER_MOVE_RIGHT_UP    = 7,
    PLAYER_MOVE_RIGHT_DOWN  = 8,
};

//--------------------------------------------------------------------------------

enum class SHADER_ID {
    BG_MOVING       = 0,
    BG_BLACKOUTING  = 1,
};

//--------------------------------------------------------------------------------

enum TILE_TYPES_ID: int {
    DEFAULT     = 0,
    COLLIDABLE  = 1 << 0,
    SPAWN_POINT = 1 << 2,
    WIN_POINT   = 1 << 3,
};

//--------------------------------------------------------------------------------

enum KEYBINDS: int {
    MOVE_UP     =  sf::Keyboard::W,
    MOVE_DOWN   =  sf::Keyboard::S,
    MOVE_LEFT   =  sf::Keyboard::A,
    MOVE_RIGHT  =  sf::Keyboard::D,
    
    OPEN_PAUSE       =  sf::Keyboard::Escape,
    OPEN_TILE_PICKER = sf::Keyboard::Tab,

    MOVE_VIEW_UP        = sf::Keyboard::W,
    MOVE_VIEW_DOWN      = sf::Keyboard::S,
    MOVE_VIEW_LEFT      = sf::Keyboard::A,
    MOVE_VIEW_RIGHT     = sf::Keyboard::D,
};
