#include "include/game.h"
#include "include/enemyWarrior.h"
#include "include/enemyArcher.h"
#include "include/enemyMage.h"
#include <vector>
#include <algorithm>

#if defined(_WIN32) || defined(_WIN64)
    #define CLEAR_SCREEN system("cls");
#else
    #define CLEAR_SCREEN system("clear");
#endif

#define PotionTime 3

extern std::unordered_map <int, enemyStats> enemies;

void clearScreen()
{
    CLEAR_SCREEN;
}

postac* game::createEnemy(const enemyStats& stats)
{
    switch (stats.Class)
    {
        case enemyClasses::enemyWarrior:
            return new enemyWarrior(stats.name, stats.stats);
        case enemyClasses::enemyMage:
            return new enemyMage(stats.name, stats.stats);
        case enemyClasses::enemyArcher:
            return new enemyArcher(stats.name, stats.stats);
        default:
            throw std::runtime_error("Unknown enemy class");
    }
}

bool game::areShopsOpen() const
{
    if (Time.gettime()>=480&&Time.gettime()<1320)
        return true;
    return false;
}

void game::loss(postac*& hero)
{
    std::cout<<"You have fainted."<<std::endl;
    std::cout<<"Luckily someone found you and brought you to the church, but he wanted half of your gold in exchange."<<std::endl;
    getch();
    setLocation(Location::Church);
    hero->currentgold-=hero->currentgold/2;
    hero->pray();
}

bool game::retcity()
{
    int ret;
    while (true)
    {
        clearScreen();
        std::cout<<"Do you want to return to the city, or search for next foe?"
        <<"\n1. Stay\n2. Return to the city"<<std::endl;
        std::cin>>ret;
        if (ret==1||ret==2)
            break;
    }
    if (ret==1)
        return false;
    else
    {
        setLocation(Location::City);
        return true;
    }
}

bool game::enemyenc(int indexmin, int indexmax, int exp, int gold, int maxlvl, postac*& hero)
{
    clearScreen();
    std::uniform_int_distribution<> dist(indexmin, indexmax);
    int index = dist(gen);
    postac* enemy=createEnemy(enemies.at(index));
    enemy->setExpworth(exp);
    enemy->setGoldworth(gold);
    while(enemy->getLvl()<hero->getLvl()||enemy->getLvl()>=maxlvl)
    {
        enemy->enemyLvlUp();
    }
    std::cout<<"You have been attacked by "<<enemy->getName()<<" (Lvl "<< enemy->getLvl()<<")!"<<std::endl;
    getch();
    clearScreen();
    int res = fight(hero, enemy);
    if(res==0)
    {
        loss(hero);
        delete enemy;
        return false;
    }
    delete enemy;
    if (retcity())
        return false;
    return true;
}

bool game::enemyenc3(int indexmin, int indexmax, int exp, int gold, int maxlvl, postac*& hero)
{
    clearScreen();
    std::uniform_int_distribution<> dist(indexmin, indexmax);
    int index = dist(gen);
    postac* enemy1=createEnemy(enemies.at(index));
    enemy1->setExpworth(exp);
    enemy1->setGoldworth(gold);
    while(enemy1->getLvl()<hero->getLvl()||enemy1->getLvl()>=maxlvl)
    {
        enemy1->enemyLvlUp();
    }
    index = dist(gen);
    postac* enemy2=createEnemy(enemies.at(index));
    enemy2->setExpworth(exp);
    enemy2->setGoldworth(gold);
    while(enemy2->getLvl()<hero->getLvl()||enemy2->getLvl()>=maxlvl)
    {
        enemy2->enemyLvlUp();
    }
    index = dist(gen);
    postac* enemy3=createEnemy(enemies.at(index));
    enemy3->setExpworth(exp);
    enemy3->setGoldworth(gold);
    while(enemy3->getLvl()<hero->getLvl()||enemy3->getLvl()>=maxlvl)
    {
        enemy3->enemyLvlUp();
    }
    std::cout<<"Watch out! You have been attacked by "<<enemy1->getName()<<" (Lvl "<< enemy1->getLvl()<<")"
    <<enemy2->getName()<<" (Lvl "<< enemy2->getLvl()<<")"
    <<enemy3->getName()<<" (Lvl "<< enemy3->getLvl()<<")!"<<std::endl;
    getch();
    clearScreen();
    int res = fight3(hero, enemy1, enemy2, enemy3);
    if(res==0)
    {
        loss(hero);
        delete enemy1;
        delete enemy2;
        delete enemy3;
        return false;
    }
    delete enemy1;
    delete enemy2;
    delete enemy3;
    if (retcity())
        return false;
    return true;
}

