#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"

class Enemy: public character {
    int expworth = 0;
    int goldworth = 0;

    public:
        Enemy (const std::string& name, const Stats& enemystats, const StatsIncrese& enemyincstats) : character(name, enemystats, enemyincstats) {}

        void enemyLvlUp ();

        void setExpworth (int worth);
        void setGoldworth (int worth);
        int getExpworth () const;
        int getGoldworth () const;

        int getDamaged (Enemy*& enemy, Hero*& hero, const DamageType& type) override;
};


#endif //ENEMY_H
