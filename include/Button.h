#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>
#include <memory>
#include "global.h"


class Button: public sf::Drawable {
    float m_scale = 1.f;
    std::unique_ptr<sf::Texture> m_texture;
    std::unique_ptr<sf::Sprite> m_sprite;

    protected:
        void draw (sf::RenderTarget& target, sf::RenderStates states) const override;

    public:
        Button (float x, float y, sf::RenderWindow*& window, const std::string& file_path);

        bool isPressed (const sf::Vector2i& mouse_position);
        void setNewTexture (const sf::Texture& new_texture);
        void setNewTexturePath (const std::string& new_file_path);
        void setPosition (const sf::Vector2f& new_position);
        sf::Vector2f getPosition ();
};

#endif
