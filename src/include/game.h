#include "POSTAC.h"
#include "damage.h"
#include <cstdlib>
#include <typeinfo>
#include "Warrior.h"
#include "Mage.h"
#include "Archer.h"
#include <conio.h>
#include "enemyWarrior.h"
#include "enemyMage.h"
#include "location.h"
#include <unordered_map>
#include "gametime.h"
#include "enemy.h"
#include <random>
#include <SFML/Graphics.hpp>
#include "AllTimeGUI.h"
#include "options.h"

class game
{
private:
    postac* hero;
    Options option;
    std::mt19937 gen;
    gameTime Time;
    Location currentLocation=Location::MainMenu;
    std::unordered_map<Location, bool> unlockedLocations =
    {
        {Location::Quit, true},
        {Location::Saves, true},
        {Location::OptionsG, true},
        {Location::OptionsGraph, true},
        {Location::OptionsS, true},
        {Location::MainMenu, true},
        {Location::Map, true},
        {Location::City, true},
        {Location::Arena, true},
        {Location::Blacksmith, true},
        {Location::WitchHut, true},
        {Location::Church, true},
        {Location::Tavern, true},
        {Location::Forest, true},
        {Location::Swamp, false},
        {Location::Caves, false},
        {Location::IcePeaks, false},
        {Location::Volcano, false},
        {Location::Graveyard, false},
        {Location::Ocean, false}
    };

    bool BlacksmithNewItems=true;
    std::vector<Item> blacksmithInv;
    void updateBlacksmith();
    sf::Font font;
public:
    game(postac*& hero, std::mt19937& gen, Options& opt)
        : hero(hero), gen(gen), option(opt) {
        if (!font.openFromFile("src\\fonts\\pixel-8x8.ttf")) {
            std::cerr <<"Failed to load font from file: " << "src\\fonts\\pixel-8x8.ttf" << std::endl;
            throw std::runtime_error("Failed to load font from file: src\\fonts\\pixel-8x8.ttf");
        }
    }

    postac* createEnemy(const enemyStats& stats);

    bool areShopsOpen() const;

    void setLocation(Location newLocation);
    Location getLocation() const;

    void unlockLocations(Location locationToUnlock);
    bool isUnlocked(Location location) const;
    std::string isUnlockedPrint(Location location) const;

    void mainMenu(postac*& hero, sf::RenderWindow* window);
    void saves(postac*& hero, sf::RenderWindow* window);
    void optionsG(sf::RenderWindow* window);
    void optionsGraph(sf::RenderWindow* window);
    void optionsS(sf::RenderWindow* window);
    void createhero(postac*& hero, sf::RenderWindow* window);
    void saveRead(postac*& hero, sf::RenderWindow* window, std::string filename);
    void worldMap(postac*& hero);
    void city(postac*& hero);

    void church(postac*& hero);
    void tavern(postac*& hero);
    void blacksmith(postac*& hero);

    int fight(postac*& hero, postac*& enemy);

    void heroaction(postac*& enemy, postac*& hero);
    void enemyaction(postac*& enemy, postac*& hero);

    int fight3(postac*& hero, postac*& enemy1, postac*& enemy2, postac*& enemy3);
    void fightEnd(postac*& hero, postac*& enemy);

    void potionMenu(postac*& hero);

    void itemRandomize(postac*& hero, std::mt19937& gen);
    void itemBuy(postac*& hero);
    void inventoryMenagment(postac*& hero);

    void loss(postac*& hero);
    bool retcity();
    bool enemyenc(int indexmin, int indexmax, int exp, int gold, int maxlvl, postac*& hero);
    bool enemyenc3(int indexmin, int indexmax, int exp, int gold, int maxlvl, postac*& hero);
    void lvl0(postac*& hero);
    void forest(postac*& hero);

    ~game()=default;
};
