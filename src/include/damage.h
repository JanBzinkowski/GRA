#include "POSTAC.h"
#pragma once

class dmgcalc
{
private:

public:

    float reduction (postac& def, postac*& atk);

    int damage(postac*& atk, postac& def, const DamageType& type);
};

