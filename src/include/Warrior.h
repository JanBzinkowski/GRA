#include "Hero.h"
#pragma once

class Warrior: public Hero {
    private:
        std::map<DamageType, float> resistance;

    public:
        Warrior (const std::string& name, const Stats& stat) : Hero(name, stat, {5, 2, 4, 3, 1}) {
            setResist(DamageType::Physical, 0.85f);
            setResist(DamageType::MagicAir, 0.75f);
            setResist(DamageType::MagicEarth, 1.2f);
            setResist(DamageType::MagicEnergy, 1.2f);
            setResist(DamageType::MagicFire, 1.2f);
            setResist(DamageType::MagicWater, 1.2f);
            setResist(DamageType::MagicPoison, 1.2f);
            setResist(DamageType::MagicIce, 1.2f);
            setResist(DamageType::Enviroment, 1.2f);
        }

        std::string getClass () const {
            return "Warrior";
        }
};
