#include "include/POSTAC.h"
#include "include/damage.h"
#include "include/Warrior.h"
#include "include/Mage.h"
#include "include/Archer.h"
#include <conio.h>
#include "include/button.h"


extern std::unordered_map<int, itemStats> itemData;

void postac::printstatcurrent()
{
    if(currenthp<=0)
        currenthp=0;
    std::cout<<getName()<<"'s stats:"<<"\nCurrent HP: " << currenthp <</*"\nObecna mana: "<<currentmana<<*/"\n"<<std::endl;
}

void postac::updateStats(itemStats stats, bool equip)
{
    int mod=equip ? 1 : -1;
    stat.ad+=stats.ad*mod;
    stat.basehp+=stats.hp*mod;
    stat.mana+=stats.mana*mod;
    stat.def+=stats.def*mod;
    stat.speed+=stats.speed*mod;
}

void postac::displayInv() const
{
    inventory.printInv();
}

int postac::getInvSize() const
{
    return inventory.getInvSize();
}

void postac::displayEqp() const
{
    std::cout<<"Equipment:\n"<<std::endl;
    if (helmetslot)
    {
        itemStats stats = helmetslot->getStats();
        std::cout<<"1. Helmet: "<< stats.name << ",Item LVL: "<< stats.itemLvl;
        if(stats.hp>0)
            std::cout<< ", HP: " << stats.hp;
        if(stats.def>0)
            std::cout<< ", DEF: " << stats.def;
        if(stats.ad>0)
            std::cout<< ", AD: " << stats.ad;
        if(stats.mana>0)
            std::cout<< ", Mana: "<< stats.mana;
        if(stats.speed>0)
            std::cout<< ", Speed: " << stats.speed;
        std::cout << ")"<< std::endl;
    }
    else
        std::cout << "1. Helmet: NONE"<<std::endl;
    if (chestplateslot)
    {
        itemStats stats = chestplateslot->getStats();
        std::cout<<"2. Chestplate: "<< stats.name << ",Item LVL: "<< stats.itemLvl;
        if(stats.hp>0)
            std::cout<< ", HP: " << stats.hp;
        if(stats.def>0)
            std::cout<< ", DEF: " << stats.def;
        if(stats.ad>0)
            std::cout<< ", AD: " << stats.ad;
        if(stats.mana>0)
            std::cout<< ", Mana: "<< stats.mana;
        if(stats.speed>0)
            std::cout<< ", Speed: " << stats.speed;
        std::cout << ")"<< std::endl;
    }
    else
        std::cout << "2. Chestplate: NONE"<<std::endl;
    if (necklaceslot)
    {
        itemStats stats = necklaceslot->getStats();
        std::cout<<"3. Necklace: "<< stats.name << ", (Item LVL: "<< stats.itemLvl;
        if(stats.hp>0)
            std::cout<< ", HP: " << stats.hp;
        if(stats.def>0)
            std::cout<< ", DEF: " << stats.def;
        if(stats.ad>0)
            std::cout<< ", AD: " << stats.ad;
        if(stats.mana>0)
            std::cout<< ", Mana: "<< stats.mana;
        if(stats.speed>0)
            std::cout<< ", Speed: " << stats.speed;
        std::cout << ")" <<std::endl;
    }
    else
        std::cout << "3. Necklace: NONE"<<std::endl;
    if (glovesslot)
    {
        itemStats stats = glovesslot->getStats();
        std::cout<<"4. Gloves: "<< stats.name << ", (Item LVL: "<< stats.itemLvl;
        if(stats.hp>0)
            std::cout<< ", HP: " << stats.hp;
        if(stats.def>0)
            std::cout<< ", DEF: " << stats.def;
        if(stats.ad>0)
            std::cout<< ", AD: " << stats.ad;
        if(stats.mana>0)
            std::cout<< ", Mana: "<< stats.mana;
        if(stats.speed>0)
            std::cout<< ", Speed: " << stats.speed;
        std::cout << ")" <<std::endl;
    }
    else
        std::cout << "4. Gloves: NONE"<<std::endl;
    if (ringslot)
    {
        itemStats stats = ringslot->getStats();
        std::cout<<"5. Ring: "<< stats.name << ", (Item LVL: "<< stats.itemLvl;
        if(stats.hp>0)
            std::cout<< ", HP: " << stats.hp;
        if(stats.def>0)
            std::cout<< ", DEF: " << stats.def;
        if(stats.ad>0)
            std::cout<< ", AD: " << stats.ad;
        if(stats.mana>0)
            std::cout<< ", Mana: "<< stats.mana;
        if(stats.speed>0)
            std::cout<< ", Speed: " << stats.speed;
        std::cout << ")" <<std::endl;
    }
    else
        std::cout << "5. Ring: NONE"<<std::endl;
    if (leggingsslot)
    {
        itemStats stats = leggingsslot->getStats();
        std::cout<<"6. Leeggings: "<< stats.name << ", (Item LVL: "<< stats.itemLvl;
        if(stats.hp>0)
            std::cout<< ", HP: " << stats.hp;
        if(stats.def>0)
            std::cout<< ", DEF: " << stats.def;
        if(stats.ad>0)
            std::cout<< ", AD: " << stats.ad;
        if(stats.mana>0)
            std::cout<< ", Mana: "<< stats.mana;
        if(stats.speed>0)
            std::cout<< ", Speed: " << stats.speed;
        std::cout << ")" <<std::endl;
    }
    else
        std::cout << "6. Leggings: NONE"<<std::endl;
    if (bootsslot)
    {
        itemStats stats = bootsslot->getStats();
        std::cout<<"7. Boots: "<< stats.name << ", (Item LVL: "<< stats.itemLvl;
        if(stats.hp>0)
            std::cout<< ", HP: " << stats.hp;
        if(stats.def>0)
            std::cout<< ", DEF: " << stats.def;
        if(stats.ad>0)
            std::cout<< ", AD: " << stats.ad;
        if(stats.mana>0)
            std::cout<< ", Mana: "<< stats.mana;
        if(stats.speed>0)
            std::cout<< ", Speed: " << stats.speed;
        std::cout << ")" <<std::endl;
    }
    else
        std::cout << "7. Boots: NONE"<<std::endl;
    if (weaponslot)
    {
        itemStats stats = weaponslot->getStats();
        std::cout<<"8. Weapon: "<< stats.name << ", (Item LVL: "<< stats.itemLvl;
        if(stats.hp>0)
            std::cout<< ", HP: " << stats.hp;
        if(stats.def>0)
            std::cout<< ", DEF: " << stats.def;
        if(stats.ad>0)
            std::cout<< ", AD: " << stats.ad;
        if(stats.mana>0)
            std::cout<< ", Mana: "<< stats.mana;
        if(stats.speed>0)
            std::cout<< ", Speed: " << stats.speed;
        std::cout << ")" <<std::endl;
    }
    else
        std::cout << "8. Weapon: NONE"<<std::endl;
}

