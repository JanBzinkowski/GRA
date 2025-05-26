#ifndef HERO_H
#define HERO_H

#include "character.h"
#include <optional>
#include "Inventory.h"
#include "Enemy.h"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

class Hero: public Character {
    sf::Clock m_gameplay_time;
    sf::Time m_playtime = sf::Time::Zero;

    int m_extraSlot = 0;
    Inventory m_inventory;

    std::string m_save_path;

    bool m_prologue_state = false;
    bool m_first_time_city = false;
    bool m_first_time_church = false;
    bool m_first_time_blacksmith = false;
    bool m_first_time_tavern = false;
    bool m_first_time_map = false;

    int m_health_potion_amount = 0;
    int m_mana_potion_amount = 0;
    int m_mana_potion_time = 0;
    int m_regen_potion_amount = 0;
    int m_regen_potion_time = 0;
    int m_action_potion_amount = 0;
    bool m_fast_action = false;

    int m_potion_cooldown = 0;

    std::optional<Item> m_helmet_slot = std::nullopt;
    std::optional<Item> m_chestplate_slot = std::nullopt;
    std::optional<Item> m_gloves_slot = std::nullopt;
    std::optional<Item> m_leggings_slot = std::nullopt;
    std::optional<Item> m_boots_slot = std::nullopt;
    std::optional<Item> m_ring_slot = std::nullopt;
    std::optional<Item> m_necklace_slot = std::nullopt;
    std::optional<Item> m_weapon_slot = std::nullopt;

    int m_current_gold = 10;
    int m_current_mana;
    int exp = 0;

    public:
        Hero (const std::string& name, const Stats& stat, const StatsIncrese& incstats, int extra = 0) : Character(name, stat, incstats), m_current_mana(stat.mana), m_extraSlot(extra) {
            for (int i = 0; i < extra; i++) {
                m_inventory.addSlot();
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
        void manaRegen ();
        void manaRegenPotion ();

        bool lvlup ();
        int getDamaged (Enemy*& enemy, const DamageType& type);
        float getAtkChance (Enemy*& enemy) const;
        float reduct(Enemy*& enemy) const;

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
