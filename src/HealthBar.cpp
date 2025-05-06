#include "HealthBar.h"
#include "global.h"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

HealthBar::HealthBar (float x, float y, character* hero): person(hero) {
    if (!texture.loadFromFile("src\\textures\\GUI\\Enemy\\health_bar.png")) {
        std::cerr << "Failed to load texture from file: src\\textures\\GUI\\Enemy\\health_bar.png" << std::endl;
        throw std::runtime_error("Failed to load texture from file: src\\textures\\GUI\\Enemy\\health_bar.png");
    }
    sprite = std::make_unique<sf::Sprite>(texture);
    sprite->setScale({scale, scale});
    sprite->setPosition({x * scale, y * scale});
    sf::Vector2f barSize = {53.f * scale, 8.f * scale};

    white.setSize(barSize);
    white.setFillColor(sf::Color::White);
    white.setPosition({(x + 1) * scale, (y + 1) * scale});

    red.setSize({barSize.x, barSize.y});
    red.setFillColor(sf::Color::Red);
    red.setPosition({(x + 1) * scale, (y + 1) * scale});
}

void HealthBar::updateRed () {
    float hpRatio = static_cast<float>(person->getCurrentHP()) / person->getMaxHP();
    red.setSize({53.f * scale * hpRatio, 8.f * scale});
}

void HealthBar::draw (sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(white, states);
    target.draw(red, states);
    target.draw(*sprite, states);
}
