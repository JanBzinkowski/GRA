#include "postac.h"
#pragma once

class Mage: public postac
{
private:
    std::map <DamageType, float> resistance;

public:
    Mage(const std::string& name, const stats& stat)
        : postac(name, stat, {3, 6, 2, 4, 1})
        {
            setResist(DamageType::Physical, 1.30f);
            setResist(DamageType::MagicAir, 0.65f);
            setResist(DamageType::MagicEarth, 0.65f);
            setResist(DamageType::MagicEnergy, 0.65f);
            setResist(DamageType::MagicFire, 0.6f);
            setResist(DamageType::MagicWater, 0.65f);
            setResist(DamageType::MagicPoison, 0.65f);
            setResist(DamageType::MagicIce, 0.65f);
        }
    std::string getClass() const
    {
        return "Mage";
    }
    Mage* clone() const override {
        return new Mage(*this);
    }
};

