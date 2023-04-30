#pragma once
#include "string"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

namespace game
{
    enum class TEXTURE_ID {
        MAIN_MENU_BG,
        PLAYER_SHEET,
    };

    enum class FONT_ID {
        MAIN_FONT,
    };
    
    enum class ANIMATION_ID {
        PLAYER_IDLE,
        PLAYER_MOVE_LEFT,
        PLAYER_MOVE_RIGHT,
        PLAYER_MOVE_UP,
        PLAYER_MOVE_DOWN,
        PLAYER_MOVE_LEFT_UP,
        PLAYER_MOVE_LEFT_DOWN,
        PLAYER_MOVE_RIGHT_UP,
        PLAYER_MOVE_RIGHT_DOWN,
    };
    
    struct Constants final  {   

//--------------------------------------------------------------------------------
        // map
        inline static const sf::Vector2u map_size = {100, 100};
        inline static const int layers_num = 3;
        inline static const float grid_size = 50; 
//--------------------------------------------------------------------------------

        //buttons
        inline static const int default_bt_text_size = 15;
        inline static const sf::Vector2f button_size = {75, 35};
        inline static const sf::Color button_bg_color    = sf::Color::Transparent;
        inline static const sf::Color button_text_idle   = sf::Color::White;
        inline static const sf::Color button_text_hover  = sf::Color(100, 107, 99);
        inline static const sf::Color button_text_active = sf::Color(46, 139, 87);

//--------------------------------------------------------------------------------

        // main menu
        inline static const sf::Color bg_sprite_color = sf::Color(255, 255, 255, 50);
        inline static const std::string main_menu_title = "Minotaur Maze";
        inline static const std::string main_menu_play_bt_text   = "play";
        inline static const std::string main_menu_editor_bt_text = "editor";
        inline static const std::string main_menu_exit_bt_text   = "exit";

//--------------------------------------------------------------------------------

        //pause menu
        inline static const std::string pause_menu_title            = "Paused";
        inline static const std::string pause_menu_resume_bt_text   = "resume";
        inline static const std::string pause_menu_back_bt_text     = "back to menu";

//--------------------------------------------------------------------------------

        // window parameters
        inline static const int window_height = 720;
        inline static const int window_width  = 1280;
        inline static const std::string game_title = "Minotaur Maze";
        inline static const long int frame_limit = 60;

//--------------------------------------------------------------------------------

        // animation parameters
        inline static const sf::Vector2i default_frame_size = {48, 48};
        inline static const float idle_tpf = 7;
        inline static const float movement_tpf = 1.2;

        
//--------------------------------------------------------------------------------
        
        // movement parameters
        inline static const float player_covement_max_speed = 250;
        inline static const float default_acceleration = 900;
        inline static const float default_deceleration = 600;

//--------------------------------------------------------------------------------

        // assets parameters
        inline static const std::string main_font_path = "../assets/fonts/RubikMonoOne-Regular.ttf"; // TODO solve issue with relative paths.
        inline static const std::string main_menu_bg_image_path = "../assets/images/backgrounds/main_menu_bg_image.jpg";
        inline static const std::string player_sheet_texture_path = "../assets/images/sprites/black_4.png";
    };
    

} // namespace game