Item postac::getItemByIndex(int index) const
{
    switch(index)
    {
    case 1:
        {
            if (helmetslot)
                return *helmetslot;
            break;
        }
    case 2:
        {
            if(chestplateslot)
                return *chestplateslot;
            break;
        }
    case 3:
        {
            if(necklaceslot)
                return *necklaceslot;
            break;
        }
    case 4:
        {
            if(glovesslot)
                return *glovesslot;
            break;
        }
    case 5:
        {
            if(ringslot)
                return *ringslot;
            break;
        }
    case 6:
        {
            if (leggingsslot)
                return *leggingsslot;
            break;
        }
    case 7:
        {
            if (bootsslot)
                return *bootsslot;
            break;
        }
    case 8:
        {
            if(weaponslot)
                return *weaponslot;
            break;
        }
    }
}

bool postac::checkIfEqp (int index) const
{
    switch(index)
    {
    case 1:
        {
            if(helmetslot)
                return true;
            break;
        }
    case 2:
        {
            if(chestplateslot)
                return true;
            break;
        }
    case 3:
        {
            if(necklaceslot)
                return true;
            break;
        }
    case 4:
        {
            if(glovesslot)
                return true;
            break;
        }
    case 5:
        {
            if(ringslot)
                return true;
            break;
        }
    case 6:
       {
            if(leggingsslot)
                return true;
            break;
        }
    case 7:
        {
            if(bootsslot)
                return true;
            break;
        }
    case 8:
        {
            if(weaponslot)
                return true;
            break;
        }
    }
    return false;
}

