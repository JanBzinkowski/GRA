#include <conio.h>
#include <optional>
#include <SFML/Graphics.hpp>
#include "include/game.h"
#include "options.h"



int main() {
    Options option;
    sf::Vector2u windowsize;
    if (option.getResolution()==Resolution::p1080) {
        windowsize = {1920, 1080};
        scale = 3.0f;
    }
    else if (option.getResolution()==Resolution::p1440) {
        windowsize = {2560, 1440};
        scale = 4.0f;
    }
    else {
        windowsize = {640, 360};
        scale = 1.0f;
    }
    sf::RenderWindow* window;
    if (option.getMode()==Mode::fullscreen)
        window = new sf::RenderWindow(sf::VideoMode(windowsize), "Gra 1.0", sf::Style::None, sf::State::Fullscreen);
    else if (option.getMode()==Mode::windowed)
        window = new sf::RenderWindow(sf::VideoMode(windowsize), "Gra 1.0", sf::Style::Default, sf::State::Windowed);
    else
        window = new sf::RenderWindow(sf::VideoMode(windowsize), "Gra 1.0", sf::Style::None, sf::State::Windowed);
    if (option.getFPS()==FPS::_144)
        window->setFramerateLimit(144);
    else if (option.getFPS()==FPS::_30)
        window->setFramerateLimit(30);
    else
        window->setFramerateLimit(60);
    std::random_device rd;
    std::mt19937 gen(rd());
    gen.seed(static_cast<unsigned int>(std::time(NULL)));
    srand(time(NULL));
    postac *hero = nullptr;
    game game(hero, gen, option);
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
            else if (game.getLocation() == Location::OptionsG) {
                game.optionsG(window);
            }
            else if (game.getLocation() == Location::OptionsGraph) {
                game.optionsGraph(window);
            }
            else if (game.getLocation() == Location::OptionsS) {
                game.optionsS(window);
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
