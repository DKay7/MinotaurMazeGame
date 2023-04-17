#pragma once
#include "string"

namespace game
{

    struct Constants
    {   
        Constants();
        
        static const int window_height = 720;
        static const int window_width  = 1280;

        // inline is needed here 'cus initializer inside class 
        // definition is only allowed with integral and enum types.
        inline static const std::string main_menu_title = "Welcome to Code Flow Game";
        inline static const std::string game_title = "Code Flow Game";
    };
    

} // namespace game
