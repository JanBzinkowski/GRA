#include "character.h"
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

class game {
    private:
        character* hero;
        Options option;
        std::mt19937 gen;
        gameTime Time;
        Location currentLocation = Location::MainMenu;
        std::unordered_map<Location, bool> unlockedLocations = {
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

        bool BlacksmithNewItems = true;
        std::array<Item, 6> blacksmithInv = {Item(0), Item(0), Item(0), Item(0), Item(0), Item(0)};
        std::vector<int> blacksmithAvaiable;
        void updateBlacksmith ();
        sf::Font font;

    public:
        game (character*& hero, std::mt19937& gen, Options& opt) : hero(hero), gen(gen), option(opt) {
            if (!font.openFromFile("src\\fonts\\pixel-8x8.ttf")) {
                std::cerr << "Failed to load font from file: " << "src\\fonts\\pixel-8x8.ttf" << std::endl;
                throw std::runtime_error("Failed to load font from file: src\\fonts\\pixel-8x8.ttf");
            }
        }

        character* createEnemy (const enemyStats& stats);

        bool areShopsOpen () const;

        void setLocation (Location newLocation);
        Location getLocation () const;

        void unlockLocations (Location locationToUnlock);
        bool isUnlocked (Location location) const;
        std::string isUnlockedPrint (Location location) const;

        void mainMenu (character*& hero, sf::RenderWindow* window);
        void saves (character*& hero, sf::RenderWindow* window);
        void optionsG (sf::RenderWindow* window);
        void optionsGraph (sf::RenderWindow* window);
        void optionsS (sf::RenderWindow* window);
        void createhero (character*& hero, sf::RenderWindow* window);
        void saveRead (character*& hero, sf::RenderWindow* window, std::string filename);
        void worldMap (character*& hero);
        void city (character*& hero, sf::RenderWindow* window);

        void church (character*& hero, sf::RenderWindow* window);
        void tavern (character*& hero, sf::RenderWindow* window);
        void blacksmith (character*& hero, sf::RenderWindow* window);

        int fight (character*& hero, int enemyID, sf::RenderWindow* window);

        void heroaction (character*& enemy, character*& hero);
        void enemyaction (character*& enemy, character*& hero);

        int fight3 (character*& hero, character*& enemy1, character*& enemy2, character*& enemy3);
        void fightEnd (character*& hero, character*& enemy);

        void itemRandomize (character*& hero, std::mt19937& gen);
        void itemBuy (character*& hero);
        void inventoryMenagment (character*& hero);

        void loss (character*& hero);
        bool retcity ();
        //bool enemyenc(int indexmin, int indexmax, int exp, int gold, int maxlvl, postac*& hero);
        //bool enemyenc3(int indexmin, int indexmax, int exp, int gold, int maxlvl, postac*& hero);
        void lvl0 (character*& hero, sf::RenderWindow* window);
        //void forest(postac*& hero);

        ~game () = default;
};
