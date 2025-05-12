#include <iostream>
#include "Enemy.h"
#pragma once

class EnemyWarrior: public Enemy {
    public:
        EnemyWarrior (const std::string& name, const Stats& enemy_stats) : Enemy(name, enemy_stats, {5, 2, 4, 3, 1}) {
            setWeaknessMult(DamageType::Physical, 0.85f);
            setWeaknessMult(DamageType::MagicAir, 0.75f);
            setWeaknessMult(DamageType::MagicEarth, 1.2f);
            setWeaknessMult(DamageType::MagicEnergy, 1.2f);
            setWeaknessMult(DamageType::MagicFire, 1.2f);
            setWeaknessMult(DamageType::MagicWater, 1.2f);
            setWeaknessMult(DamageType::MagicPoison, 1.2f);
            setWeaknessMult(DamageType::MagicIce, 1.2f);
            setWeaknessMult(DamageType::Environment, 1.2f);
        }

        std::string getClass() const override {
            return "EnemyWarrior";
        }
};

