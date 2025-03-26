#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>
#include <memory>
#include "global.h"


class Button : public sf::Drawable
{
    sf::Texture texture;
    std::unique_ptr<sf::Sprite> sprite;

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(*sprite, states);
    }
public:
    Button(float x, float y, const std::string &filePath) {
        if (!texture.loadFromFile(filePath)) {
            std::cerr << "Failed to load texture from file: " << filePath << std::endl;
            throw std::runtime_error("Failed to load texture from file: " + filePath);
        }

        sprite = std::make_unique<sf::Sprite>(texture);
        sprite->setPosition({scale*x, scale*y});
        sprite->scale({scale, scale});
    }
    bool isPressed(const sf::Vector2i& mousePos);
    void setTexture(const sf::Texture &texture);
    void setTextureFile(std::string filePath);
    void setPosition(const sf::Vector2f &pos);
};

#endif