void game::lvl0(postac*& hero)
{
    getch();
    std::cout<<"Currently playing: Tutorial"<<std::endl;
    postac* enemy1=createEnemy(enemies.at(0));
    enemy1->setExpworth(6);
    enemy1->setGoldworth(10);
    getch();
    clearScreen();
    std::cout<<"One day when you have been laying under an old oak tree in the middle of plains nearby the city you heard loud crack and scream..."<<std::endl;
    getch();
    std::cout<<"\nYou rushed to the source of all that noise to see what is going on."<<std::endl;
    getch();
    std::cout<<"\nYou found the King, whose carriage just broke down. The king seemed distressed so you came closer."<<std::endl;
    getch();
    std::cout<<"\nThe King got attacked by a bunny. But there was something wrong with that bunny... You came to help and then the Killer Bunny attacked you."<<std::endl;
    getch();
    int fight1=fight(hero, enemy1);
    if (fight1==0)
    {
        getch();
        clearScreen();
        hero->prologueSet(true);
        std::cout<<"Sadly you have been badly injured by your enemy."<<std::endl;
        getch();
        std::cout<<"\nLuckily King's guards came in time to save both you and the King."<<std::endl;
        getch();
        std::cout<< "\nBut won or lost, this fight taught you various things. You gain 6XP."<<std::endl;
        hero->exp+=6;
        hero->lvlup();
        getch();
        clearScreen();
        std::cout<<"You have been brought to the church."<<std::endl;
        getch();
        std::cout<< "\nMonks took care of u and you made a full recovery." <<std::endl;
        getch();
        std::cout<<"\nKing paid for all of the expenses and gave you 20 Gold Coins as a reward for your bravery." <<std::endl;
        getch();
        std::cout<<"\nBut remember that it won't happen again."<<std::endl;
        hero->currentgold+=20;
        hero->pray();
    }
    else
    {
        getch();
        clearScreen();
        std::cout<<"Watch out! New wave of enemies incoming!"<<std::endl;
        postac* enemy2 = createEnemy(enemies.at(1));
        postac* enemy3 = createEnemy(enemies.at(2));
        postac* enemy4 = createEnemy(enemies.at(3));
        getch();
        int fight2=fight3(hero,enemy2,enemy3,enemy4);
        if (fight2==0)
        {
            getch();
            clearScreen();
            hero->prologueSet(true);
            std::cout<<"Sadly you have been badly injured by your enemies."<<std::endl;
            getch();
            std::cout<<"\nLuckily King's guards came in time to save both you and the King."<<std::endl;
            getch();
            clearScreen();
            std::cout<<"You have been brought to the church."<<std::endl;
            getch();
            std::cout<< "\nMonks took care of u and you made a full recovery." <<std::endl;
            getch();
            std::cout<<"\nKing paid for all of the expenses and gave you 20 Gold Coins as a reward for your bravery." <<std::endl;
            getch();
            std::cout<<"\nBut remember that it won't happen again."<<std::endl;
            hero->currentgold+=20;
            hero->pray();
        }
        else
        {
            getch();
            clearScreen();
            hero->prologueSet(true);
            std::cout<<"\nKing's guards came to save both you and the King."<<std::endl;
            getch();
            std::cout<<"\nThey escorted you to the city."<<std::endl;
            getch();
            std::cout<<"\nKing thanked you and gave you 20 Gold Coins as a reward for your bravery." <<std::endl;
            getch();
            std::cout<<"\nThe King departed with his guards towards the castle."<<std::endl;
            hero->currentgold+=20;
        }
        delete enemy2;
        delete enemy3;
        delete enemy4;
    }
    setLocation(Location::City);
    hero->citySet(true);
    hero->churchSet(true);
    hero->tavernSet(true);
    hero->blacksmithSet(true);
    hero->mapSet(true);
    delete enemy1;
    Time.resetTime();
}

void game::forest(postac*& hero)
{
    getch();
    if(!enemyenc(4, 6, 6, 10, 10, hero))
        return;
    if(!enemyenc(4, 6, 6, 10, 10, hero))
        return;
    if(!enemyenc(4, 8, 10, 15, 10, hero))
        return;
    if(!enemyenc(4, 8, 10, 15, 10, hero))
        return;
    clearScreen();
    std::cout<<"Huge wave of enemies ahead!"<<std::endl;
    getch();
    if(!enemyenc3(9, 12, 14, 20, 10, hero))
        return;
    if(!enemyenc(7, 12, 14, 20, 10, hero))
        return;
    if(!enemyenc(7, 12, 14, 20, 10, hero))
        return;
    if(!enemyenc(7, 12, 14, 20, 10, hero))
        return;
    if(!enemyenc(7, 12, 14, 20, 10, hero))
        return;
    if(!enemyenc(13, 13, 22, 30, 10, hero))
        return;
    getch();
    clearScreen();
    if(!isUnlocked(Location::Swamp))
    {
        unlockLocations(Location::Swamp);
        std::cout<<"You have unlocked swamp. Are you scared to get yourself dirty?"<<std::endl;
        getch();
        clearScreen();
    }
    std::cout<<"You have come to the edge of the forest, slaying all enemies that stood on you way.\n\nReturning to the city now." <<std::endl;
    getch();
}

int game::fight(postac*& hero, postac*& enemy)
{
    while (hero->currenthp>0)
    {
        hero->regen();
        if (hero->getHPRegpotT()>0)
        {
            hero->potionregen();
            hero->setHPRegpotT(-1);
        }
        if(hero->getManapotT()>0)
        {
            hero->manaregen();
            hero->setManapotT(-1);
        }
        while (true)
        {
            clearScreen();
            int action;
            std::cout<<"Choose your action:\n\n1. Attack"<<std::endl;
            if(hero->getPotionCD()==0&&hero->getLvl()>=2)
                std::cout<<"2. Drink Potion"<<std::endl;
            std::cin >>action;
            if(action==1)
            {
                enemy->atktypenb = std::rand() % 3 +1;//

                int whofirst;
                if((hero->getSpeed())>(enemy->getSpeed()))
                    whofirst=1;
                if((hero->getSpeed())<(enemy->getSpeed()))
                    whofirst=0;
                if((hero->getSpeed())==(enemy->getSpeed()))
                    whofirst=std::rand()%2;
                hero->printstatcurrent();
                enemy->printstatcurrent();
                if(whofirst==1)
                {
                    heroaction(enemy, hero);
                    if (enemy->currenthp<=0)
                    {
                        std::cout<<std::endl;
                        fightEnd(hero, enemy);
                        hero->setFastAction(false);
                        hero->setHPRegpotT(-hero->getHPRegpotT());
                        hero->setManapotT(-hero->getManapotT());
                        return 1;
                    }
                    enemyaction(enemy, hero);
                    getch();
                    if(hero->currenthp<=0)
                    {
                        hero->setFastAction(false);
                        hero->setHPRegpotT(-(hero->getHPRegpotT()));
                        hero->setManapotT((-hero->getManapotT()));
                        return 0;
                    }
                }
                else
                {
                    enemyaction(enemy, hero);
                    if(hero->currenthp<=0)
                    {
                        hero->setFastAction(false);
                        hero->setHPRegpotT(-(hero->getHPRegpotT()));
                        hero->setManapotT((-hero->getManapotT()));
                        return 0;
                    }
                    heroaction(enemy, hero);
                    getch();
                    hero->setFastAction(false);
                    if (enemy->currenthp<=0)
                    {
                        std::cout<<std::endl;
                        fightEnd(hero, enemy);
                        hero->setFastAction(false);
                        hero->setHPRegpotT(-hero->getHPRegpotT());
                        hero->setManapotT(-hero->getManapotT());
                        return 1;
                    }
                }
                break;
            }
            else if(action==2&&hero->getPotionCD()==0&&hero->getLvl()>=2)
            {
                potionMenu(hero);
            }
        }
    }
    return 0;
}

