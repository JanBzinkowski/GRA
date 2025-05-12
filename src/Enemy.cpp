#include "Enemy.h"
#include "damage.h"

void Enemy::enemyLvlUp () {
    Stats stat = getStats();
    StatsIncrese incstats = getStatsInc();
    stat.lvl++;
    stat.ad += incstats.ad_inc;
    stat.base_hp += incstats.base_HP_inc * stat.lvl;
    stat.def += incstats.def_inc;
}

void Enemy::setGoldworth (int worth) {
    goldworth = worth;
}

void Enemy::setExpworth (int worth) {
    expworth = worth;
}

int Enemy::getGoldworth () const {
    return goldworth;
}

int Enemy::getExpworth () const {
    return expworth;
}

int Enemy::getDamaged (Hero*& hero, const DamageType& type) {
    int before_HP = this->getCurrentHP();
    int dmg;
    float randChance = rand()/RAND_MAX;
    if (randChance < this->getAtkChance(hero)) {
        int lvl_diff = (this->getLvl()) - (hero->getLvl());
        if (lvl_diff >= 10)
            lvl_diff = 9;
        float reduction = reduct(hero);
        float resistancemult = hero->getResistance(type);
        dmg = dmgcalc::damageCalculator(this->getAd(), this->getLvl(), this->getMultDmg(), reduction, resistancemult, lvl_diff);
    }
    this->incCurrentHP(-dmg);
    if (this->getCurrentHP() < 0)
        this->setCurrentHP(0);
    return before_HP - this->getCurrentHP();
}

float Enemy::getAtkChance (Hero*& hero) const {
    int lvldif = (this->getLvl()) - (hero->getLvl());
    float base = 0;
    switch (this->getAtkTypeNB()) {
        case 1:
            base = 0.95f;
        break;
        case 2:
            base = 0.75f;
        break;
        case 3:
            base = 0.50f;
        break;
        default:
            return 0.0f;
    }
    float chance = base + 0.1f * lvldif;

    if (chance < 0.0f)
        chance = 0.0f;
    else if (chance > 1.0f)
        chance = 1.0f;
    return chance;
}

float Enemy::reduct (Hero*& hero) const {
    int lvlDiff = (this->getLvl()) - (hero->getLvl());
    if (lvlDiff >= 10)
        lvlDiff = 9;
    float reduction = atan(this->getDef()) / this->getLvl() * (1 + 0.1 * lvlDiff);
    std::string classhero = hero->getClass();
    if (((classhero == "enemyWarrior")) && reduction > 0.75f)
        reduction = 0.75f;
    else if (((classhero == "enemyArcher")) && reduction > 0.55f)
        reduction = 0.55f;
    else if (((classhero == "enemyMage")) && reduction > 0.40f)
        reduction = 0.40f;
    return reduction;
}
