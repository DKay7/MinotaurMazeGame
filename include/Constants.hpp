#pragma once
#include "string"
#include <string>

namespace game
{
    enum class TEXTURE_ID {
        MAIN_MENU_BG,
        PLAYER_IDLE,
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
    };
    
    struct Constants final
    {   
        Constants();
        
        inline static const int window_height = 720;
        inline static const int window_width  = 1280;

        // inline is needed here 'cus initializer inside class 
        // definition is only allowed with integral and enum types.
        inline static const std::string main_menu_title = "Minotaur Maze";
        inline static const std::string game_title = "Minotaur Maze";

        inline static const std::string main_font_path = "../assets/fonts/RubikMonoOne-Regular.ttf";
        inline static const std::string main_menu_bg_image_path = "../assets/images/backgrounds/main_menu_bg_image.jpg";
        inline static const std::string player_idle_texture_path = "../assets/images/sprites/black_4.png";
    };
    

} // namespace game
