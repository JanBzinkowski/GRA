#include "DamageCalculation.h"

int DMGCalculation::damageCalculator (int attack, int lvl, float mult, float reduct, float resistancemult, int lvl_diff){
    return static_cast<int>(1.5 * attack * lvl * mult * (1.f - reduct) * resistancemult) * (1 + 0.1 * lvl_diff);
}