void game::fightEnd(postac*& hero, postac*& enemy)
{
    if(enemy->currenthp<=0)
    {
        std::cout << "You have slain " << enemy->getName() << ". You earn " << enemy->getExpworth() << " EXP points and " << enemy->getGoldworth() << " Gold coins." <<std::endl;
        hero->exp+=enemy->getExpworth();
        hero->goldInc(enemy->getGoldworth());
        getch();
        hero->lvlup();
    }
}

void game::setLocation(Location newLocation)
{
    currentLocation=newLocation;
}

Location game::getLocation() const
{
    return currentLocation;
}

bool game::isUnlocked(Location location) const
{
    return unlockedLocations.at(location);
}

std::string game::isUnlockedPrint(Location location) const
{
    if (isUnlocked(location))
        return "[Unlocked]";
    return "[Locked]";
}

void game::unlockLocations(Location locationToUnlock)
{
    if(!isUnlocked(locationToUnlock))
        unlockedLocations.at(locationToUnlock)=true;
}

void game::updateBlacksmith()
{
    if(Time.newDayBlacksith)
    {
        BlacksmithNewItems=true;
        Time.newDayBlacksith=false;
    }
    else
        BlacksmithNewItems=false;
}

void game::church(postac*& hero)
{

    while (true)
    {
        Time.timeFlow();
        Time.printTime();
        std::cout<<"Church"<<"\nA place where you can pray, or buy potions from humble monks."<<std::endl;
        std::cout<<"\nWhat do you want to do?\n"
        <<"\n1. Pray for health. (5 Gold Coins)"
        <<"\n2. Buy potions."
        <<"\n\n0. Go back to the city."
        <<"\n\n\n-------------------------------------------------------------------------------\n"
        <<"\tMoney: "<<hero->currentgold<< " Gold Coins\t\t Current HP: "<< hero->currenthp <<std::endl;
        int dest;
        std::cin>>dest;
        if (dest==1&&hero->currentgold>=5)
        {
            clearScreen();
            hero->pray();
            std::cout<<"You have prayed for your health. Gods bless you and regenerate your HP."<<std::endl;
            hero->currentgold-=5;
            getch();
            clearScreen();
        }
        else if (dest==1&&hero->currentgold<5)
        {
            std::cout << "\nNot enough Gold Coins."<<std::endl;
            getch();
            clearScreen();
        }
        else if(dest==2)
        {
            while (true)
            {
                clearScreen();
                std::cout << "What potion do you want to buy?"<<std::endl;
                std::cout << "\n1. Instant Health Potion (20 Gold Coins)\n2. Potion of Regeneration (10 Gold Coins)"<<std::endl;
                if(hero->getLvl()>=5)
                    std::cout<<"3. Potion of Mana Regeneration (30 Gold Coins)"<<std::endl;
                if(hero->getLvl()>=10)
                    std::cout<<"4. Potion of Fast Action (80 Gold Coins)"<<std::endl;
                std::cout<<"\n\n0. \"I don't want a potion.\""<<std::endl;
                std::cout<<"\n\n\n-------------------------------------------------------------------------------\n\n"
                <<"\tMoney: "<<hero->currentgold<< " Gold Coins\t\t Current HP: "<< hero->currenthp <<std::endl;
                std::cout<<"\n\n\n-------------------------------------------------------------------------------\n\n"
                <<"\tPotions in Inventory:\n\n\t\t1. Instant Health Potion: x"<<hero->getHPpot()
                << "\n\t\t2. Potion of Regeneration: x"<< hero->getHPRegpot() <<std::endl;
                if (hero->getLvl()>=5)
                    std::cout << "\t\t3. Potion of Mana Regeneration: x"<< hero->getManapot() <<std::endl;
                if (hero->getLvl()>=10)
                    std::cout << "\t\t4. Potion of Fast Action: x"<< hero->getActionpot() <<std::endl;

                int potionnb;
                while (true)
                {
                    std::cin>>potionnb;
                    if (potionnb==1&&hero->currentgold>=20)
                    {
                        hero->currentgold-=20;
                        hero->setHPpot(1);
                        std::cout<<"You have bought an Instant Health Potion."<<std::endl;
                        getch();
                        clearScreen();
                        break;
                    }
                    else if(potionnb==1&&hero->currentgold<20)
                    {
                        std::cout<<"You don't have enough Gold Coins."<<std::endl;
                        getch();
                        clearScreen();
                        break;
                    }
                    else if (potionnb==2&&hero->currentgold>=10)
                    {
                        hero->currentgold-=10;
                        hero->setHPRegpot(1);
                        std::cout<<"You have bought an Potion of Regeneration."<<std::endl;
                        getch();
                        clearScreen();
                        break;
                    }
                    else if(potionnb==1&&hero->currentgold<10)
                    {
                        std::cout<<"You don't have enough Gold Coins."<<std::endl;
                        getch();
                        clearScreen();
                        break;
                    }
                    else if (potionnb==3&&hero->currentgold>=30&&hero->getLvl()>=5)
                    {
                        hero->currentgold-=80;
                        hero->setActionpot(1);
                        std::cout<<"You have bought an Potion of Mana Regeneration."<<std::endl;
                        getch();
                        clearScreen();
                        break;
                    }
                    else if(potionnb==3&&hero->currentgold<30&&hero->getLvl()>=5)
                    {
                        std::cout<<"You don't have enough Gold Coins."<<std::endl;
                        getch();
                        clearScreen();
                        break;
                    }
                    else if (potionnb==4&&hero->currentgold>=80&&hero->getLvl()>=10)
                    {
                        hero->currentgold-=80;
                        hero->setActionpot(1);
                        std::cout<<"You have bought an Potion of Fast Action."<<std::endl;
                        getch();
                        clearScreen();
                        break;
                    }
                    else if(potionnb==4&&hero->currentgold<80&&hero->getLvl()>=10)
                    {
                        std::cout<<"You don't have enough Gold Coins."<<std::endl;
                        getch();
                        clearScreen();
                        break;
                    }
                    else if (potionnb==0)
                        break;
                }
                if (potionnb==0)
                    break;
            }
            getch();
            clearScreen();
        }
        else if (dest==0)
        {
            setLocation(Location::City);
            std::cout << "\nReturning to the city"<<std::endl;
            getch();
            clearScreen();
            break;
        }
    }
}