void postac::addToInv(const Item& item)
{
    inventory.addItem(item);
}

void postac::equip(size_t index)
{
    std::optional<Item> item = inventory.getItemByIndex(index);
    itemStats itemstats = item->getStats();
    switch(item->getType())
    {
    case itemType::Helmet:
        {
            if (helmetslot)
                unequip(*helmetslot);
            helmetslot = item;
            break;
        }
    case itemType::Necklace:
        {
            if (necklaceslot)
                unequip(*necklaceslot);
            necklaceslot = item;
            break;
        }
    case itemType::Chestplate:
        {
            if (chestplateslot)
                unequip(*chestplateslot);
            chestplateslot = item;
            break;
        }
    case itemType::Gloves:
        {
            if (glovesslot)
                unequip(*glovesslot);
            glovesslot = item;
            break;
        }
    case itemType::Ring:
        {
            if (ringslot)
                unequip(*ringslot);
            ringslot = item;
            break;
        }
    case itemType::Leggings:
        {
            if (leggingsslot)
                unequip(*leggingsslot);
            leggingsslot = item;
            break;
        }
    case itemType::Boots:
        {
            if (bootsslot)
                unequip(*bootsslot);
            bootsslot = item;
            break;
        }
    case itemType::Weapon:
        {
            if (weaponslot)
                unequip(*weaponslot);
            weaponslot = item;
            break;
        }
    default:
        {
            std::cout<<"ERROR"<<std::endl;
            return;
            break;
        }
    }
    inventory.removeItem(index-1);
    stats statistics = stat;
    updateStats(itemstats, true);
    
    std::cout<<"\nYour Stats:\n"<<std::endl;
    std::cout<<"Atk: " << statistics.ad<<" + "<< stat.ad-statistics.ad<< " ("<<stat.ad<< ")" <<std::endl;
    std::cout<<"Def: " << statistics.def<<" + "<< stat.def-statistics.def<< " ("<<stat.def<< ")" <<std::endl;
    std::cout<<"HP: " << statistics.basehp<<" + "<< stat.basehp-statistics.basehp<< "("<<stat.basehp<< ")" <<std::endl;
    std::cout<<"Mana: " << statistics.mana<<" + "<< stat.mana-statistics.mana<< " ("<<stat.mana<< ")" <<std::endl;
    std::cout<<"Speed: " <<statistics.speed<<" + " << stat.speed - statistics.speed<< " ("<<stat.speed<< ")" <<std::endl;
}

void postac::unequip(const Item& item)
{
    itemStats stats = item.getStats();
    inventory.addItem(item);
    switch(item.getType())
    {
    case itemType::Helmet:
        {
            if(helmetslot && helmetslot->getId()==item.getId())
                helmetslot.reset();
            break;
        }
    case itemType::Chestplate:
        {
            if(chestplateslot && chestplateslot->getId()==item.getId())
                chestplateslot.reset();
            break;
        }
    case itemType::Necklace:
        {
            if(necklaceslot && necklaceslot->getId()==item.getId())
                necklaceslot.reset();
            break;
        }
    case itemType::Gloves:
        {
            if(glovesslot && glovesslot->getId()==item.getId())
                glovesslot.reset();
            break;
        }
    case itemType::Ring:
        {
            if(ringslot && ringslot->getId()==item.getId())
                ringslot.reset();
            break;
        }
    case itemType::Leggings:
        {
            if(leggingsslot && leggingsslot->getId()==item.getId())
                leggingsslot.reset();
            break;
        }
    case itemType::Boots:
        {
            if(bootsslot && bootsslot->getId()==item.getId())
                bootsslot.reset();
            break;
        }
    case itemType::Weapon:
        {
            if(weaponslot && weaponslot->getId()==item.getId())
                weaponslot.reset();
            break;
        }
    default:
        {
            std::cout << "Item is not Eqipped"<<std::endl;
            return;
        }
    }
    updateStats(stats, false);
    std::cout<<"\nUneqipped " << itemData.at(item.getId()).name<< std::endl;
}

