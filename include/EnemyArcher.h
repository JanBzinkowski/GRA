#pragma once
#include <iostream>
#include "Enemy.h"


class EnemyArcher: public Enemy {
    public:
        EnemyArcher (const std::string& name, const Stats& enemystats) : Enemy(name, enemystats, {3, 6, 3, 2, 2}) {
            setWeaknessMult(DamageType::Physical, 1.25f);
            setWeaknessMult(DamageType::MagicAir, 1.05f);
            setWeaknessMult(DamageType::MagicEarth, 1.05f);
            setWeaknessMult(DamageType::MagicEnergy, 1.05f);
            setWeaknessMult(DamageType::MagicFire, 1.05f);
            setWeaknessMult(DamageType::MagicWater, 1.05f);
            setWeaknessMult(DamageType::MagicPoison, 1.05f);
            setWeaknessMult(DamageType::MagicIce, 1.05f);
            setWeaknessMult(DamageType::Environment, 1.35f);
        }

        std::string getClass () const override {
            return "EnemyArcher";
        }
};
