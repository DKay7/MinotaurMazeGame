#pragma once

#include "Settings/WindowParameters.hpp"
#include "Settings/CameraState.hpp"
#include "Settings/Enums.hpp"
#include "States/State.hpp"
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>

namespace states_engine {
    class CameraState: virtual public states_engine::State {
    public:
        CameraState() {
            view.setSize({
                settings::window_width,
                settings::window_height,
            });
            
            view.setCenter({
                settings::window_width / 2.f,
                settings::window_height / 2.f,
            });
        }

        virtual ~CameraState() = default;
        
        virtual void process_view_move_input(sf::Event& event) {
            if (event.type == sf::Event::KeyPressed) {

                #define move_view(key_code, x, y)                                       \
                    case key_code:                                                      \
                        view_move_dir = {                                               \
                            x * settings::view_move,                                   \
                            y * settings::view_move                                    \
                        };                                                              \
                        break;
                
                switch (static_cast<KEYBINDS>(event.key.code)) {
                    move_view(MOVE_VIEW_UP,      0, -1)
                    move_view(MOVE_VIEW_DOWN,    0,  1)
                    move_view(MOVE_VIEW_RIGHT,   1,  0)
                    move_view(MOVE_VIEW_LEFT,   -1,  0)
                        
                    default:
                        break;
                }

                #undef move_view 
            }
        }

        virtual void update_view(const float delta_time) {
            view.move(view_move_dir);
            view_move_dir = {0, 0};
        }

    protected:
        sf::Vector2f view_move_dir = {0, 0};
        sf::View view;

    };
}