void postac::lvlup()
{
    int exp_treshold=pow(2, stat.lvl)*pow(3, stat.lvl);
    if(exp>=exp_treshold)
    {
        
        
        exp-=exp_treshold;
        stat.lvl++;
        std::cout<<"\nCongratulations! You have leveled up to level " << stat.lvl<<"!\n"<<std::endl;
        std::cout<<"Atk: " << stat.ad<<" + "<< incstats.adinc<<std::endl;
        std::cout<<"Def: " << stat.def<<" + "<< incstats.definc<<std::endl;
        std::cout<<"HP: " << stat.basehp<<" + "<< incstats.basehpinc*stat.lvl<<std::endl;
        std::cout<<"Mana: " << stat.mana<<" + "<< incstats.manainc<<std::endl;
        std::cout<<"Gold Coins: " << currentgold<<" + "<< 5*stat.lvl<<std::endl;
        std::cout<<"\nHP and mana restored."<<std::endl;
        
        stat.ad+=incstats.adinc;
        stat.basehp+=incstats.basehpinc*stat.lvl;
        stat.def+=incstats.definc;
        stat.mana+=incstats.manainc;
        currentgold+=5*stat.lvl;
        currenthp=stat.basehp;
        currentmana=stat.mana;
        if (stat.lvl==2)
        {
            std::cout<<"\n-------------------------------------------------------------------------------------------------------------------------------"<<std::endl;
            std::cout<<"\n\nYou have unlocked:\n  - Potions\n  - Items"<<std::endl;
            
        }
        if (stat.lvl==5)
        {
            std::cout<<"\n-------------------------------------------------------------------------------------------------------------------------------"<<std::endl;
            std::cout<<"\n\nYou have unlocked:\n  - Potion of Mana Regeneration\n  - New Items"<<std::endl;
            
        }
    }
}

void postac::enemyLvlUp()
{
    stat.lvl++;
    stat.ad+=incstats.adinc;
    stat.basehp+=incstats.basehpinc*stat.lvl;
    stat.def+=incstats.definc;
}

void postac::hpcheck()
 {
    if (currenthp <= 0)
    {
        currenthp =0;
        printstatcurrent();
        std::cout<< "\nYou fainted. Someone has got you back to the city, but he took 50% of your resources as a thank you."<<std::endl;
        currentgold/=2;
        currenthp=stat.basehp;
        currentmana+=stat.mana;
    }
}

void postac::pray()
{
    currenthp=stat.basehp;
}

float postac::getAtkChance(postac*& atk, postac& def) const
{
    int lvldif=(atk->getLvl())-( def.getLvl());
    float chance;
    if (atktypenb==1)
    {
        chance=0.95f+0.3*lvldif;
        if (chance>1.0f)
            chance=1.0f;
        return chance;
    }
    if (atktypenb==2)
    {
        chance=0.75f+0.3*lvldif;
        if (chance>1.0f)
            chance=1.0f;
        return chance;
    }
    if (atktypenb==3)
    {
        chance=0.50f+0.3*lvldif;
        if (chance>1.0f)
            chance=1.0f;
        return chance;
    }
    return 0;
}

float postac::getMultDmg() const
{
    if (atktypenb==1)
    {
        return 1;
    }
    if (atktypenb==2)
    {
        return 1.3f;
    }
    if (atktypenb==3)
    {
        return 1.8f;
    }
    return 0;
}

