#include "include/damage.h"
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <conio.h>
#include <string>
#include "include/POSTAC.h"

float dmgcalc::reduction(postac& def, postac *& atk)
{
    int lvldif=(def.getLvl())-(atk->getLvl());
    if (lvldif>=10)
        lvldif=9;
    float reduct=atan(def.getDef())/def.getLvl()*(1+0.1*lvldif);
    std::string classhero = def.getClass();
    if (((classhero=="Warrior")||(classhero=="enemyWarrior")) && reduct>0.75f)
        reduct=0.75f;
    if (((classhero=="Archer")||(classhero=="enemyArcher")) && reduct>0.55f)
        reduct=0.55f;
    if (((classhero=="Mage")||(classhero=="enemyMage")) && reduct>0.40f)
        reduct=0.40f;
    return reduct;
}

int dmgcalc::damage(postac*& atk, postac& def, const DamageType& type)
{
    float randChance = static_cast<float>(std::rand()) / RAND_MAX;
    if(randChance<atk->getAtkChance(atk, def))
    {
        int lvldif=(atk->getLvl())-(def.getLvl());
        if (lvldif>=10)
            lvldif=9;
        float reduct=reduction(def, atk);
        
        float resistancemult = def.getResistance(type);
        int dmg=static_cast<int>(1.5*atk->getAd()*atk->getLvl()*atk->getMultDmg()*(1-reduct)*resistancemult)*(1+0.1*lvldif);
        return dmg;
    }
    else
        std::cout <<atk->getName()<<"'s attack missed!" <<std::endl;
    return 0;
}
