#ifndef SLIDER_H
#define SLIDER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "global.h"

class Slider: public sf::Drawable {
private:
  sf::Texture background;
  sf::Texture slider;
  std::unique_ptr<sf::Sprite> backgroundSprite;
  std::unique_ptr<sf::Sprite> sliderSprite;
protected:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
    target.draw(*backgroundSprite, states);
    target.draw(*sliderSprite, states);
  }
public:
  Slider(float x, float y) {
    if (!background.loadFromFile("src\\textures\\background\\Options\\slider1.png")) {
      std::cerr << "Failed to load texture from file: " << "src\\textures\\background\\Options\\slider1.png" << std::endl;
      throw std::runtime_error("Failed to load texture from file: src\\textures\\background\\Options\\slider1.png");
    }

    backgroundSprite = std::make_unique<sf::Sprite>(background);
    backgroundSprite->setPosition({scale*x, scale*y});
    backgroundSprite->scale({scale, scale});
    if (!slider.loadFromFile("src\\textures\\background\\Options\\slider2.png")) {
      std::cerr << "Failed to load texture from file: " << "src\\textures\\background\\Options\\slider2.png" << std::endl;
      throw std::runtime_error("Failed to load texture from file: src\\textures\\background\\Options\\slider2.png");
    }

    sliderSprite = std::make_unique<sf::Sprite>(slider);
    sliderSprite->setPosition({scale*(x+7), scale*(y+8)});
    sliderSprite->scale({scale, scale});
  }
  void slide(const sf::Vector2i &mousePos, int& value, int min, int max);
  void setPosition(const sf::Vector2f &pos);
  bool isPressed(const sf::Vector2i& mousePos);
  void setSlider(int percent);
};

#endif //SLIDER_H
