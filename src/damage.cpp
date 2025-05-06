#include "include/damage.h"
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <conio.h>
#include <string>

float dmgcalc::reduction (Enemy*& enemy, Hero*& hero, bool isHero) {
    int lvldif;
    if (isHero) {
        lvldif = (hero->getLvl()) - (enemy->getLvl());
    }
    else
        lvldif = (enemy->getLvl()) - (hero->getLvl());
    if (lvldif >= 10)
        lvldif = 9;
    if (isHero) {
        float reduct = atan(hero->getDef()) / hero->getLvl() * (1 + 0.1 * lvldif);
        std::string classhero = hero->getClass();
        if (((classhero == "Warrior")) && reduct > 0.75f)
            reduct = 0.75f;
        else if (((classhero == "Archer")) && reduct > 0.55f)
            reduct = 0.55f;
        else if (((classhero == "Mage")) && reduct > 0.40f)
            reduct = 0.40f;
        return reduct;
    }
    float reduct = atan(enemy->getDef()) / enemy->getLvl() * (1 + 0.1 * lvldif);
    std::string classhero = hero->getClass();
    if (((classhero == "enemyWarrior")) && reduct > 0.75f)
        reduct = 0.75f;
    else if (((classhero == "enemyArcher")) && reduct > 0.55f)
        reduct = 0.55f;
    else if (((classhero == "enemyMage")) && reduct > 0.40f)
        reduct = 0.40f;
    return reduct;
}

int dmgcalc::damage (Enemy*& enemy, Hero*& hero, const DamageType& type, const bool toHero) {
    float randChance = static_cast<float>(std::rand()) / RAND_MAX;
    if (!toHero && randChance < hero->getAtkChance(enemy, hero, toHero)) {
        int lvl_diff = (hero->getLvl()) - (enemy->getLvl());
        if (lvl_diff >= 10)
            lvl_diff = 9;
        float reduct = reduction(enemy, hero, toHero);

        float resistancemult = enemy->getResistance(type);
        int dmg = static_cast<int>(1.5 * hero->getAd() * hero->getLvl() * hero->getMultDmg() * (1 - reduct) * resistancemult) * (1 + 0.1 * lvl_diff);
        return dmg;
    }
    else if (randChance < enemy->getAtkChance(enemy, hero, toHero)) {
        int lvl_diff = (enemy->getLvl()) - (hero->getLvl());
        if (lvl_diff >= 10)
            lvl_diff = 9;
        float reduct = reduction(enemy, hero, toHero);

        float resistancemult = hero->getResistance(type);
        int dmg = static_cast<int>(1.5 * enemy->getAd() * enemy->getLvl() * enemy->getMultDmg() * (1 - reduct) * resistancemult) * (1 + 0.1 * lvl_diff);
        return dmg;
    }
    return 0;
}
