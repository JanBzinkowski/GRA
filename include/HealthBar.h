#ifndef HEALTBAR_H
#define HEALTBAR_H
#include <character.h>
#include <SFML/Graphics/Drawable.hpp>
#include <memory>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>


class HealthBar: public sf::Drawable {
    protected:
        void draw (sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        float m_scale = 1.f;
        sf::Texture texture;
        sf::RectangleShape red;
        sf::RectangleShape white;
        std::unique_ptr<sf::Sprite> sprite;
        Character* person;

    public:
        HealthBar (float x, float y, sf::RenderWindow*& window, Character* hero);
        void updateRed ();
};


#endif //HEALTBAR_H