void postac::goldInc (int gold)
{
    currentgold+=gold;
}

void postac::expInc (int experience)
{
    exp+=experience;
}

int postac::getMaxHP() const
{
    return stat.basehp;
}

int postac::getLvl() const
{
    return stat.lvl;
}

int postac::getAd() const
{
    return stat.ad;
}

int postac::getDef() const
{
    return stat.def;
}

int postac::getMaxMana() const
{
    return stat.mana;
}

std::string postac::getName() const
{
    return name;
}

int postac::getSpeed() const
{
    return stat.speed;
}

int postac::getMaxHPinc() const
{
    return incstats.basehpinc;
}

int postac::getAdInc() const
{
    return incstats.adinc;
}

int postac::getDefInc() const
{
    return incstats.definc;
}

int postac::getMaxManaInc() const
{
    return incstats.manainc;
}

int postac::getSpeedInc() const
{
    return incstats.speedinc;
}

void postac::getDamaged(postac*& atk, const DamageType& type)
{
    int thenhp=currenthp;
    dmgcalc calc;
    int dmg=calc.damage(atk, *this, type);
    currenthp-=dmg;
    if(currenthp<0)
        currenthp=0;
    std::cout<<name<<" got damaged by "<< atk->getName()<<" for " << thenhp-currenthp <<"HP." <<std::endl;
}

void postac::regen()
{
    currenthp+=(getLvl()*getLvl()/2);
    if (currenthp>getMaxHP())
        currenthp=getMaxHP();
}

void postac::potionregen()
{
    currenthp+=(getLvl()*getLvl()/2);
    if (currenthp>getMaxHP())
        currenthp=getMaxHP();
}

void postac::instaHP()
{
    currenthp+=(getMaxHP()/4);
    if (currenthp>getMaxHP())
        currenthp=getMaxHP();
}
void postac::manaregen()
{
    currentmana+=getLvl();
    if (currentmana>getMaxMana())
        currentmana=getMaxMana();
}

void postac::potionmanaregen()
{
    currentmana+=getLvl()/2;
    if (currentmana>getMaxMana())
        currentmana=getMaxMana();
}

float postac::getResistance(const DamageType& type) const
{
    auto it = resistance.find(type);
    return it != resistance.end() ? it->second : 1.0f;
}

void postac::setResist(const DamageType& type, float resist)
{
    resistance[type]=resist;
}

void postac::setGoldworth(int worth)
{
    goldworth+=worth;
}

void postac::setExpworth(int worth)
{
    expworth+=worth;
}

int postac::getGoldworth() const
{
    return goldworth;
}

int postac::getExpworth() const
{
    return expworth;
}

void postac::prologueSet(bool isPrologue)
{
    prologue = isPrologue;
}

bool postac::prologueState() const
{
    return prologue;
}

void postac::citySet(bool isCity)
{
    firstcity = isCity;
}

bool postac::cityState() const
{
    return firstcity;
}

void postac::blacksmithSet(bool isBlacksmith)
{
    firstblacksmith = isBlacksmith;
}

bool postac::blacksmithState() const
{
    return firstblacksmith;
}

void postac::churchSet(bool isChurch)
{
    firstchurch = isChurch;
}

bool postac::churchState() const
{
    return firstchurch;
}

void postac::tavernSet(bool isTavern)
{
    firsttavern = isTavern;
}

bool postac::tavernState() const
{
    return firsttavern;
}

void postac::mapSet(bool isMap)
{
    firstmap = isMap;
}

bool postac::mapState() const
{
    return firstmap;
}

void postac::setHPpot(int x)
{
    healthpotion+=x;
}

int postac::getHPpot() const
{
    return healthpotion;
}

void postac::setManapot(int x)
{
    manapotion+=x;
}

int postac::getManapot() const
{
    return manapotion;
}

void postac::setHPRegpot(int x)
{
    regenpotion+=x;
}

int postac::getHPRegpot() const
{
    return regenpotion;
}

void postac::setManapotT(int x)
{
    manapotionT+=x;
}

