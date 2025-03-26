#include "button.h"

bool Button::isPressed(const sf::Vector2i& mousePos)
{
    sf::FloatRect bounds = sprite->getGlobalBounds();
    return bounds.contains(static_cast<sf::Vector2f>(mousePos));
}

void Button::setTexture(const sf::Texture &texture) {
    sprite->setTexture(texture);
}

void Button::setTextureFile(std::string filePath) {
    if (!texture.loadFromFile(filePath)) {
        std::cerr << "Failed to load texture from file: " << filePath << std::endl;
        throw std::runtime_error("Failed to load texture from file: " + filePath);
    }
    setTexture(texture);
}

void Button::setPosition(const sf::Vector2f &pos) {
    sprite->setPosition({scale*pos.x, scale*pos.y});
}