#ifndef HERO_H
#define HERO_H

#include "character.h"
#include <optional>
#include "Inventory.h"
#include "Enemy.h"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

class Hero: public character {
    sf::Clock gameplay_time;
    sf::Time playtime = sf::Time::Zero;

    int extraSlot = 0;
    Inventory heroInv;

    std::string save;

    bool prologue = false;
    bool firstcity = false;
    bool firstchurch = false;
    bool firstblacksmith = false;
    bool firsttavern = false;
    bool firstmap = false;

    int healthpotion = 0;
    int manapotion = 0;
    int manapotionT = 0;
    int regenpotion = 0;
    int regenpotionT = 0;
    int actionPot = 0;
    bool fastaction = false;

    int potionCD = 0;

    std::optional<Item> helmetslot = std::nullopt;
    std::optional<Item> chestplateslot = std::nullopt;
    std::optional<Item> glovesslot = std::nullopt;
    std::optional<Item> leggingsslot = std::nullopt;
    std::optional<Item> bootsslot = std::nullopt;
    std::optional<Item> ringslot = std::nullopt;
    std::optional<Item> necklaceslot = std::nullopt;
    std::optional<Item> weaponslot = std::nullopt;

    int current_gold = 10;
    int currentmana;
    int exp = 0;

    public:
        Hero (const std::string& name, const Stats& stat, const StatsIncrese& incstats, int extra = 0) : character(name, stat, incstats), currentmana(stat.mana), extraSlot(extra) {
            for (int i = 0; i < extra; i++) {
                heroInv.addSlot();
            }
        }

        int getCurrentMana () const;
        void setCurrentMana (int mana);
        void incCurrentMana (int inc);

        std::string getClass () const override;

        void setSave (const std::string fileName);
        const std::string getSave ();

        void startClock ();
        void restartClock ();
        sf::Time getPlaytime ();
        void setPlaytime (sf::Time time);

        int get1stAvaiableIndex () const;
        int getAvaiableAmount () const;
        bool isAvailable (const int slot) const;

        void swapItems (size_t i, size_t x);

        int getInvSize () const;

        Item getItemFromEqp (itemType type) const;
        Item getItemFromInventory (int slot) const;

        void removeFromEqp (const itemType type);
        void removeFromInv (const int slot);
        void addToInv (const Item& item, const int slot);

        void equipItem (const Item& item);
        void equipFromInv (const int& slot);
        bool checkIfEqp (itemType type) const;
        void unequip (const itemType type, int slot = -1);

        int getExtraSlot () const;
        void setExtraSlot (int extra);

        void updateStats (itemStats stats, bool equip);

        void setHPpot (int x);
        int getHPpot () const;

        void setManapot (int x);
        int getManapot () const;

        void setHPRegpot (int x);
        int getHPRegpot () const;

        void setManapotT (int x);
        int getManapotT () const;

        void setHPRegpotT (int x);
        int getHPRegpotT () const;

        void setActionpot (int x);
        int getActionpot () const;
        void setFastAction (bool isFastAction);
        bool getFastAction () const;

        void setPotionCD ();
        int getPotionCD () const;

        void regen ();
        void instaHP ();
        void manaregen ();
        void potionmanaregen ();

        void lvlup ();
        int getDamaged (Enemy*& enemy, Hero*& hero, const DamageType& type) override;

        void goldInc (int gold);
        void setCurrentGold (int gold);
        int getCurrentGold () const;
        void expInc (int experience);
        void setExp (int experience);
        int getCurrentExp () const;

        void prologueSet (bool isPrologue);
        bool prologueState () const;
        void citySet (bool isPrologue);
        bool cityState () const;
        void blacksmithSet (bool isPrologue);
        bool blacksmithState () const;
        void churchSet (bool isPrologue);
        bool churchState () const;
        void tavernSet (bool isPrologue);
        bool tavernState () const;
        void mapSet (bool isPrologue);
        bool mapState () const;

        void pray ();

        void save_to_file ();
        bool load_from_file (const std::string filename, Hero*& hero);
};


#endif //HERO_H
