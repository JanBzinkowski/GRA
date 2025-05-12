#include "damage.h"
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <conio.h>
#include <string>

int dmgcalc::damageCalculator (int ad, int lvl, float mult, float reduct, float resistancemult, int lvl_diff){
    return static_cast<int>(1.5 * ad * lvl * mult * (1.f - reduct) * resistancemult) * (1 + 0.1 * lvl_diff);
}
