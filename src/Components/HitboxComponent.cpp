#include "Components/HitboxComponent.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

namespace components {
    HitboxComponent::HitboxComponent(sf::Sprite& sprite_, sf::Vector2f offset_, sf::Vector2f size):
        sprite(sprite_), offset(offset_) 
    {
        auto position = sprite.getPosition();
        hitbox.setPosition({
            position.x + offset.x,
            position.y + offset.y
        });
        
        hitbox.setSize(size);
        hitbox.setFillColor(sf::Color::Transparent);

        hitbox.setOutlineThickness(1.f); // TODO
        hitbox.setOutlineColor(sf::Color::Magenta); // TODO
    }

    const sf::Vector2f& HitboxComponent::get_position() const {
        return hitbox.getPosition();
    }

    const bool HitboxComponent::intersects(const sf::FloatRect& rect) const {
        return hitbox.getGlobalBounds().intersects(rect);
    }

    void HitboxComponent::set_position(const sf::Vector2f& position) {
        hitbox.setPosition(position);
        sprite.setPosition({
            position.x - offset.x,
            position.y - offset.y
        });
    }


    void HitboxComponent::update(const float delta_time) {
        auto position = sprite.getPosition();
        hitbox.setPosition({
            position.x + offset.x,
            position.y + offset.y
        });
    }

    void HitboxComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(hitbox, states);
        
    }

}