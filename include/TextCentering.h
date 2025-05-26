#ifndef TEXTCENTERING_H
#define TEXTCENTERING_H

#include <iostream>
#include <SFML/Graphics.hpp>

class TextCentering {
    public:
      static void textCentering(std::vector<std::unique_ptr<sf::Text>>& texts, std::string full_text, sf::Font& font, int char_size, sf::Vector2f starting_pos);
};

#endif //TEXTCENTERING_H
