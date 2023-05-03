#include "GUIElements/TextureSelector.hpp"
#include "Constants.hpp"
#include <iostream>

namespace gui {
    TextureSelector::TextureSelector(const sf::Vector2f position, const sf::Vector2f size, 
                                     const sf::Texture &texture) {
        bounds.setSize(size);
        bounds.setPosition(position);
        bounds.setFillColor(game::Constants::texture_selector_bg_color);
        bounds.setOutlineColor(game::Constants::texture_selector_outline_color);
        bounds.setOutlineThickness(1);

        sheet.setTexture(texture);
        sheet.setPosition(position);

        if (sheet.getGlobalBounds().width >= bounds.getGlobalBounds().width) {
            // we need to substract outline thickness multiplied by 2
            // 'cuz texture displayed after left outline
            // and should not be over after right ouline
    
            auto bounds_width = bounds.getGlobalBounds().width - 2 * bounds.getOutlineThickness();
            auto sheet_height = sheet.getGlobalBounds().height;

            sheet.setTextureRect(sf::IntRect(0, 0, bounds_width, sheet_height));
        }

        if (sheet.getGlobalBounds().height >= bounds.getGlobalBounds().height) {
            auto bounds_height = bounds.getGlobalBounds().height - 2 * bounds.getOutlineThickness();
            auto sheet_width   = sheet.getGlobalBounds().width;

            sheet.setTextureRect(sf::IntRect(0, 0, sheet_width, bounds_height));
        }

    }
    
    void TextureSelector::update(sf::Vector2f mouse_pos) {

    }

    void TextureSelector::draw(sf::RenderTarget &target, sf::RenderStates states) const {

        target.draw(bounds);
        target.draw(sheet);

    }
        

}