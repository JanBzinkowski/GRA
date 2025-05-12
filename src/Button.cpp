#include "button.h"

bool Button::isPressed (const sf::Vector2i& mousePos) {
    sf::FloatRect bounds = m_sprite->getGlobalBounds();
    return bounds.contains(static_cast<sf::Vector2f>(mousePos));
}

void Button::setTexture (const sf::Texture& texture) {
    m_sprite->setTexture(texture);
}

void Button::setTextureFile (const std::string& filePath) {
    if (!m_texture->loadFromFile(filePath)) {
        std::cerr << "Failed to load texture from file: " << filePath << std::endl;
        throw std::runtime_error("Failed to load texture from file: " + filePath);
    }
    setTexture(*m_texture);
}

void Button::setPosition (const sf::Vector2f& pos) {
    m_sprite->setPosition({scale * pos.x, scale * pos.y});
}

sf::Vector2f Button::getPosition () {
    return m_sprite->getPosition();
}
