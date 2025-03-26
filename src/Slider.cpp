#include "Slider.h"

void Slider::setPosition(const sf::Vector2f &pos) {
    backgroundSprite->setPosition({scale*pos.x, scale*pos.y});
    sliderSprite->setPosition({scale*pos.x, scale*pos.y});
}

bool Slider::isPressed(const sf::Vector2i& mousePos)
{
    sf::FloatRect bounds = backgroundSprite->getGlobalBounds();
    bounds.position.x += scale*10;
    bounds.size.x -= scale*24;
    return bounds.contains(static_cast<sf::Vector2f>(mousePos));
}

void Slider::slide(const sf::Vector2i &mousePos, int& value, int min, int max) {
    sf::FloatRect bounds = backgroundSprite->getGlobalBounds();
    bounds.position.x += scale*10;
    bounds.size.x -= scale*24;
    if (isPressed(mousePos))
        sliderSprite->setPosition({float(mousePos.x-(3*scale)), sliderSprite->getPosition().y});
    value = int(-(max-min)*(backgroundSprite->getPosition().x - sliderSprite->getPosition().x - (7*scale))/bounds.size.x + min-10.8);
}

void Slider::setSlider(int percent) {
    sf::FloatRect bounds = backgroundSprite->getGlobalBounds();
    bounds.position.x += scale*10;
    bounds.size.x -= scale*24;
    sliderSprite->setPosition({static_cast<float>(percent*0.01*bounds.size.x+bounds.position.x), sliderSprite->getPosition().y});
}
