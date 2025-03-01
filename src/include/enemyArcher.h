#include <iostream>
#include "POSTAC.h"
#pragma once

class enemyArcher: public postac
{
private:
    std::map <DamageType, float> resistance;

public:
    enemyArcher(const std::string& name, const stats& enemystats)
        : postac(name, enemystats, {3, 6, 3, 2, 2})
        {
            setResist(DamageType::Physical, 1.25f);
            setResist(DamageType::MagicAir, 1.05f);
            setResist(DamageType::MagicEarth, 1.05f);
            setResist(DamageType::MagicEnergy, 1.05f);
            setResist(DamageType::MagicFire, 1.05f);
            setResist(DamageType::MagicWater, 1.05f);
            setResist(DamageType::MagicPoison, 1.05f);
            setResist(DamageType::MagicIce, 1.05f);
            setResist(DamageType::Enviroment, 1.35f);
        }

    std::string getClass() const override
    {
        return "enemyArcher";
    }
};
