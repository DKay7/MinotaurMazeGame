#pragma once
#include "string"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <string>

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

//--------------------------------------------------------------------------------

namespace Constants  {   
//--------------------------------------------------------------------------------

    // window parameters
    const int window_height = 720;
    const int window_width  = 1280;
    const std::string game_title = "Minotaur Maze";
    const long int frame_limit = 60;

//--------------------------------------------------------------------------------

    // texture selector
    const sf::Color texture_selector_select_color = sf::Color::Red;
    const sf::Color texture_selector_bg_color = {50, 50, 50, 100};
    const sf::Color texture_selector_outline_color = {255, 255, 255, 200};
    const float texture_selector_outline_thick = 1;

//--------------------------------------------------------------------------------

    // map
    const sf::Vector2u map_size = {20, 20};
    const int layers_num = 3;
    const float grid_size = 48; 
    const int rebound_coef = 2;
    const int tiles_to_check = 8;
    const int fogged_map_size = 5;
    
//--------------------------------------------------------------------------------

    // buttons
    const int default_bt_text_size = 15;
    const sf::Vector2f button_size = {75, 35};
    const sf::Color button_bg_color    = sf::Color::Transparent;
    const sf::Color button_text_idle   = sf::Color::White;
    const sf::Color button_text_hover  = {100, 107, 99};
    const sf::Color button_text_active = {46, 139, 87};
    const int button_bg_indent = 20;

//--------------------------------------------------------------------------------

    // menu gui element
    const int menu_bg_indent = 20;
    const int menu_button_indent = 5;

//--------------------------------------------------------------------------------

    // main menu
    const sf::Color bg_sprite_color = {255, 255, 255, 50};
    const std::string main_menu_title = "Minotaur Maze";
    const std::string main_menu_play_bt_text   = "play";
    const std::string main_menu_editor_bt_text = "editor";
    const std::string main_menu_exit_bt_text   = "exit";

//--------------------------------------------------------------------------------
        
    // map editor
    const sf::Color mouse_rect_bg_color = {255, 255, 255, 150};
    const sf::Color mouse_rect_outline_color = sf::Color::Cyan;
    const sf::Vector2f selector_gui_pos = {40, 40};
    const int mouse_text_size = 12;
    const float mouse_text_indent = 7;
    
//--------------------------------------------------------------------------------

    // pause menu
    const std::string pause_menu_title            = "Paused";
    const std::string pause_menu_resume_bt_text   = "resume";
    const std::string pause_menu_save_bt_text     = "save";
    const std::string pause_menu_load_bt_text     = "load";
    const std::string pause_menu_back_bt_text     = "back to menu";

//--------------------------------------------------------------------------------

    // animation parameters
    const sf::Vector2i default_frame_size = {48, 48};
    const float idle_tpf = 7;
    const float movement_tpf = 1.2;
        
//--------------------------------------------------------------------------------
        
    // player parameters
    const float player_movement_max_speed = 250;
    const float default_acceleration = 900;
    const float default_deceleration = 600;
    const sf::Vector2f player_hitbox_offset = {0, 0};
    const sf::Vector2f player_hitbox_size = {24, 48};
    const sf::Vector2f player_hitbox_idle_size = {24, 24};

//--------------------------------------------------------------------------------

    // camera state
    const float view_move = 20.f;


//--------------------------------------------------------------------------------

    // gameplay state
    const sf::Color game_bg_back_color  = {255, 255, 255, 240};
    const sf::Color game_bg_front_color = {255, 255, 255, 100};
    const float bg_back_offset_coef  = 300;
    const float bg_front_offset_coef = 600;

//--------------------------------------------------------------------------------

    // assets parameters
    // TODO solve issue with relative paths.
    const std::string tile_sheet_texture_path = "../assets/images/tiles/Dung_tileset.png";
    const std::string bg_shader_path = "../assets/shaders/bg_shader.vert";
    const std::string game_fog_front_texture_path = "../assets/images/backgrounds/game_fog_bg_front.png";
    const std::string game_fog_back_texture_path = "../assets/images/backgrounds/game_fog_bg_back.png";
    const std::string game_blackout_texture_path = "../assets/images/backgrounds/bg_blackouting_5.png";

    const std::string main_font_path = "../assets/fonts/RubikMonoOne-Regular.ttf"; 
    const std::string main_menu_bg_image_path = "../assets/images/backgrounds/main_menu_bg_image.jpg";
    const std::string player_sheet_texture_path = "../assets/images/sprites/black_4.png";
}  // namespace constants
    
