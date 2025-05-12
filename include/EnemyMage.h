#pragma once

#include <iostream>
#include "Enemy.h"

class EnemyMage: public Enemy {
    public:
        EnemyMage (const std::string& name, const Stats& enemy_stats) : Enemy(name, enemy_stats, {3, 6, 2, 4, 1}) {
            setWeaknessMult(DamageType::Physical, 1.30f);
            setWeaknessMult(DamageType::MagicAir, 0.65f);
            setWeaknessMult(DamageType::MagicEarth, 0.65f);
            setWeaknessMult(DamageType::MagicEnergy, 0.65f);
            setWeaknessMult(DamageType::MagicFire, 0.6f);
            setWeaknessMult(DamageType::MagicWater, 0.65f);
            setWeaknessMult(DamageType::MagicPoison, 0.65f);
            setWeaknessMult(DamageType::MagicIce, 0.65f);
        }

        std::string getClass () const override {
            return "EnemyMage";
        }
};


