#include "Hero.h"
#include "Enemy.h"
#pragma once

class dmgcalc {
    public:
        static float reduction (Enemy*& enemy, Hero*& hero, bool isHero);

        static int damage (Enemy*& enemy, Hero*& hero, const DamageType& type, const bool toHero);
};

