#include <iostream>
#include "Enemy.h"
#pragma once

class enemyMage: public Enemy {
    private:
        std::map<DamageType, float> resistance;

    public:
        enemyMage (const std::string& name, const Stats& enemystats) : Enemy(name, enemystats, {3, 6, 2, 4, 1}) {
            setResist(DamageType::Physical, 1.30f);
            setResist(DamageType::MagicAir, 0.65f);
            setResist(DamageType::MagicEarth, 0.65f);
            setResist(DamageType::MagicEnergy, 0.65f);
            setResist(DamageType::MagicFire, 0.6f);
            setResist(DamageType::MagicWater, 0.65f);
            setResist(DamageType::MagicPoison, 0.65f);
            setResist(DamageType::MagicIce, 0.65f);
        }

        std::string getClass () const override {
            return "enemyMage";
        }
};


