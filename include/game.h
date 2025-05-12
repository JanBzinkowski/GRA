#include "character.h"
#include <cstdlib>
#include <typeinfo>
#include "Warrior.h"
#include "Mage.h"
#include "Archer.h"
#include <conio.h>
#include "enemyArcher.h"
#include "enemyWarrior.h"
#include "enemyMage.h"
#include "location.h"
#include <unordered_map>
#include "gametime.h"
#include "EnemyMap.h"
#include <random>
#include <SFML/Graphics.hpp>
#include "HUD.h"
#include "options.h"

class game {
    private:
        Hero* hero;
        Options option;
        std::mt19937 gen;
        GameTime time;
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
        game (Hero*& hero, std::mt19937& gen, Options& opt) : hero(hero), gen(gen), option(opt) {
            if (!font.openFromFile("..\\src\\fonts\\pixel-8x8.ttf")) {
                std::cerr << "Failed to load font from file: " << "..\\src\\fonts\\pixel-8x8.ttf" << std::endl;
                throw std::runtime_error("Failed to load font from file: ..\\src\\fonts\\pixel-8x8.ttf");
            }
        }

        Enemy* createEnemy (const enemyStats& stats);

        bool areShopsOpen () const;

        void setLocation (Location newLocation);
        Location getLocation () const;

        void unlockLocations (Location locationToUnlock);
        bool isUnlocked (Location location) const;
        std::string isUnlockedPrint (Location location) const;

        void mainMenu (sf::RenderWindow* window);
        void saves (sf::RenderWindow* window);
        void optionsG (sf::RenderWindow* window);
        bool optionsGraph (sf::RenderWindow* window);
        bool optionsS (sf::RenderWindow* window);
        void createhero (sf::RenderWindow* window);
        bool pauseMenu (sf::RenderWindow* window);

        std::string getTextSave (std::string filename);
        void saveRead (sf::RenderWindow* window, std::string filename);
        void worldMap (sf::RenderWindow* window);
        void city (sf::RenderWindow* window);

        void church (sf::RenderWindow* window);
        void tavern (sf::RenderWindow* window);

        void blacksmith (sf::RenderWindow* window);
        std::string getBlacksmithInvPath ();
        void saveBlacksmithInv ();
        void loadBlacksmithInv ();
        void inventory (sf::RenderWindow* window);

        int hoverFrameSetBlacksmith (sf::Text& hover, sf::Sprite& frame, std::vector<Button>& slots, std::vector<std::string>& texts, bool& flag, sf::RenderWindow* window);
        int hoverFrameSetInventory (sf::Text& hover, sf::Sprite& frame, std::vector<Button>& slots, std::vector<std::string>& texts, bool& flag, sf::RenderWindow* window);
        int hoverFrameSetEquipmentLoop (sf::Text& hover, sf::Sprite& frame, std::vector<std::pair<bool, Button>>& eqp, std::vector<std::string>& texts, bool& flag, sf::RenderWindow* window);
        bool hoverFrameSetEquipment (sf::Text& hover, sf::Sprite& frame, std::pair<bool, Button>& eqp, std::vector<std::string>& texts, bool& flag, sf::RenderWindow* window, int& index);
        void hoverFrameSetEquipmentSlot (sf::Text& hover, sf::Sprite& frame, std::pair<bool, Button>& eqp, std::vector<std::string>& texts, bool& flag, int index);

        int fight (Enemy*& enemy, sf::RenderWindow* window);

        int heroaction (Enemy*& enemy, Hero*& hero);
        int enemyaction (Enemy*& enemy, Hero*& hero);

        int fight3 (Enemy*& enemy1, Enemy*& enemy2, Enemy*& enemy3, sf::RenderWindow* window);
        void fightEnd (Enemy*& enemy);

        void itemRandomize (std::mt19937& gen);

        void loss ();
        bool retcity ();
        bool enemyenc (int indexmin, int indexmax, int exp, int gold, int maxlvl, sf::RenderWindow*& window, sf::Sprite background);
        bool enemyenc3 (int indexmin, int indexmax, int exp, int gold, int maxlvl, sf::RenderWindow* window, sf::Sprite background);
        void lvl0 (sf::RenderWindow* window);
        void forest (sf::RenderWindow* window);

        ~game () = default;
};
