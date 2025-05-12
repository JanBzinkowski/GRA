#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"

class Enemy: public Character {
    int m_EXP_drop = 0;
    int m_gold_drop = 0;

    public:
        Enemy (const std::string& name, const Stats& enemy_stats, const StatsIncrese& enemy_inc_stats) : Character(name, enemy_stats, enemy_inc_stats) {}

        void enemyLvlUp ();

        void setEXPDrop (int exp);
        void setGoldDrop (int gold);
        int getEXPDrop () const;
        int getGoldDrop () const;

        int getDamaged (Hero*& hero, const DamageType& type);
        float getAtkChance (Hero*& hero) const;
        float reduction(Hero*& hero) const;
};


#endif //ENEMY_H
