#pragma once
#include "string"
#include <string>

namespace game
{

    struct Constants
    {   
        Constants();
        
        inline static const int window_height = 720;
        inline static const int window_width  = 1280;

        // inline is needed here 'cus initializer inside class 
        // definition is only allowed with integral and enum types.
        inline static const std::string main_menu_title = "Minotaur Maze";
        inline static const std::string game_title = "Minotaur Maze";

        inline static const std::string main_font_path = "../assets/fonts/RubikMonoOne-Regular.ttf";
        inline static const std::string main_menu_bg_image_path = "../assets/images/main_menu_bg_image.jpg";
    };
    

} // namespace game
