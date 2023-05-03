#include "GUIElements/TextureSelector.hpp"
#include "Constants.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>

namespace gui {
    TextureSelector::TextureSelector(const sf::Vector2f position, const sf::Texture &texture, const float grid_size): 
        grid_size(grid_size), texture_rect({0, 0, static_cast<int>(grid_size), static_cast<int>(grid_size)})
    {   
        bounds.setSize(static_cast<sf::Vector2f>(texture.getSize()));
        bounds.setPosition(position);
        bounds.setFillColor(Constants::texture_selector_bg_color);
        bounds.setOutlineColor(Constants::texture_selector_outline_color);
        bounds.setOutlineThickness(Constants::texture_selector_outline_thick);

        selector.setPosition(position);
        selector.setSize({grid_size, grid_size});
        selector.setOutlineColor(Constants::texture_selector_select_color);
        selector.setOutlineThickness(Constants::texture_selector_outline_thick);
        selector.setFillColor(sf::Color::Transparent);

        sheet.setTexture(texture);
        sheet.setPosition(position);
    }
    
    void TextureSelector::update(sf::Vector2i mouse_global_pos) {
        is_active = false;
        
        if (!is_shown)
            return;

        if (bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_global_pos)))
            is_active = true;

        if (!is_active)
            return;
        
        gridded_mouse_pos = static_cast<sf::Vector2u>(
            (static_cast<sf::Vector2f>(mouse_global_pos) - bounds.getPosition()) / grid_size
        );

        selector.setPosition(static_cast<sf::Vector2f>(gridded_mouse_pos) * grid_size + bounds.getPosition());
        
        auto global_bounds = bounds.getGlobalBounds();
        auto selector_pos = selector.getPosition();
        auto selector_size = selector.getSize();

        if (selector_pos.x + selector_size.x >= global_bounds.left + global_bounds.width)
            selector.setPosition(selector_pos.x - grid_size, selector_pos.y);

        if (selector_pos.y + selector_size.y > global_bounds.top + global_bounds.height)
            selector.setPosition(selector_pos.x, selector_pos.y - grid_size);
                    
        texture_rect.left = static_cast<int>(selector.getPosition().x - bounds.getPosition().x);
        texture_rect.top  = static_cast<int>(selector.getPosition().y - bounds.getPosition().y);
    }

    void TextureSelector::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        
        if (!is_shown)
            return;

        target.draw(bounds);
        target.draw(sheet);
        
        if (is_active)
            target.draw(selector); 
    }
    
    const bool TextureSelector::active() const {
        return is_active;
    }

    const sf::IntRect& TextureSelector::get_texture_rect() const {
        return texture_rect;
    }

    void TextureSelector::change_shown() {
        is_shown = !is_shown;
    }

}