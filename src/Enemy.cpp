#include "Enemy.h"
#include "DamageCalculation.h"
#include "Hero.h"
#include <math.h>

void Enemy::enemyLvlUp () {
    Stats stat = getStats();
    StatsIncrese inc_stats = getStatsInc();
    stat.lvl++;
    stat.ad += inc_stats.ad_inc;
    stat.base_hp += inc_stats.base_HP_inc * stat.lvl;
    stat.def += inc_stats.def_inc;
}

void Enemy::setGoldDrop (int gold) {
    m_gold_drop = gold;
}

void Enemy::setEXPDrop (int exp) {
    m_EXP_drop = exp;
}

int Enemy::getGoldDrop () const {
    return m_gold_drop;
}

int Enemy::getEXPDrop () const {
    return m_EXP_drop;
}

int Enemy::getDamaged (Hero*& hero, const DamageType& type) {
    int before_HP = this->getCurrentHP();
    int dmg;
    float randChance = rand()/RAND_MAX;
    if (randChance < this->getAtkChance(hero)) {
        int lvl_diff = (this->getLvl()) - (hero->getLvl());
        if (lvl_diff >= 10)
            lvl_diff = 9;
        float reduction_percent = reduction(hero);
        float resistance_mult = hero->getWeaknessMult(type);
        dmg = DMGCalculation::damageCalculator(this->getAd(), this->getLvl(), this->getMultDmg(), reduction_percent, resistance_mult, lvl_diff);
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

float Enemy::reduction (Hero*& hero) const {
    int lvlDiff = (this->getLvl()) - (hero->getLvl());
    if (lvlDiff >= 10)
        lvlDiff = 9;
    float reduction = atan(this->getDef()) / this->getLvl() * (1 + 0.1 * lvlDiff);
    std::string classhero = hero->getClass();
    if (((classhero == "EnemyWarrior")) && reduction > 0.75f)
        reduction = 0.75f;
    else if (((classhero == "EnemyArcher")) && reduction > 0.55f)
        reduction = 0.55f;
    else if (((classhero == "EnemyMage")) && reduction > 0.40f)
        reduction = 0.40f;
    return reduction;
}