int postac::getManapotT() const
{
    return manapotionT;
}

void postac::setHPRegpotT(int x)
{
    regenpotionT+=x;
}

int postac::getHPRegpotT() const
{
    return regenpotionT;
}

void postac::setActionpot(int x)
{
    actionPot+=x;
}

int postac::getActionpot() const
{
    return actionPot;
}

void postac::setFastAction(bool isFastAction)
{
    fastaction=isFastAction;
}

bool postac::getFastAction() const
{
    return fastaction;
}

void postac::setPotionCD()
{
    potionCD=3;
}

int postac::getPotionCD() const
{
    return potionCD;
}

void postac::save_to_file(const std::string filename, postac*& hero)
{
    std::ofstream file(filename);
    if (file.is_open())
    {
        file << hero->getClass() << "\n"
        << hero->getName() << "\n"
        << hero->getLvl() << "\n"
        << hero->getMaxHP() << "\n"
        << hero->getAd() << "\n"
        << hero->getDef() << "\n"
        << hero->getMaxMana() << "\n"
        << hero->getSpeed() << "\n"
        << hero->getMaxHPinc() << "\n"
        << hero->getAdInc() << "\n"
        << hero->getDefInc() << "\n"
        << hero->getMaxManaInc() << "\n"
        << hero->getSpeedInc() << "\n"
        << hero->currentgold << "\n"
        << hero->currenthp << "\n"
        << hero->currentmana << "\n"
        << hero->exp << "\n"
        << hero->prologueState() << "\n"
        << hero->getHPpot() << "\n"
        << hero->getHPRegpot() << "\n"
        << hero->getManapot() << "\n"
        << hero->getActionpot() << "\n"
        << hero->getResistance(DamageType::MagicEnergy) << "\n"
        << hero->getResistance(DamageType::MagicFire) << "\n"
        << hero->getResistance(DamageType::MagicIce) << "\n"
        << hero->getResistance(DamageType::MagicEarth) << "\n"
        << hero->getResistance(DamageType::MagicWater) << "\n"
        << hero->getResistance(DamageType::MagicPoison) << "\n"
        << hero->getResistance(DamageType::MagicAir) << "\n"
        << hero->getResistance(DamageType::Physical)<< "\n"
        << hero->getResistance(DamageType::Enviroment)<<"\n"
        << hero->inventory.items.size()<<"\n";

        for(size_t i=0; i<inventory.items.size(); i++)
        {
            file<<inventory.items[i].getId()<<"\n"
            <<inventory.items[i].stats.hp<<"\n"
            <<inventory.items[i].stats.ad<<"\n"
            <<inventory.items[i].stats.def<<"\n"
            <<inventory.items[i].stats.mana<<"\n"
            <<inventory.items[i].stats.speed<<"\n";
        }

        if(helmetslot)
        {
            file<<"x\n"
            <<helmetslot->getId()<<"\n"
            <<helmetslot->stats.hp<<"\n"
            <<helmetslot->stats.ad<<"\n"
            <<helmetslot->stats.def<<"\n"
            <<helmetslot->stats.mana<<"\n"
            <<helmetslot->stats.speed<<"\n";
        }
        else
            file<<"NOHELMET\n";

        if(necklaceslot)
        {
            file<<"x\n"
            <<necklaceslot->getId()<<"\n"
            <<necklaceslot->stats.hp<<"\n"
            <<necklaceslot->stats.ad<<"\n"
            <<necklaceslot->stats.def<<"\n"
            <<necklaceslot->stats.mana<<"\n"
            <<necklaceslot->stats.speed<<"\n";
        }
        else
            file<<"NONECKLACE\n";

        if(chestplateslot)
        {
            file<<"x\n"
            <<chestplateslot->getId()<<"\n"
            <<chestplateslot->stats.hp<<"\n"
            <<chestplateslot->stats.ad<<"\n"
            <<chestplateslot->stats.def<<"\n"
            <<chestplateslot->stats.mana<<"\n"
            <<chestplateslot->stats.speed<<"\n";
        }
        else
            file<<"NOCHEST\n";

        if(glovesslot)
        {
            file<<"x\n"
            <<glovesslot->getId()<<"\n"
            <<glovesslot->stats.hp<<"\n"
            <<glovesslot->stats.ad<<"\n"
            <<glovesslot->stats.def<<"\n"
            <<glovesslot->stats.mana<<"\n"
            <<glovesslot->stats.speed<<"\n";
        }
        else
            file<<"NOGLOVES\n";

        if(ringslot)
        {
            file<<"x\n"
            <<ringslot->getId()<<"\n"
            <<ringslot->stats.hp<<"\n"
            <<ringslot->stats.ad<<"\n"
            <<ringslot->stats.def<<"\n"
            <<ringslot->stats.mana<<"\n"
            <<ringslot->stats.speed<<"\n";
        }
        else
            file<<"NORING\n";

        if(leggingsslot)
        {
            file<<"x\n"
            <<leggingsslot->getId()<<"\n"
            <<leggingsslot->stats.hp<<"\n"
            <<leggingsslot->stats.ad<<"\n"
            <<leggingsslot->stats.def<<"\n"
            <<leggingsslot->stats.mana<<"\n"
            <<leggingsslot->stats.speed<<"\n";
        }
        else
            file<<"NOLEGS\n";

        if(bootsslot)
        {
            file<<"x\n"
            <<bootsslot->getId()<<"\n"
            <<bootsslot->stats.hp<<"\n"
            <<bootsslot->stats.ad<<"\n"
            <<bootsslot->stats.def<<"\n"
            <<bootsslot->stats.mana<<"\n"
            <<bootsslot->stats.speed<<"\n";
        }
        else
            file<<"NOBOOTS\n";

        if(weaponslot)
        {
            file<<"x\n"
            <<weaponslot->getId()<<"\n"
            <<weaponslot->stats.hp<<"\n"
            <<weaponslot->stats.ad<<"\n"
            <<weaponslot->stats.def<<"\n"
            <<weaponslot->stats.mana<<"\n"
            <<weaponslot->stats.speed<<"\n";
        }
        else
            file<<"NOWEAPON\n";

        file.close();
    }
    else
    {
        std::cout<<"Saving gamestate ERROR" << std::endl;
    }
}


