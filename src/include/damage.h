#include "character.h"
#pragma once

class dmgcalc {
    private:

    public:
        float reduction (character& def, character*& atk);

        int damage (character*& atk, character& def, const DamageType& type);
};