void game::tavern(postac*& hero)
{
    while (true)
    {
        Time.timeFlow();
        Time.printTime();
        clearScreen();
        std::cout<<"Tavern"<<"\nA place where you can rest (save the game), drink and accept missions."<<std::endl;
        std::cout<<"\nWhat do you want to do?\n"
        <<"\n1. Drink (1 Gold Coin)"
        <<"\n2. Rest (5 Gold Coins)."
        <<"\n3. (TBA) Missions."
        <<"\n\n4. Go back to the city."\
        <<"\n\n\n-------------------------------------------------------------------------------\n"
        <<"\tMoney: "<<hero->currentgold<< " Gold Coins\t\t Current HP: "<< hero->currenthp <<std::endl;
        int dest;
        std::cin>>dest;
        if (dest==1&&hero->currentgold>=1)
        {
            std::cout<<"You drank a pint of beer."<<std::endl;
            hero->currentgold-=1;
            getch();
            clearScreen();
        }
        else if (dest==1&&hero->currentgold<1)
        {
            std::cout << "\nNot enough Gold Coins."<<std::endl;
            getch();
            clearScreen();
        }
        else if(dest==2&&hero->currentgold>=5)
        {
            hero->currentgold-=5;
            std::cout << "You lay down in bed to rest."<<std::endl;
            while (true)
            {
                getch();
                clearScreen();
                int saveslot;
                std::cout<<"Choose save slot that you want to save in:\n1. Save 1\n2. Save 2\n3. Save 3\n\n4. Exit"<<std::endl;
                std::cin>>saveslot;
                if (saveslot==1)
                {
                    const std::string filename = "saves/saveFile1.txt";
                    hero->save_to_file(filename, hero);
                    setLocation(Location::City);
                    break;
                }
                else if (saveslot==2)
                {
                    const std::string filename="saves/saveFile2.txt";
                    hero->save_to_file(filename, hero);
                    setLocation(Location::City);
                    break;
                }
                else if (saveslot==3)
                {
                    const std::string filename = "saves/saveFile3.txt";
                    hero->save_to_file(filename, hero);
                    setLocation(Location::City);
                    break;
                }
                else if (saveslot==4)
                {
                    std::cout<<"Gold refunded."<< std::endl;
                    hero->currentgold+=5;
                    break;
                }
            }
            getch();
            clearScreen();
            Time.resetTime();
        }
        else if(dest==2&&hero->currentgold<5)
        {
            std::cout << "\nNot enough Gold Coins."<<std::endl;
            getch();
            clearScreen();
        }
        else if (dest==3)
        {
            std::cout << "\nTBA"<<std::endl;
            getch();
            clearScreen();
        }
        else if (dest==4)
        {
            setLocation(Location::City);
            std::cout << "\nReturning to the city"<<std::endl;
            getch();
            clearScreen();
            break;
        }
    }
}

void game::itemRandomize(postac*& hero, std::mt19937& gen)
{
    if(BlacksmithNewItems)
    {
        blacksmithInv.clear();
        int min_id, max_id;
        if (hero->getClass()=="Warrior"&&hero->getLvl()<=7)
        {
            min_id=1;
            max_id=20;
        }
        else if (hero->getClass()=="Mage"&&hero->getLvl()<=7)
        {
            min_id=21;
            max_id=40;
        }
        else if (hero->getClass()=="Archer"&&hero->getLvl()<=7)
        {
            min_id=41;
            max_id=60;
        }

        std::uniform_int_distribution<> dist (min_id, max_id);

        for(int i=0; i<6; i++)
        {


            int ItemId=dist(gen);
            Item item(ItemId);
            item.generateStats(gen, hero);
            blacksmithInv.push_back(item);
        }
        BlacksmithNewItems=false;
    }
}

