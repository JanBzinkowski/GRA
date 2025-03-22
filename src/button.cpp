#include "button.h"

bool Button::isPressed(const sf::Vector2i& mousePos)
{
    sf::FloatRect bounds = sprite->getGlobalBounds();
    return bounds.contains(static_cast<sf::Vector2f>(mousePos));
}

void Button::setTexture(const sf::Texture &texture) {
    sprite->setTexture(texture);
}
