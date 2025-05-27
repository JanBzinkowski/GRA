#include "HealthBar.h"
#include "global.h"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

HealthBar::HealthBar (float x, float y, sf::RenderWindow*& window, Character* hero): person(hero) {
    m_scale = window->getSize().y / 360.f;
    if (!texture.loadFromFile("..\\src\\textures\\GUI\\Enemy\\health_bar.png")) {
        std::cerr << "Failed to load texture from file: ..\\src\\textures\\GUI\\Enemy\\health_bar.png" << std::endl;
        throw std::runtime_error("Failed to load texture from file: ..\\src\\textures\\GUI\\Enemy\\health_bar.png");
    }
    sprite = std::make_unique<sf::Sprite>(texture);
    sprite->setScale({m_scale, m_scale});
    sprite->setPosition({x * m_scale, y * m_scale});
    sf::Vector2f barSize = {53.f * m_scale, 8.f * m_scale};

    white.setSize(barSize);
    white.setFillColor(sf::Color::White);
    white.setPosition({(x + 1) * m_scale, (y + 1) * m_scale});

    red.setSize({barSize.x, barSize.y});
    red.setFillColor(sf::Color::Red);
    red.setPosition({(x + 1) * m_scale, (y + 1) * m_scale});
}

void HealthBar::updateRed () {
    float hpRatio = static_cast<float>(person->getCurrentHP()) / person->getMaxHP();
    red.setSize({53.f * m_scale * hpRatio, 8.f * m_scale});
}

void HealthBar::draw (sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(white, states);
    target.draw(red, states);
    target.draw(*sprite, states);
}
