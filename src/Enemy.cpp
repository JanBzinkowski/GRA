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

int Enemy::getDamaged(Enemy*& enemy, Hero*& hero, const DamageType& type){
  int thenhp = this->getCurrentHP();
    dmgcalc calc;
    int dmg = calc.damage(enemy, hero, type, false);
    this -> incCurrentHP(-dmg);
    if (this->getCurrentHP() < 0)
        this->setCurrentHP(0);
    return thenhp - this->getCurrentHP();
}