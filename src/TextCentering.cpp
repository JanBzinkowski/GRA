#include "TextCentering.h"

void TextCentering::textCentering(std::vector<std::unique_ptr<sf::Text>>& texts, std::string full_text, sf::Font& font, int char_size, sf::Vector2f starting_pos) {
    std::istringstream stream(full_text);
    std::string line;

    float lineSpacing = char_size + 4.f;
    int lineIndex = 0;

    while (std::getline(stream, line)) {
        std::unique_ptr<sf::Text> textLine = std::make_unique<sf::Text>(font);
        textLine->setString(sf::String::fromUtf8(line.begin(), line.end()));
        textLine->setCharacterSize(char_size);

        sf::FloatRect bounds = textLine->getLocalBounds();
        textLine->setOrigin({bounds.size.x / 2.0f, 0.f});
        textLine->setPosition({starting_pos.x, starting_pos.y + lineIndex * lineSpacing});

        texts.emplace_back(std::move(textLine));
        ++lineIndex;
    }
}