#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>
#include <memory>
#include "global.h"


class Button: public sf::Drawable {
    std::unique_ptr<sf::Texture> m_texture;
    std::unique_ptr<sf::Sprite> m_sprite;

    protected:
        void draw (sf::RenderTarget& target, sf::RenderStates states) const override {
            target.draw(*m_sprite, states);
        }

    public:
        Button (float x, float y, const std::string& filePath) {
            m_texture = std::make_unique<sf::Texture>();
            if (!m_texture->loadFromFile(filePath)) {
                std::cerr << "Failed to load texture from file: " << filePath << std::endl;
                throw std::runtime_error("Failed to load texture from file: " + filePath);
            }
            m_sprite = std::make_unique<sf::Sprite>(*m_texture);
            m_sprite->setPosition({scale * x, scale * y});
            m_sprite->scale({scale, scale});
        }

        bool isPressed (const sf::Vector2i& mousePos);
        void setTexture (const sf::Texture& texture);
        void setTextureFile (const std::string& filePath);
        void setPosition (const sf::Vector2f& pos);
        sf::Vector2f getPosition ();
};

#endif