void game::blacksmith(postac*& hero)
{
    while (true)
    {
        Time.timeFlow();
        updateBlacksmith();
        Time.printTime();
        itemRandomize(hero, gen);
        if (areShopsOpen())
        {
            if (blacksmithInv.empty())
            {
                std::cout << "The blacksmith currently has no items for sale. Returning to previous menu.\n";
                getch();
                break;
            }
            clearScreen();
            std::cout<<"Blacksmith"<<"\nA place where you can buy new equipment."<<std::endl;
            std::cout<<"\nWhat do you want to do?\n"
            <<"\n1. Buy Items"
            <<"\n2. Inventory"
            <<"\n\n0. Go back to the city."
            <<"\n\n\n-------------------------------------------------------------------------------\n"
            <<"\tMoney: "<<hero->currentgold<< " Gold Coins\t\t Current HP: "<< hero->currenthp <<std::endl;
            int dest;
            while (true)
            {
                std::cin>>dest;
                if(dest<=2||dest>=0)
                    break;
            }
            if (dest==0)
            {
                setLocation(Location::City);
                std::cout << "\nReturning to the city"<<std::endl;
                getch();
                clearScreen();
                break;
            }
            else if (dest==1)
            {
                itemBuy(hero);
            }
            else if(dest==2)
            {
                inventoryMenagment(hero);
            }
        }
        else
        {
            std::cout<<"Blacksmith is currently closed. Come back tommorow."<<std::endl;
        }
    }
}

void game::itemBuy(postac*& hero)
{
    while (true)
    {
        if (blacksmithInv.empty())
        {
            getch();
            continue;
        }
        clearScreen();
        std::cout<<"Items List:\n"<<std::endl;
        for(size_t i=0; i<blacksmithInv.size(); i++)
        {
            itemStats stats=blacksmithInv[i].getStats();
            std::cout<<"\n"<<i+1<<". "<<stats.name<<" (";
            if(stats.hp!=0)
                std::cout<<"HP: "<<stats.hp<<", ";
            if(stats.def!=0)
                std::cout<<"DEF: "<<stats.def<<", ";
            if(stats.ad!=0)
                std::cout<<"AD: "<<stats.ad<<", ";
            if(stats.mana!=0)
                std::cout<<"Mana: "<<stats.mana<<", ";
            if(stats.speed!=0)
                std::cout<<"Speed: "<<stats.speed;
            std::cout<<") Price: "<<stats.price<<std::endl;
        }

        std::cout<<"\n\n0. Go back."
        <<"\n\n\n-------------------------------------------------------------------------------\n"
        <<"\tMoney: "<<hero->currentgold<< " Gold Coins\t\t Current HP: "<< hero->currenthp <<"\n\n"<<std::endl;
        hero->displayInv();
        hero->displayEqp();
        size_t dest;
        while (true)
        {
            std::cin>>dest;
            if (dest>=0&&dest<=blacksmithInv.size())
                break;
        }
        if(dest==0)
        {
            setLocation(Location::Blacksmith);
            getch();
            clearScreen();
            break;
        }
        else if(dest>0&&blacksmithInv.size()>=1)
        {
            itemStats stats=blacksmithInv[dest-1].getStats();
            if (stats.price<=hero->currentgold)
            {
                hero->currentgold-=stats.price;
                std::cout<<"You have Bought "<<stats.name<<". Item added to your inventory.";
                hero->addToInv(blacksmithInv[dest-1]);
                blacksmithInv.erase(blacksmithInv.begin()+(dest-1));
            }
            else
                std::cout<<"You dont have enough money."<<std::endl;
            getch();
        }
    }
}

void game::inventoryMenagment(postac*& hero)
{
    while (true)
    {
        clearScreen();
        int eq;
        std::cout<<"------------==INVENTORY==------------\n\n"
        <<"\tMoney: "<<hero->currentgold<< " Gold Coins\t\t Current HP: "<< hero->currenthp
        <<"\n\n\n-------------------------------------------------------------------------------\n\n"
        <<"1. Equip\n2. Unequip\n\n0. Return\n\n"
        <<"-------------------------------------------------------------------------------\n\n"
        <<"\tPotions in Inventory:\n\n\t\t1. Instant Health Potion: x"<<hero->getHPpot()
        << "\n\t\t2. Potion of Regeneration: x"<< hero->getHPRegpot()<<std::endl;
        if (hero->getLvl()>=5)
            std::cout << "\t\t3. Potion of Mana Regeneration: x"<< hero->getManapot() <<std::endl;
        if (hero->getLvl()>=10)
            std::cout << "\t\t4. Potion of Fast Action: x"<< hero->getActionpot() <<std::endl;
        std::cout<<"\n\n-------------------------------------------------------------------------------\n\n";
        hero->displayEqp();
        std::cout<<"\n\n-------------------------------------------------------------------------------\n\n";
        hero->displayInv();
        while (true)
        {
            std::cin>>eq;
            if(eq>=0&&eq<=2)
                break;
        }
        if (eq==0)
        {
            std::cout<<"\nReturning..."<<std::endl;
            getch();
            clearScreen();
            break;
        }
        else if(eq==1)
        {
            int index;
            getch();
            clearScreen();
            std::cout<<"Choose item that you want to equip:\n\n0. Cancel\n"<<std::endl;
            hero->displayInv();
            while (true)
            {
                std::cin>>index;
                if(index>=0&&index<=hero->getInvSize())
                    break;
            }
            if(index!=0)
                hero->equip(index);
            getch();
            clearScreen();
        }
        else if(eq==2)
        {
            int index;
            getch();
            clearScreen();
            std::cout<<"Choose item that you want to unequip:\n"<<std::endl;
            hero->displayEqp();
            while (true)
            {
                std::cin>>index;
                if(index>=1&&index<=8)
                    break;
            }
            if(!hero->checkIfEqp(index))
                std::cout<<"\nNo item in that slot.";
            else
                hero->unequip(hero->getItemByIndex(index));
            getch();
            clearScreen();
        }
    }
}

