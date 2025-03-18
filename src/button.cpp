#include "button.h"

bool Button::isPressed(const sf::Vector2f& mousePos)
{
    return sprite->getGlobalBounds().contains(mousePos);
}
