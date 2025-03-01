#include "POSTAC.h"
#pragma once

class Archer: public postac
{
private:
    std::map <DamageType, float> resistance;

public:
    Archer(const std::string& name, const stats& stat)
        : postac(name, stat, {3, 6, 3, 2, 2})
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
    std::string getClass() const
    {
        return "Archer";
    }
};