bool game::mainMenu(postac*& hero)
{
    while (true)
    {
        clearScreen();
        std::cout<<"Welcome To \"The Arcane Trials: Pray, Fight, Repeat\"\n\nChoose an option:\n\n1. Continue\n2. New Game\n3. Load Game\n\n0. Exit"<<std::endl;
        int menu;
        std::cin >> menu;
        if (menu == 1)
        {
            if(hero!=nullptr)
                setLocation(Location::Map);
            else
            {
                clearScreen();
                std::cout<<"Your character is not loaded yet.\n\nLoad existing save or start a new game."<<std::endl;
                getch();
            }
            clearScreen();
            break;
        }
        else if (menu==2)
        {
            getch();
            clearScreen();
            std::string name1;
            std::cout << "\nName your character: ";
            std::cin >> name1;

            int klasa;
            while (true)
            {
                std::cout << "\nChoose character's class:\n\n1. Warrior\n2. Mage\n3. Archer"<<std::endl;
                std::cin >> klasa;
                if (klasa == 1)
                {
                    stats stat = {1, 18, 8, 9, 10, 1};
                    hero = new Warrior(name1, stat);
                    break;
                }
                if (klasa == 2)
                {
                    stats stat = {1, 13, 12, 7, 10, 1};
                    hero = new Mage(name1, stat);
                    break;
                }
                if (klasa == 3)
                {
                    stats stat = {1, 14, 10, 8, 8, 2};
                    hero = new Archer(name1, stat);
                    break;
                }
                else
                {
                    std::cout << "\nInvalid class. Please choose again." << std::endl;
                }
            }
            Time.resetTime();
            lvl0(hero);
            getch();
            clearScreen();
            break;
        }
        else if(menu==3)
        {
            getch();
            clearScreen();
            int saveslot;
            std::cout<<"Choose save that you want to load:\n1. Save 1\n2. Save 2\n3. Save 3\n\n4. Exit"<<std::endl;
            std::cin>>saveslot;
            if (saveslot==1)
            {
                const std::string filename = "saves/saveFile1.txt";
                if(hero->load_from_file(filename, hero))
                {
                    if(hero->prologueState())
                        setLocation(Location::City);
                    else
                        lvl0(hero);
                    break;
                }
            }
            else if (saveslot==2)
            {
                const std::string filename="saves/saveFile2.txt";
                if(hero->load_from_file(filename, hero))
                {
                    if(hero->prologueState())
                        setLocation(Location::City);
                    else
                        lvl0(hero);
                    break;
                }
            }
            else if (saveslot==3)
            {
                const std::string filename = "saves/saveFile3.txt";
                if(hero->load_from_file(filename, hero))
                {
                    if(hero->prologueState())
                        setLocation(Location::City);
                    else
                        lvl0(hero);
                    break;
                }
            }
            else if (saveslot==4)
            {
                break;
            }
            Time.resetTime();
        }
        else if(menu==0)
        {
            return true;
            break;
        }
    }
    return false;
}

void game::worldMap(postac*& hero)
{
    while (true)
    {
        Time.timeFlow();
        Time.printTime();
        std::cout<<"Chose your destination:\n\n0. Main Menu\n\n1. City"
        <<"\n2. Whispering Woods "<<isUnlockedPrint(Location::Forest)
        <<"\n3.(TBA) Mud-flooded Swamp "<<isUnlockedPrint(Location::Swamp)
        <<"\n4.(TBA) Howling Maw Cavern "<<isUnlockedPrint(Location::Caves)
        <<"\n5.(TBA) Ice Peaks "<<isUnlockedPrint(Location::IcePeaks)
        <<"\n6.(TBA) Lava-Flooded Volcano "<<isUnlockedPrint(Location::Volcano)
        <<"\n7.(TBA) Unholy Graveyard "<<isUnlockedPrint(Location::Graveyard)
        <<"\n8.(TBA) Ocean of Trial "<<isUnlockedPrint(Location::Ocean)<<std::endl;
        int loc;
        std::cin>>loc;
        if(loc==0)
        {
            setLocation(Location::MainMenu);
            getch();
            clearScreen();
            break;
        }
        if(loc==1)
        {
            setLocation(Location::City);
            std::cout<<"You have entered to the city."<<std::endl;
            getch();
            clearScreen();
            break;
        }
        else if(loc==2)
        {
            setLocation(Location::Forest);
            std::cout<<"You have entered to Whispering Woods. Watch out for what hides in the shadows..."<<std::endl;
            forest(hero);
            clearScreen();
            break;
        }
        else if(loc==3&&isUnlocked(Location::Caves))
        {
            setLocation(Location::Caves);
            std::cout<<"You have entered to the Howling Maw Cavern."<<std::endl;
            getch();
            clearScreen();
            break;
        }
        else if(loc==3&&!isUnlocked(Location::Caves))
        {
            std::cout<<"Location Locked."<<std::endl;
            getch();
            clearScreen();
        }
        else if(loc==4&&isUnlocked(Location::IcePeaks))
        {
            setLocation(Location::IcePeaks);
            std::cout<<"You have entered the Ice Peaks."<<std::endl;
            getch();
            clearScreen();
            break;
        }
        else if(loc==4&&!isUnlocked(Location::IcePeaks))
        {
            std::cout<<"Location Locked."<<std::endl;
            getch();
            clearScreen();
        }
        else if(loc==5&&isUnlocked(Location::Volcano))
        {
            setLocation(Location::Volcano);
            std::cout<<"You have entered the Lava-Flooded Volcano."<<std::endl;
            getch();
            clearScreen();
            break;
        }
        else if(loc==5&&!isUnlocked(Location::Volcano))
        {
            std::cout<<"Location Locked."<<std::endl;
            getch();
            clearScreen();
        }
        else if(loc==6&&isUnlocked(Location::Graveyard))
        {
            setLocation(Location::Graveyard);
            std::cout<<"You have entered to the Unholy Graveyard."<<std::endl;
            getch();
            clearScreen();
            break;
        }
        else if(loc==6&&!isUnlocked(Location::Graveyard))
        {
            std::cout<<"Location Locked."<<std::endl;
            getch();
            clearScreen();

        }
        else if(loc==7&&isUnlocked(Location::Ocean))
        {
            setLocation(Location::Ocean);
            std::cout<<"You have entered the Ocean of Trial."<<std::endl;
            getch();
            clearScreen();
            break;
        }
        else if(loc==7&&!isUnlocked(Location::Ocean))
        {
            std::cout<<"Location Locked."<<std::endl;
            getch();
            clearScreen();
        }
    }
}