bool postac::load_from_file(const std::string filename, postac*& hero)
{
    std::ifstream file(filename);
    if (file.is_open())
    {
        std::string className;
        std::string name;
        stats charStats;
        statsincrese incStats;

        file >> className >> name
             >> charStats.lvl >> charStats.basehp >> charStats.ad
             >> charStats.def >> charStats.mana >> charStats.speed
             >> incStats.basehpinc >> incStats.adinc >> incStats.definc
             >> incStats.manainc >> incStats.speedinc;

        if (className == "Warrior")
        {
            hero = new Warrior(name, charStats);
        }
        else if (className == "Mage")
        {
            hero = new Mage(name, charStats);
        }
        else if (className == "Archer")
        {
            hero = new Archer(name, charStats);
        }
        else
        {
            std::cerr << "Error: Unknown class name '" << className << "'!" << std::endl;
            return false;
        }
        bool isPrologue;
        int x,y,z,a;
        file >> hero->currentgold >> hero->currenthp
             >> hero->currentmana >> hero->exp >> isPrologue
             >> x >> y >> z >> a;
        hero->setHPpot(x);
        hero->setHPRegpot(y);
        hero->setManapot(z);
        hero->setActionpot(a);
        hero->prologueSet(isPrologue);
        float energy, fire, ice, earth, water, poison, air, phys, env;
        file>> energy
        >> fire
        >> ice
        >> earth
        >> water
        >> poison
        >> air
        >> phys
        >> env;
        hero->setResist(DamageType::MagicEnergy, energy);
        hero->setResist(DamageType::MagicFire, fire);
        hero->setResist(DamageType::MagicIce, ice);
        hero->setResist(DamageType::MagicEarth, earth);
        hero->setResist(DamageType::MagicWater, water);
        hero->setResist(DamageType::MagicPoison, poison);
        hero->setResist(DamageType::MagicAir, air);
        hero->setResist(DamageType::Physical, phys);
        hero->setResist(DamageType::Enviroment, env);
        int invSize;

        file>>invSize;
        for(int i=0; i<invSize; i++)
        {
            int id;
            file>>id;
            Item item(id);
            file>>item.stats.hp;
            file>>item.stats.ad;
            file>>item.stats.def;
            file>>item.stats.mana;
            file>>item.stats.speed;
            hero->inventory.items.push_back(item);

        }
        std::string isSlot;
        file>>isSlot;
        std::cout << isSlot << std::endl;
        if (isSlot == "NOHELMET")
            std::cout<<"OK";
        else
        {
            int id;
            file >> id;
            Item helmet(id);
            file>>helmet.stats.hp
            >>helmet.stats.ad
            >>helmet.stats.def
            >>helmet.stats.mana
            >>helmet.stats.speed;
            hero->helmetslot = std::make_optional<Item>(helmet);
        }
        file>>isSlot;
        if (isSlot == "NONECKLACE")
            std::cout<<"OK";
        else
        {
            int id;
            file>>id;
            Item necklace(id);
            file>>necklace.stats.hp
            >>necklace.stats.ad
            >>necklace.stats.def
            >>necklace.stats.mana
            >>necklace.stats.speed;
            hero->necklaceslot = std::make_optional<Item>(necklace);
        }
        file>>isSlot;
        if (isSlot == "NOCHEST")
            std::cout<<"OK";
        else
        {
            int id;
            file>>id;
            Item chest(id);
            file>>chest.stats.hp
            >>chest.stats.ad
            >>chest.stats.def
            >>chest.stats.mana
            >>chest.stats.speed;
            hero->chestplateslot = std::make_optional<Item>(chest);
        }
        file>>isSlot;
        if (isSlot == "NOGLOVES")
            std::cout<<"OK";
        else
        {
            int id;
            file>>id;
            Item gloves(id);
            file>>gloves.stats.hp
            >>gloves.stats.ad
            >>gloves.stats.def
            >>gloves.stats.mana
            >>gloves.stats.speed;
            hero->glovesslot = std::make_optional<Item>(gloves);
        }
        file>>isSlot;
        if (isSlot == "NORING")
            std::cout<<"OK";
        else
        {
            int id;
            file>>id;
            Item ring(id);
            file>>ring.stats.hp
            >>ring.stats.ad
            >>ring.stats.def
            >>ring.stats.mana
            >>ring.stats.speed;
            hero->ringslot = std::make_optional<Item>(ring);
        }
        file>>isSlot;
        if (isSlot == "NOLEGS")
            std::cout<<"OK";
        else
        {
            int id;
            file>>id;
            Item leg(id);
            file>>leg.stats.hp
            >>leg.stats.ad
            >>leg.stats.def
            >>leg.stats.mana
            >>leg.stats.speed;
            hero->leggingsslot = std::make_optional<Item>(leg);
        }
        file>>isSlot;
        if (isSlot == "NOBOOTS")
            std::cout<<"OK";
        else
        {
            int id;
            file>>id;
            Item boots(id);
            file>>boots.stats.hp
            >>boots.stats.ad
            >>boots.stats.def
            >>boots.stats.mana
            >>boots.stats.speed;
            hero->bootsslot = std::make_optional<Item>(boots);
        }
        file>>isSlot;
        if (isSlot == "NOWEAPON")
            std::cout<<"OK";
        else
        {
            int id;
            file>>id;
            Item weapon(id);
            file>>weapon.stats.hp
            >>weapon.stats.ad
            >>weapon.stats.def
            >>weapon.stats.mana
            >>weapon.stats.speed;
            hero->weaponslot = std::make_optional<Item>(weapon);
        }
        file.close();
        return true;
    }
    else
    {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return false;
    }
}
