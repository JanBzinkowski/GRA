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
        Button (float x, float y, const std::string& file_path) {
            m_texture = std::make_unique<sf::Texture>();
            if (!m_texture->loadFromFile(file_path)) {
                std::cerr << "Failed to load texture from file: " << file_path << std::endl;
                throw std::runtime_error("Failed to load texture from file: " + file_path);
            }
            m_sprite = std::make_unique<sf::Sprite>(*m_texture);
            m_sprite->setPosition({scale * x, scale * y});
            m_sprite->scale({scale, scale});
        }

        bool isPressed (const sf::Vector2i& mouse_position);
        void setNewTexture (const sf::Texture& new_texture);
        void setNewTexturePath (const std::string& new_file_path);
        void setPosition (const sf::Vector2f& new_position);
        sf::Vector2f getPosition ();
};

#endif