void game::city(postac*& hero)
{
    clearScreen();
    if(hero->cityState())
    {
        getch();
        std::cout<<"Welcome to the city of Omphalos!\n"<<std::endl;
        getch();
        std::cout<<"This will be your central hub, where you'll return after every batlle to rest, upgrade you gear and prepare for challenges ahead.\n"<<std::endl;
        getch();
        std::cout<<"The city has few key locations important for your progress."<<std::endl;
        getch();
        hero->citySet(false);
    }
    while(true)
    {
        clearScreen();
        Time.timeFlow();
        Time.printTime();
        std::cout<<"You have entered the city. \n\nChoose your destination:\n"<<std::endl;
        std::cout<<"\n1. Map\n2. Church\n3. Blacksmith\n4.(TBA) Witch Hut\n5. Tavern\n6.(TBA) Arena"<<std::endl;
        int loc;
        std::cin>>loc;
        if (loc==1)
        {
            setLocation(Location::Map);
            getch();
            clearScreen();
            break;
        }
        else if(loc==2)
        {
            std::cout << "Entering to the church..."<<std::endl;
            setLocation(Location::Church);
            getch();
            clearScreen();
            church(hero);
            break;
        }
        else if(loc==3)
        {
            std::cout << "Entering the forge..."<<std::endl;
            setLocation(Location::Blacksmith);
            getch();
            clearScreen();
            blacksmith(hero);
            break;
        }
        else if(loc==4)
        {
            std::cout << "\nTBA"<<std::endl;
            getch();
            clearScreen();
        }
        else if(loc==5)
        {
            std::cout << "Entering to the tavern..."<<std::endl;
            setLocation(Location::Tavern);
            getch();
            clearScreen();
            tavern(hero);
            break;
        }
        else if(loc==6)
        {
            std::cout << "\nTBA"<<std::endl;
            getch();
            clearScreen();
        }
    }
}

void game::potionMenu(postac*& hero)
{
    while (true)
    {
        clearScreen();
        int potion;
        std::cout<<"What Potion do you want to drink?\n\n1. Instant Health Potion (in inventory: "<<hero->getHPpot()<<")\n2. Potion of Regeneration (in inventory: "<<hero->getHPRegpot()<<")"<<std::endl;
        if (hero->getLvl()>=5)
            std::cout<<"3. Potion of Mana Regeneration(in inventory: "<<hero->getManapot()<<")"<<std::endl;
        if(hero->getLvl()>=10)
            std::cout<<"4. Potion of Fast Action (in inventory: "<<hero->getActionpot()<<")"<<std::endl;
        std::cout<<"\n\n0. \"I don't want to drink a potion.\""<<std::endl;
        std::cin>>potion;
        if(potion==1)
        {
            clearScreen();
            if(hero->getHPpot()>0)
            {
                int x=hero->currenthp;
                std::cout << "You have drunk Instant Health potion."<<std::endl;
                hero->instaHP();
                std::cout << "You have regenerated "<<(hero->currenthp-x) <<" HP."<<std::endl;
                hero->setPotionCD();
                hero->setHPpot(-1);
                break;
            }
            else
            {
                std::cout << "You don't have any Instant Health Potion."<<std::endl;
            }
        }
        else if(potion==2)
        {
            clearScreen();
            if(hero->getHPRegpot()>0)
            {
                std::cout << "You have drunk Potion of Regeneration."<<std::endl;
                hero->setPotionCD();
                hero->setHPRegpot(-1);
                hero->setHPRegpotT(PotionTime);
                break;
            }
            else
            {
                std::cout << "You don't have any Potion of Regeneration."<<std::endl;
            }
        }
        else if(potion==3&&hero->getLvl()>=5)
        {
            clearScreen();
            if(hero->getManapot()>0)
            {
                std::cout << "You have drunk Potion of Mana Regeneration."<<std::endl;
                hero->setPotionCD();
                hero->setManapot(-1);
                hero->setManapotT(PotionTime);
                break;
            }
            else
            {
                std::cout << "You don't have any Potion of Mana Regeneration."<<std::endl;
            }
        }
        else if(potion==4&&hero->getLvl()>=10)
        {
            clearScreen();
            if(hero->getActionpot()>0)
            {
                std::cout << "You have drunk Potion of Fast Action."<<std::endl;
                hero->setPotionCD();
                hero->setActionpot(-1);
                hero->setFastAction(true);
                break;
            }
            else
            {
                std::cout << "You don't have any Potion of Fast Action."<<std::endl;
            }
        }
        else if(potion==0)
            break;
    }
}

