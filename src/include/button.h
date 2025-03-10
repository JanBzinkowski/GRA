/*#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Button
{
private:
    sf::Sprite sprite;
    sf::Texture texture;

public:
    Button(float x, float y, const std::string &filePath);
    {
        if (!texture.loadFromFile(filePath))
        {
          throw std::runtime_error("Failed to load texture from file: ") + filePath;
        }
        sprite.setTexture(texture);
        sprite.setPosition(x, y);
    }

    void draw(sf::RenderWindow &window);
    bool isPressed(sf::Vector2f mousePos);
};
#endif
*/