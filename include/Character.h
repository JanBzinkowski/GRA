#pragma once

#include <string>
#include "DamageType.h"
#include <map>
#include "stats.h"

class Enemy;

class Hero;

class Character {
    std::map<DamageType, float> m_weakness_multiplayer;
    std::string m_name;
    Stats m_stats;
    StatsIncrese m_stats_inc;

    int m_current_HP;

    int m_atk_type_nb = 0;

    public:
        Character (const std::string& name, const Stats& stats, const StatsIncrese& inc_stats) : m_name(name), m_stats(stats), m_stats_inc(inc_stats), m_current_HP(stats.base_hp) {
            m_weakness_multiplayer[DamageType::MagicEnergy] = 1.0f;
            m_weakness_multiplayer[DamageType::MagicFire] = 1.0f;
            m_weakness_multiplayer[DamageType::MagicIce] = 1.0f;
            m_weakness_multiplayer[DamageType::MagicEarth] = 1.0f;
            m_weakness_multiplayer[DamageType::MagicWater] = 1.0f;
            m_weakness_multiplayer[DamageType::MagicPoison] = 1.0f;
            m_weakness_multiplayer[DamageType::MagicAir] = 1.0f;
            m_weakness_multiplayer[DamageType::Physical] = 1.0f;
            m_weakness_multiplayer[DamageType::Environment] = 1.0f;
        }

        // virtual float getAtkChance (Enemy*& enemy, Hero*& hero) const = 0;
        virtual float getMultDmg () const;
        // virtual int getDamaged (Enemy*& enemy, Hero*& hero, const DamageType& type) = 0;

        int getCurrentHP () const;
        void setCurrentHP (const int current_HP);
        void incCurrentHP (const int current_HP_inc);

        virtual std::string getClass () const = 0;

        void setWeaknessMult (const DamageType& type, float weakness_mult);
        float getWeaknessMult (const DamageType& type) const;

        Stats getStats () const;
        void setStats(const Stats& stats);
        StatsIncrese getStatsInc () const;

        int getMaxHP () const;
        int getLvl () const;
        int getAd () const;
        int getDef () const;
        int getMaxMana () const;
        int getSpeed () const;
        std::string getName () const;
        std::string getPath () const;

        int getMaxHPInc () const;
        int getAdInc () const;
        int getDefInc () const;
        int getMaxManaInc () const;
        int getSpeedInc () const;

        void setAtkTypeNB (int attack_number);
        int getAtkTypeNB () const;

        virtual ~Character () = default;
};

