#include "Hero.h"
#include "Enemy.h"
#pragma once

class dmgcalc {
    public:
        static int damageCalculator (int ad, int lvl, float mult, float reduct, float resistancemult, int lvl_diff);
};

