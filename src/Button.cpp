#include <Hero.h>

#include "button.h"

bool Button::isPressed (const sf::Vector2i& mouse_position) {
    sf::FloatRect bounds = m_sprite->getGlobalBounds();
    return bounds.contains(static_cast<sf::Vector2f>(mouse_position));
}

void Button::setNewTexture (const sf::Texture& new_texture) {
    m_sprite->setTexture(new_texture);
}

void Button::setNewTexturePath (const std::string& new_file_path) {
    if (!m_texture->loadFromFile(new_file_path)) {
        std::cerr << "Failed to load texture from file: " << new_file_path << std::endl;
        throw std::runtime_error("Failed to load texture from file: " + new_file_path);
    }
    setNewTexture(*m_texture);
}

void Button::setPosition (const sf::Vector2f& new_position) {
    m_sprite->setPosition({scale * new_position.x, scale * new_position.y});
}

sf::Vector2f Button::getPosition () {
    return m_sprite->getPosition();
}

Button::Button (float x, float y, const std::string& file_path) {
    m_texture = std::make_unique<sf::Texture>();
    if (!m_texture->loadFromFile(file_path)) {
        std::cerr << "Failed to load texture from file: " << file_path << std::endl;
        throw std::runtime_error("Failed to load texture from file: " + file_path);
    }
    m_sprite = std::make_unique<sf::Sprite>(*m_texture);
    m_sprite->setPosition({scale * x, scale * y});
    m_sprite->scale({scale, scale});
}

void Button::draw (sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(*m_sprite, states);
}