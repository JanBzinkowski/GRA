#include <conio.h>
#include <optional>
#include <SFML/Graphics.hpp>
#include "include/game.h"
#include "button.h"


#define SCALE 3
int main() {
    sf::Vector2u windowsize(1920, 1080);
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(windowsize), "Gra 1.0");
    std::random_device rd;
    std::mt19937 gen(rd());
    gen.seed(static_cast<unsigned int>(std::time(NULL)));
    srand(time(NULL));
    postac *hero = nullptr;
    game game(hero, gen);

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event -> is<sf::Event::Closed>())
                window->close();
        }
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            if (game.getLocation() == Location::MainMenu) {
                game.mainMenu(hero, window);
            }
            else if (game.getLocation() == Location::Saves) {
                game.saves(hero, window);
            }
            else if (game.getLocation() == Location::Map) {
                game.worldMap(hero);
            }
            else if (game.getLocation() == Location::City) {
                game.city(hero);
            }
            else if (game.getLocation() == Location::Church) {
                game.church(hero);
            }
            else if (game.getLocation() == Location::Quit) {
                window->close();
            }
        }
    }
    delete window;
    delete hero;
    return 0;
}
