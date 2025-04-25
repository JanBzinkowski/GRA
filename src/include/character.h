#include <iostream>
#include <math.h>
#include <string>
#include <time.h>
#include <cstdlib>
#include "dmgtype.h"
#include <map>
#include <fstream>
#include <optional>
#include "Inventory.h"

#pragma once
#include "stats.h"

class AllTimeGUI;

class character {
    private:
        std::map<DamageType, float> resistance;
        std::string name;
        stats stat;
        statsincrese incstats;
        int extraSlot = 0;
        Inventory heroInv;

        std::string save;

        int expworth = 0;
        int goldworth = 0;
        int currentLocation;
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

    public:
        virtual character* clone () const = 0;
        int currenthp;
        int currentgold = 10;
        int currentmana;
        int exp = 0;
        int atktypenb = '0';

        void setSave (const std::string fileName);
        const std::string getSave ();

        character (const std::string& name, const stats& stat, const statsincrese& incstats,
                   int extra = 0) : name(name), stat(stat), incstats(incstats), currenthp(stat.basehp),
                                    currentmana(stat.mana), extraSlot(extra) {
            resistance[DamageType::MagicEnergy] = 1.0f;
            resistance[DamageType::MagicFire] = 1.0f;
            resistance[DamageType::MagicIce] = 1.0f;
            resistance[DamageType::MagicEarth] = 1.0f;
            resistance[DamageType::MagicWater] = 1.0f;
            resistance[DamageType::MagicPoison] = 1.0f;
            resistance[DamageType::MagicAir] = 1.0f;
            resistance[DamageType::Physical] = 1.0f;
            resistance[DamageType::Enviroment] = 1.0f;
            for (int i = 0; i < extra; i++) {
                heroInv.addSlot();
            }
        }

        void updateStats (itemStats stats, bool equip);
        int getInvSize () const;
        int get1stAvaiableIndex () const;
        bool isAvailable (const int slot) const;
        void swapItems (size_t i, size_t x);
        void displayEqp () const;
        bool checkIfEqp (itemType type) const;
        Item getItemFromEqp (itemType type) const;
        void addToInv (const Item& item, const int slot);
        void removeFromInv (const int slot);
        void equipItem (const Item& item);
        void equipFromInv (const int& slot);
        void unequip (const itemType type, int slot = -1);
        void removeFromEqp (const itemType type);
        Item getItemFromInventory (int slot) const;

        virtual std::string getClass () const = 0;
        void setResist (const DamageType& type, float resist);
        float getResistance (const DamageType& type) const;

        int getMaxHP () const;
        int getLvl () const;
        int getAd () const;
        int getDef () const;
        int getMaxMana () const;
        int getSpeed () const;
        std::string getName () const;
        std::string getPath () const;

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

        int getMaxHPinc () const;
        int getAdInc () const;
        int getDefInc () const;
        int getMaxManaInc () const;
        int getSpeedInc () const;

        float getAtkChance (character*& atk, character& def) const;
        float getMultDmg () const;

        void getDamaged (character*& atk, const DamageType& type);
        void regen ();
        void potionregen ();
        void instaHP ();
        void manaregen ();
        void potionmanaregen ();

        void goldInc (int gold);
        void expInc (int experience);

        void printstatcurrent ();

        void lvlup ();
        void enemyLvlUp ();

        void hpcheck ();

        void setExpworth (int worth);
        void setGoldworth (int worth);
        int getExpworth () const;
        int getGoldworth () const;

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

        void save_to_file (character*& hero);
        bool load_from_file (const std::string filename, character*& hero);
        int getExtraSlot () const;
        void setExtraSlot (int extra);


        friend class AllTimeGUI;
        virtual ~character () = default;
};

