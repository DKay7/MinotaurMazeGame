#pragma once

#include "Entity.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>


namespace entities {
    class Player final: public Entity  {

    public:
        Player(sf::Vector2f position, const sf::Texture& texture_sheet);
        void update(const float delta_time) override;

    };

}
