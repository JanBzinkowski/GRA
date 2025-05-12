#pragma once

#include <string>
#include "dmgtype.h"
#include <map>
#include "stats.h"

class Enemy;

class Hero;

class character {
    std::map<DamageType, float> m_resistance;
    std::string m_name;
    Stats m_stats;
    StatsIncrese m_stats_inc;

    int m_current_HP;

    int m_atk_type_nb = 0;

    public:
        character (const std::string& name, const Stats& stats, const StatsIncrese& inc_stats) : m_name(name), m_stats(stats), m_stats_inc(inc_stats), m_current_HP(stats.base_hp) {
            m_resistance[DamageType::MagicEnergy] = 1.0f;
            m_resistance[DamageType::MagicFire] = 1.0f;
            m_resistance[DamageType::MagicIce] = 1.0f;
            m_resistance[DamageType::MagicEarth] = 1.0f;
            m_resistance[DamageType::MagicWater] = 1.0f;
            m_resistance[DamageType::MagicPoison] = 1.0f;
            m_resistance[DamageType::MagicAir] = 1.0f;
            m_resistance[DamageType::Physical] = 1.0f;
            m_resistance[DamageType::Enviroment] = 1.0f;
        }

        // virtual float getAtkChance (Enemy*& enemy, Hero*& hero) const = 0;
        virtual float getMultDmg () const;
        // virtual int getDamaged (Enemy*& enemy, Hero*& hero, const DamageType& type) = 0;

        int getCurrentHP () const;
        void setCurrentHP (const int current_HP);
        void incCurrentHP (const int current_HP_inc);

        virtual std::string getClass () const = 0;

        void setResist (const DamageType& type, float resist);
        float getResistance (const DamageType& type) const;

        Stats getStats () const;
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

        void setAtkTypeNB (int nb);
        int getAtkTypeNB () const;

        virtual ~character () = default;
};