void game::heroaction(postac*& enemy, postac*& hero)
{
    for(int i=0; i<2; i++)
    {
        if(!hero->getFastAction())
            i++;
        int atktype;

        while (true)
        {
            clearScreen();
            std::cout<<std::endl;
            hero->printstatcurrent();
            std::cout<<"\n\nChoose your attack type:\n\n1. Weak (95%)\n2. Normal (75%)\n3. Strong (50%)"<<std::endl;
            std::cin>>atktype;
            if((atktype>=1)&&(atktype<=3))
                break;
        }
        hero->atktypenb=atktype;
        if (hero->getClass()=="Mage")
        {
            enemy->getDamaged(hero, DamageType::MagicEnergy);
        }
        else
        {
            enemy->getDamaged(hero, DamageType::Physical);
        }
    }
    hero->setFastAction(false);
}

void game::enemyaction(postac*& enemy, postac*& hero)
{
    if (enemy == nullptr)
        return;
    if (enemy->getClass()=="enemyMage")
        hero->getDamaged(enemy, DamageType::MagicEnergy);
    else
        hero->getDamaged(enemy, DamageType::Physical);
    getch();
}

int game::fight3(postac*& hero, postac*& enemy1, postac*& enemy2, postac*& enemy3)
{
    std::vector<postac*> enemies={enemy1, enemy2, enemy3};
    std::vector<postac*> turn={enemy1, enemy2, enemy3, hero};
    std::sort(turn.begin(), turn.end(), [](postac* a, postac* b)
    {
        if (a == nullptr)
            return false;
        if (b == nullptr)
            return true;
        return a->getSpeed() > b->getSpeed();
    });

    while (hero->currenthp>0)
    {

        hero->regen();
        if (hero->getHPRegpotT()>0)
        {
            hero->potionregen();
            hero->setHPRegpotT(-1);
        }
        if(hero->getManapotT()>0)
        {
            hero->manaregen();
            hero->setManapotT(-1);
        }
        while (true)
        {
            clearScreen();
            int action;
            std::cout<<"Choose your action:\n\n1. Attack"<<std::endl;
            if(hero->getPotionCD()==0&&hero->getLvl()>=2)
                std::cout<<"2. Drink Potion"<<std::endl;
            std::cin >>action;
            int enemynb;
            if(action==1)
            {
                if(enemies.size()>=2)
                {
                    while(true)
                    {
                        std::cout<<"\nChoose enemy to attack:"<<std::endl;

                        for (size_t i = 0; i < enemies.size(); ++i)
                        {
                            if (enemies[i] != nullptr)
                            {
                                std::cout << i + 1 << ". " << enemies[i]->getName()
                                          << " (current HP: " << enemies[i]->currenthp << ")" << std::endl;
                            }
                        }
                        std::cin>>enemynb;
                        if(enemies.size()==2&&(enemynb==1||enemynb==2))
                            break;
                        else if(enemies.size()==3&&(enemynb==1||enemynb==2||enemynb==3))
                            break;
                        getch();
                        clearScreen();
                    }
                }
                else
                    enemynb=1;

                if (enemies[0] != nullptr)
                    enemies[0]->atktypenb = std::rand() % 3 + 1;
                if (enemies[1] != nullptr)
                    enemies[1]->atktypenb = std::rand() % 3 + 1;
                if (enemies[2] != nullptr)
                    enemies[2]->atktypenb = std::rand() % 3 + 1;

                for (size_t turnnb = 0; turnnb<turn.size();turnnb++)
                {
                    if (turn[turnnb] == hero)
                    {
                        heroaction(enemies[enemynb-1], hero);
                        getch();
                        if (enemies[enemynb-1]->currenthp<=0)
                        {
                            std::cout<<std::endl;
                            hero->printstatcurrent();
                            std::cout<<std::endl;
                            fightEnd(hero, enemies[enemynb-1]);

                            enemies[enemynb-1]->printstatcurrent();
                            enemies[enemynb-1]=nullptr;
                            enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](postac* character)
                            {
                                return character == nullptr || character->currenthp <= 0;
                            }), enemies.end());
                            turn.erase(std::remove_if(turn.begin(), turn.end(), [](postac* character)
                            {
                                return character == nullptr || character->currenthp <= 0;
                            }), turn.end());

                            if (std::all_of(enemies.begin(), enemies.end(), [](postac* e) { return e == nullptr; }))
                            {
                                hero->setFastAction(false);
                                hero->setHPRegpotT(-hero->getHPRegpotT());
                                hero->setManapotT(-hero->getManapotT());
                                return 1;
                            }
                        }

                        getch();
                        if(hero->currenthp<=0)
                        {
                            hero->setFastAction(false);
                            hero->setHPRegpotT(-hero->getHPRegpotT());
                            hero->setManapotT(-hero->getManapotT());
                            return 0;
                        }
                    }
                    else if (turn[turnnb] != nullptr)
                    {
                        enemyaction(turn[turnnb], hero);
                        if(hero->currenthp<=0)
                        {
                            return 0;
                        }
                    }
                }
                break;
            }
            else if(action==2&&hero->getPotionCD()==0&&hero->getLvl()>=2)
            {
                potionMenu(hero);
            }
        }
    }
    return 0;
}