#include <charconv>
#include "game.h"
#include "enemyWarrior.h"
#include "enemyArcher.h"
#include "enemyMage.h"
#include <vector>
#include <algorithm>
#include <button.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <fstream>
#include "Slider.h"
#define PotionTime 3


extern std::unordered_map<int, enemyStats> enemies;


character* game::createEnemy (const enemyStats& stats) {
    switch (stats.Class) {
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

bool game::areShopsOpen () const {
    if (Time.gettime() >= 480 && Time.gettime() < 1320)
        return true;
    return false;
}

void game::loss (character*& hero) {
    std::cout << "You have fainted." << std::endl;
    std::cout << "Luckily someone found you and brought you to the church, but he wanted half of your gold in exchange."
            << std::endl;
    setLocation(Location::Church);
    hero->currentgold -= hero->currentgold / 2;
    hero->pray();
}

bool game::retcity () {
    int ret;
    while (true) {
        std::cout << "Do you want to return to the city, or search for next foe?" << "\n1. Stay\n2. Return to the city"
                << std::endl;
        std::cin >> ret;
        if (ret == 1 || ret == 2)
            break;
    }
    if (ret == 1)
        return false;
    else {
        setLocation(Location::City);
        return true;
    }
}

// bool game::enemyenc(int indexmin, int indexmax, int exp, int gold, int maxlvl, postac*& hero)
// {
//     std::uniform_int_distribution<> dist(indexmin, indexmax);
//     int index = dist(gen);
//     postac* enemy=createEnemy(enemies.at(index));
//     enemy->setExpworth(exp);
//     enemy->setGoldworth(gold);
//     while(enemy->getLvl()<hero->getLvl()||enemy->getLvl()>=maxlvl)
//     {
//         enemy->enemyLvlUp();
//     }
//     int res = fight(hero, enemy);
//     if(res==0)
//     {
//         loss(hero);
//         delete enemy;
//         return false;
//     }
//     delete enemy;
//     if (retcity())
//         return false;
//     return true;
// }

// bool game::enemyenc3(int indexmin, int indexmax, int exp, int gold, int maxlvl, postac*& hero)
// {
//     std::uniform_int_distribution<> dist(indexmin, indexmax);
//     int index = dist(gen);
//     postac* enemy1=createEnemy(enemies.at(index));
//     enemy1->setExpworth(exp);
//     enemy1->setGoldworth(gold);
//     while(enemy1->getLvl()<hero->getLvl()||enemy1->getLvl()>=maxlvl)
//     {
//         enemy1->enemyLvlUp();
//     }
//     index = dist(gen);
//     postac* enemy2=createEnemy(enemies.at(index));
//     enemy2->setExpworth(exp);
//     enemy2->setGoldworth(gold);
//     while(enemy2->getLvl()<hero->getLvl()||enemy2->getLvl()>=maxlvl)
//     {
//         enemy2->enemyLvlUp();
//     }
//     index = dist(gen);
//     postac* enemy3=createEnemy(enemies.at(index));
//     enemy3->setExpworth(exp);
//     enemy3->setGoldworth(gold);
//     while(enemy3->getLvl()<hero->getLvl()||enemy3->getLvl()>=maxlvl)
//     {
//         enemy3->enemyLvlUp();
//     }
//     std::cout<<"Watch out! You have been attacked by "<<enemy1->getName()<<" (Lvl "<< enemy1->getLvl()<<")"
//     <<enemy2->getName()<<" (Lvl "<< enemy2->getLvl()<<")"
//     <<enemy3->getName()<<" (Lvl "<< enemy3->getLvl()<<")!"<<std::endl;
//
//
//     int res = fight3(hero, enemy1, enemy2, enemy3);
//     if(res==0)
//     {
//         loss(hero);
//         delete enemy1;
//         delete enemy2;
//         delete enemy3;
//         return false;
//     }
//     delete enemy1;
//     delete enemy2;
//     delete enemy3;
//     if (retcity())
//         return false;
//     return true;
// }

void game::lvl0 (character*& hero, sf::RenderWindow* window) {
    std::cout << "Currently playing: Tutorial" << std::endl;
    character* enemy1 = createEnemy(enemies.at(0));
    enemy1->setExpworth(18);
    enemy1->setGoldworth(10);


    std::cout <<
            "One day when you have been laying under an old oak tree in the middle of plains nearby the city you heard loud crack and scream..."
            << std::endl;

    std::cout << "\nYou rushed to the source of all that noise to see what is going on." << std::endl;

    std::cout << "\nYou found the King, whose carriage just broke down. The king seemed distressed so you came closer."
            << std::endl;

    std::cout <<
            "\nThe King got attacked by a bunny. But there was something wrong with that bunny... You came to help and then the Killer Bunny attacked you."
            << std::endl;

    int fight1 = fight(hero, 0, window);
    if (fight1 == 0) {
        hero->prologueSet(true);
        std::cout << "Sadly you have been badly injured by your enemy." << std::endl;
        std::cout << "\nLuckily King's guards came in time to save both you and the King." << std::endl;
        std::cout << "\nBut won or lost, this fight taught you various things. You gain 6XP." << std::endl;
        hero->exp += 6;
        hero->lvlup();
        std::cout << "You have been brought to the church." << std::endl;
        std::cout << "\nMonks took care of u and you made a full recovery." << std::endl;
        std::cout << "\nKing paid for all of the expenses and gave you 20 Gold Coins as a reward for your bravery." <<
                std::endl;
        std::cout << "\nBut remember that it won't happen again." << std::endl;
        hero->currentgold += 20;
        hero->pray();
    }
    // else
    // {
    //     std::cout<<"Watch out! New wave of enemies incoming!"<<std::endl;
    //     postac* enemy2 = createEnemy(enemies.at(1));
    //     postac* enemy3 = createEnemy(enemies.at(2));
    //     postac* enemy4 = createEnemy(enemies.at(3));
    //     int fight2=fight3(hero,enemy2,enemy3,enemy4);
    //     if (fight2==0)
    //     {
    //         hero->prologueSet(true);
    //         std::cout<<"Sadly you have been badly injured by your enemies."<<std::endl;
    //         std::cout<<"\nLuckily King's guards came in time to save both you and the King."<<std::endl;
    //         std::cout<<"You have been brought to the church."<<std::endl;
    //         std::cout<< "\nMonks took care of u and you made a full recovery." <<std::endl;
    //         std::cout<<"\nKing paid for all of the expenses and gave you 20 Gold Coins as a reward for your bravery." <<std::endl;
    //         std::cout<<"\nBut remember that it won't happen again."<<std::endl;
    //         hero->currentgold+=20;
    //         hero->pray();
    //     }
    //     else
    //     {
    //         hero->prologueSet(true);
    //         std::cout<<"\nKing's guards came to save both you and the King."<<std::endl;
    //         std::cout<<"\nThey escorted you to the city."<<std::endl;
    //         std::cout<<"\nKing thanked you and gave you 20 Gold Coins as a reward for your bravery." <<std::endl;
    //         std::cout<<"\nThe King departed with his guards towards the castle."<<std::endl;
    //         hero->currentgold+=20;
    //     }
    //     delete enemy2;
    //     delete enemy3;
    //     delete enemy4;
    // }
    setLocation(Location::City);
    hero->citySet(true);
    hero->churchSet(true);
    hero->tavernSet(true);
    hero->blacksmithSet(true);
    hero->mapSet(true);
    delete enemy1;
    Time.resetTime();
}

// void game::forest(postac*& hero)
// {
//     if(!enemyenc(4, 6, 6, 10, 10, hero))
//         return;
//     if(!enemyenc(4, 6, 6, 10, 10, hero))
//         return;
//     if(!enemyenc(4, 8, 10, 15, 10, hero))
//         return;
//     if(!enemyenc(4, 8, 10, 15, 10, hero))
//         return;
//     std::cout<<"Huge wave of enemies ahead!"<<std::endl;
//     if(!enemyenc3(9, 12, 14, 20, 10, hero))
//         return;
//     if(!enemyenc(7, 12, 14, 20, 10, hero))
//         return;
//     if(!enemyenc(7, 12, 14, 20, 10, hero))
//         return;
//     if(!enemyenc(7, 12, 14, 20, 10, hero))
//         return;
//     if(!enemyenc(7, 12, 14, 20, 10, hero))
//         return;
//     if(!enemyenc(13, 13, 22, 30, 10, hero))
//         return;
//     if(!isUnlocked(Location::Swamp))
//     {
//         unlockLocations(Location::Swamp);
//         std::cout<<"You have unlocked swamp. Are you scared to get yourself dirty?"<<std::endl;
//     }
//     std::cout<<"You have come to the edge of the forest, slaying all enemies that stood on you way.\n\nReturning to the city now." <<std::endl;
// }

void game::heroaction (character*& enemy, character*& hero) {
    if (hero->getClass() == "Mage") {
        enemy->getDamaged(hero, DamageType::MagicEnergy);
    }
    else {
        enemy->getDamaged(hero, DamageType::Physical);
    }
    hero->setFastAction(false);
}

void game::enemyaction (character*& enemy, character*& hero) {
    if (enemy == nullptr)
        return;
    if (enemy->getClass() == "enemyMage")
        hero->getDamaged(enemy, DamageType::MagicEnergy);
    else
        hero->getDamaged(enemy, DamageType::Physical);
}

int game::fight (character*& hero, int enemyID, sf::RenderWindow* window) {
    AllTimeGUI gui(hero);
    sf::Clock clock;
    character* enemy = createEnemy(enemies.at(enemyID));
    int whofirst;
    int potionCD = 0;
    bool heroAction = false;
    bool heroChosen = false;
    bool regenHandled = true;
    bool turnHero = false;
    bool turnEnemy = false;
    if ((hero->getSpeed()) > (enemy->getSpeed()))
        whofirst = 1;
    if ((hero->getSpeed()) < (enemy->getSpeed()))
        whofirst = 0;
    if ((hero->getSpeed()) == (enemy->getSpeed()))
        whofirst = std::rand() % 2;
    if (whofirst == 1)
        heroAction = true;

    while (hero->currenthp > 0 && window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window->close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            if (gui.atk1IsClicked(mousePos) && !heroChosen && heroAction) {
                hero->atktypenb = 1;
                heroChosen = true;
            }
            else if (gui.atk1IsClicked(mousePos) && !heroChosen && heroAction) {
                hero->atktypenb = 2;
                heroChosen = true;
            }
            else if (gui.atk1IsClicked(mousePos) && !heroChosen && heroAction) {
                hero->atktypenb = 3;
                heroChosen = true;
            }
            else if (gui.actionIsClicked(mousePos) && !heroChosen && heroAction && hero->getActionpot() > 0) {
                hero->setFastAction(true);
                hero->setActionpot(-1);
                potionCD = 4;
            }
            else if (gui.regenIsClicked(mousePos) && !heroChosen && heroAction && hero->getHPRegpot() > 0) {
                hero->setHPRegpot(-1);
                hero->setHPRegpotT(PotionTime);
                potionCD = 4;
            }
            else if (gui.manaIsClicked(mousePos) && !heroChosen && heroAction && hero->getManapot() > 0) {
                hero->setManapot(-1);
                hero->setManapotT(PotionTime);
                potionCD = 4;
            }
            else if (gui.hpIsClicked(mousePos) && !heroChosen && heroAction && hero->getHPpot() > 0) {
                hero->setHPpot(-1);
                hero->instaHP();
                potionCD = 4;
            }
        }
        if (turnHero && turnEnemy) {
            regenHandled = false;
            turnHero = false;
            turnEnemy = false;
        }
        if (!regenHandled) {
            hero->regen();
            if (hero->getHPRegpotT() > 0) {
                hero->potionregen();
                hero->setHPRegpotT(-1);
            }
            if (hero->getManapotT() > 0) {
                hero->manaregen();
                hero->setManapotT(-1);
            }
            regenHandled = true;
        }
        if (heroAction && heroChosen) {
            if (!hero->getFastAction()) {
                heroAction = false;
                clock.restart();
                turnHero = true;
            }
            heroaction(enemy, hero);
            if (enemy->currenthp <= 0) {
                fightEnd(hero, enemy);
                hero->setFastAction(false);
                hero->setHPRegpotT(-hero->getHPRegpotT());
                hero->setManapotT(-hero->getManapotT());
                delete enemy;
                return 1;
            }
        }
        int elapsedTime = clock.getElapsedTime().asSeconds();
        if (!heroAction && elapsedTime >= 2) {
            enemy->atktypenb = rand() % 3;
            enemyaction(enemy, hero);
            heroAction = true;
            turnEnemy = true;
            if (hero->currenthp <= 0) {
                hero->setFastAction(false);
                hero->setHPRegpotT(-(hero->getHPRegpotT()));
                hero->setManapotT((-hero->getManapotT()));
                delete enemy;
                return 0;
            }
        }
        window->clear();
        window->draw(gui);
        window->display();
    }
    delete enemy;
    return 0;
}

void game::fightEnd (character*& hero, character*& enemy) {
    if (enemy->currenthp <= 0) {
        hero->exp += enemy->getExpworth();
        hero->goldInc(enemy->getGoldworth());
        hero->lvlup();
    }
}

void game::setLocation (Location newLocation) {
    currentLocation = newLocation;
}

Location game::getLocation () const {
    return currentLocation;
}

bool game::isUnlocked (Location location) const {
    return unlockedLocations.find(location) != unlockedLocations.end() && unlockedLocations.at(location);
}

std::string game::isUnlockedPrint (Location location) const {
    if (unlockedLocations.find(location) != unlockedLocations.end() && unlockedLocations.at(location))
        return "[Unlocked]";
    return "[Locked]";
}

void game::unlockLocations (Location locationToUnlock) {
    unlockedLocations[locationToUnlock] = true;
}

void game::updateBlacksmith () {
    if (Time.newDayBlacksith) {
        BlacksmithNewItems = true;
        Time.newDayBlacksith = false;
    }
    else
        BlacksmithNewItems = false;
}

void game::church (character*& hero, sf::RenderWindow* window) {
    while (true) {
        Time.timeFlow();
        Time.printTime();
        std::cout << "Church" << "\nA place where you can pray, or buy potions from humble monks." << std::endl;
        std::cout << "\nWhat do you want to do?\n" << "\n1. Pray for health. (5 Gold Coins)" << "\n2. Buy potions." <<
                "\n\n0. Go back to the city." <<
                "\n\n\n-------------------------------------------------------------------------------\n" << "\tMoney: "
                << hero->currentgold << " Gold Coins\t\t Current HP: " << hero->currenthp << std::endl;
        int dest;
        std::cin >> dest;
        if (dest == 1 && hero->currentgold >= 5) {
            hero->pray();
            std::cout << "You have prayed for your health. Gods bless you and regenerate your HP." << std::endl;
            hero->currentgold -= 5;
        }
        else if (dest == 1 && hero->currentgold < 5) {
            std::cout << "\nNot enough Gold Coins." << std::endl;
        }
        else if (dest == 2) {
            while (true) {
                std::cout << "What potion do you want to buy?" << std::endl;
                std::cout << "\n1. Instant Health Potion (20 Gold Coins)\n2. Potion of Regeneration (10 Gold Coins)" <<
                        std::endl;
                if (hero->getLvl() >= 5)
                    std::cout << "3. Potion of Mana Regeneration (30 Gold Coins)" << std::endl;
                if (hero->getLvl() >= 10)
                    std::cout << "4. Potion of Fast Action (80 Gold Coins)" << std::endl;
                std::cout << "\n\n0. \"I don't want a potion.\"" << std::endl;
                std::cout << "\n\n\n-------------------------------------------------------------------------------\n\n"
                        << "\tMoney: " << hero->currentgold << " Gold Coins\t\t Current HP: " << hero->currenthp <<
                        std::endl;
                std::cout << "\n\n\n-------------------------------------------------------------------------------\n\n"
                        << "\tPotions in Inventory:\n\n\t\t1. Instant Health Potion: x" << hero->getHPpot() <<
                        "\n\t\t2. Potion of Regeneration: x" << hero->getHPRegpot() << std::endl;
                if (hero->getLvl() >= 5)
                    std::cout << "\t\t3. Potion of Mana Regeneration: x" << hero->getManapot() << std::endl;
                if (hero->getLvl() >= 10)
                    std::cout << "\t\t4. Potion of Fast Action: x" << hero->getActionpot() << std::endl;

                int potionnb;
                while (true) {
                    std::cin >> potionnb;
                    if (potionnb == 1 && hero->currentgold >= 20) {
                        hero->currentgold -= 20;
                        hero->setHPpot(1);
                        std::cout << "You have bought an Instant Health Potion." << std::endl;


                        break;
                    }
                    else if (potionnb == 1 && hero->currentgold < 20) {
                        std::cout << "You don't have enough Gold Coins." << std::endl;


                        break;
                    }
                    else if (potionnb == 2 && hero->currentgold >= 10) {
                        hero->currentgold -= 10;
                        hero->setHPRegpot(1);
                        std::cout << "You have bought an Potion of Regeneration." << std::endl;


                        break;
                    }
                    else if (potionnb == 1 && hero->currentgold < 10) {
                        std::cout << "You don't have enough Gold Coins." << std::endl;


                        break;
                    }
                    else if (potionnb == 3 && hero->currentgold >= 30 && hero->getLvl() >= 5) {
                        hero->currentgold -= 80;
                        hero->setActionpot(1);
                        std::cout << "You have bought an Potion of Mana Regeneration." << std::endl;


                        break;
                    }
                    else if (potionnb == 3 && hero->currentgold < 30 && hero->getLvl() >= 5) {
                        std::cout << "You don't have enough Gold Coins." << std::endl;


                        break;
                    }
                    else if (potionnb == 4 && hero->currentgold >= 80 && hero->getLvl() >= 10) {
                        hero->currentgold -= 80;
                        hero->setActionpot(1);
                        std::cout << "You have bought an Potion of Fast Action." << std::endl;


                        break;
                    }
                    else if (potionnb == 4 && hero->currentgold < 80 && hero->getLvl() >= 10) {
                        std::cout << "You don't have enough Gold Coins." << std::endl;


                        break;
                    }
                    else if (potionnb == 0)
                        break;
                }
                if (potionnb == 0)
                    break;
            }
        }
        else if (dest == 0) {
            setLocation(Location::City);
            std::cout << "\nReturning to the city" << std::endl;


            break;
        }
    }
}

void game::tavern (character*& hero, sf::RenderWindow* window) {
    while (true) {
        Time.timeFlow();
        Time.printTime();

        std::cout << "Tavern" << "\nA place where you can rest (save the game), drink and accept missions." <<
                std::endl;
        std::cout << "\nWhat do you want to do?\n" << "\n1. Drink (1 Gold Coin)" << "\n2. Rest (5 Gold Coins)." <<
                "\n3. (TBA) Missions." << "\n\n4. Go back to the city." <<
                "\n\n\n-------------------------------------------------------------------------------\n" << "\tMoney: "
                << hero->currentgold << " Gold Coins\t\t Current HP: " << hero->currenthp << std::endl;
        int dest;
        std::cin >> dest;
        if (dest == 1 && hero->currentgold >= 1) {
            std::cout << "You drank a pint of beer." << std::endl;
            hero->currentgold -= 1;
        }
        else if (dest == 1 && hero->currentgold < 1) {
            std::cout << "\nNot enough Gold Coins." << std::endl;
        }
        else if (dest == 2 && hero->currentgold >= 5) {
            hero->currentgold -= 5;
            std::cout << "You lay down in bed to rest." << std::endl;
            hero->save_to_file(hero);
            setLocation(Location::City);
            break;
            Time.resetTime();
        }
        else if (dest == 2 && hero->currentgold < 5) {
            std::cout << "\nNot enough Gold Coins." << std::endl;
        }
        else if (dest == 3) {
            std::cout << "\nTBA" << std::endl;
        }
        else if (dest == 4) {
            setLocation(Location::City);
            std::cout << "\nReturning to the city" << std::endl;
            break;
        }
    }
}

void game::itemRandomize (character*& hero, std::mt19937& gen) {
    if (BlacksmithNewItems) {
        int min_id, max_id;
        blacksmithAvaiable.clear();
        if (hero->getClass() == "Warrior") {//&& hero->getLvl() <= 7
            min_id = 1;
            max_id = 20;
        }
        else if (hero->getClass() == "Mage") {//&& hero->getLvl() <= 7
            min_id = 21;
            max_id = 40;
        }
        else if (hero->getClass() == "Archer") {//&& hero->getLvl() <= 7
            min_id = 41;
            max_id = 60;
        }

        std::uniform_int_distribution<> dist(min_id, max_id);

        for (int i = 0; i < 6; i++) {
            int ItemId = dist(gen);
            Item item(ItemId);
            item.generateStats(gen, hero);
            blacksmithInv[i] = item;
            blacksmithAvaiable.push_back(i);
        }
        BlacksmithNewItems = false;
    }
}

void game::blacksmith (character*& hero, sf::RenderWindow* window) {
    updateBlacksmith();
    itemRandomize(hero, gen);

    sf::Texture blacksmith_bg;
    if (!blacksmith_bg.loadFromFile("src\\textures\\GUI\\gui_blacksmith.png")) {
        std::cerr << "Failed to load texture from file: src\\textures\\GUI\\gui_blacksmith.png" << std::endl;
        throw std::runtime_error("Failed to load texture from file: src\\textures\\GUI\\gui_blacksmith.png");
    }
    sf::Texture hoverFrame;
    if (!hoverFrame.loadFromFile("src\\textures\\GUI\\192x80border.png")) {
        std::cerr << "Failed to load texture from file: src\\textures\\GUI\\192x80border.png" << std::endl;
        throw std::runtime_error("Failed to load texture from file: src\\textures\\GUI\\192x80border.png");
    }
    sf::Sprite blacksmith_background(blacksmith_bg);
    sf::Sprite hover_frame(hoverFrame);
    blacksmith_background.scale({scale, scale});
    hover_frame.scale({scale, scale});

    AllTimeGUI gui(hero);

    Button arrow_l(281.f, 95.f, "src\\textures\\GUI\\arrow_key_left.png");
    Button arrow_r(588.f, 95.f, "src\\textures\\GUI\\arrow_key_right.png");
    Button back(593.f, 44.f, "src\\textures\\GUI\\x.png");

    std::vector<Button> items;
    int startX = 377;
    int startY = 199;
    int spacingX = 49;
    int spacingY = 49;
    for (int i = 0; i < 6; ++i) {
        int x = startX + (i % 3) * spacingX;
        int y = startY + (i / 3) * spacingY;
        items.emplace_back(x, y, blacksmithInv[i].getPath());
    }

    std::vector<Button> inventory;
    int startXinv = 304;
    int startYinv = 91;
    int spacingXinv = 49;
    for (int i = 0; i < hero->getInvSize(); ++i) {
        int x = startXinv + spacingXinv * i;
        if (hero->getItemFromInventory(i).getId() > 0)
            items.emplace_back(x, startYinv, hero->getItemFromInventory(i).getPath());
        else
            items.emplace_back(x, startYinv, "src\\textures\\items\\Buty.png");
    }


    std::vector<std::string> texts;
    for (int i = 0; i < 6; ++i) {
        texts.push_back(blacksmithInv[i].getData());
    }

    std::vector<std::string> texts_inv;
    for (int i = 0; i < hero->getInvSize(); ++i) {
        if (hero->getItemFromInventory(i).getId() > 0) {
            texts_inv.push_back(hero->getItemFromInventory(i).getData());
            texts.push_back(Item(0).getData());
        }
    }

    std::vector<std::pair<bool, Button>> eqp;
    std::vector<std::string> texts_eqp;
    if (hero->checkIfEqp(itemType::Helmet)) {
        eqp.emplace_back(true, Button(59.f, 91.f, hero->getItemFromEqp(itemType::Helmet).getPath()));
        texts_eqp.push_back(hero->getItemFromEqp(itemType::Helmet).getData());
    }
    else {
        eqp.emplace_back(false, Button(59.f, 91.f, Item(0).getPath()));
        texts_eqp.push_back(Item(0).getData());
    }
    if (hero->checkIfEqp(itemType::Chestplate)) {
        eqp.emplace_back(true, Button(59.f, 140.f, hero->getItemFromEqp(itemType::Chestplate).getPath()));
        texts_eqp.push_back(hero->getItemFromEqp(itemType::Chestplate).getData());
    }
    else {
        eqp.emplace_back(false, Button(59.f, 140.f, Item(0).getPath()));
        texts_eqp.push_back(Item(0).getData());
    }
    if (hero->checkIfEqp(itemType::Leggings)) {
        eqp.emplace_back(true, Button(59.f, 189.f, hero->getItemFromEqp(itemType::Leggings).getPath()));
        texts_eqp.push_back(hero->getItemFromEqp(itemType::Leggings).getData());
    }
    else {
        eqp.emplace_back(false, Button(59.f, 189.f, Item(0).getPath()));
        texts_eqp.push_back(Item(0).getData());
    }
    if (hero->checkIfEqp(itemType::Necklace)) {
        eqp.emplace_back(true, Button(238.f, 91.f, hero->getItemFromEqp(itemType::Necklace).getPath()));
        texts_eqp.push_back(hero->getItemFromEqp(itemType::Necklace).getData());
    }
    else {
        eqp.emplace_back(false, Button(238.f, 91.f, Item(0).getPath()));
        texts_eqp.push_back(Item(0).getData());
    }
    if (hero->checkIfEqp(itemType::Gloves)) {
        eqp.emplace_back(true, Button(238.f, 140.f, hero->getItemFromEqp(itemType::Gloves).getPath()));
        texts_eqp.push_back(hero->getItemFromEqp(itemType::Gloves).getData());
    }
    else {
        eqp.emplace_back(false, Button(238.f, 140.f, Item(0).getPath()));
        texts_eqp.push_back(Item(0).getData());
    }
    if (hero->checkIfEqp(itemType::Boots)) {
        eqp.emplace_back(true, Button(238.f, 189.f, hero->getItemFromEqp(itemType::Boots).getPath()));
        texts_eqp.push_back(hero->getItemFromEqp(itemType::Boots).getData());
    }
    else {
        eqp.emplace_back(false, Button(238.f, 189.f, Item(0).getPath()));
        texts_eqp.push_back(Item(0).getData());
    }
    if (hero->checkIfEqp(itemType::Weapon)) {
        eqp.emplace_back(true, Button(108.f, 238.f, hero->getItemFromEqp(itemType::Weapon).getPath()));
        texts_eqp.push_back(hero->getItemFromEqp(itemType::Weapon).getData());
    }
    else {
        eqp.emplace_back(false, Button(108.f, 238.f, Item(0).getPath()));
        texts_eqp.push_back(Item(0).getData());
    }
    if (hero->checkIfEqp(itemType::Ring)) {
        eqp.emplace_back(true, Button(157.f, 238.f, hero->getItemFromEqp(itemType::Ring).getPath()));
        texts_eqp.push_back(hero->getItemFromEqp(itemType::Ring).getData());
    }
    else {
        eqp.emplace_back(false, Button(157.f, 238.f, Item(0).getPath()));
        texts_eqp.push_back(Item(0).getData());
    }


    sf::Text hover(font);
    hover.setFillColor(sf::Color::Black);
    hover.setCharacterSize(8 * scale);
    bool hovering = false;
    bool hoverAvaiable = true;

    int isDragged = -1;
    bool isDraggedFlag = false;
    while (window->isOpen()) {
        hovering = false;
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window->close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            if (!blacksmithAvaiable.empty() && !isDraggedFlag) {
                for (int i = 0; i < blacksmithAvaiable.size(); i++) {
                    int x = blacksmithAvaiable[i];
                    if (items[x].isPressed(sf::Mouse::getPosition(*window))) {
                        items[x].setPosition({mousePos.x - 10.f, mousePos.y - 10.f});
                        isDragged = x;
                        isDraggedFlag = true;
                        hoverAvaiable = false;
                        break;
                    }
                }
            }
            if (back.isPressed(mousePos) && isDraggedFlag) {
                break;
            }
        }
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && isDraggedFlag) {
            isDraggedFlag = false;
            items[isDragged].setPosition({
                                             startX + (isDragged % 3) * spacingX * 1.f,
                                             startY + (isDragged / 3) * spacingY * 1.f
                                         });
            isDragged = -1;
            hoverAvaiable = true;
        }
        if (isDraggedFlag && isDragged >= 0) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            items[isDragged].setPosition({static_cast<float>(mousePos.x - 10), static_cast<float>(mousePos.y - 10)});
        }

        if (!blacksmithAvaiable.empty() && hoverAvaiable) {
            for (auto id: blacksmithAvaiable) {
                int x = blacksmithAvaiable[id];
                if (items[x].isPressed(sf::Mouse::getPosition(*window))) {
                    hover.setString(texts[id]);
                    hover.setPosition({items[x].getPosition().x - 85 * scale, items[x].getPosition().y + 34 * scale});
                    hover_frame.setPosition({
                                                items[x].getPosition().x - 95 * scale,
                                                items[x].getPosition().y + 27 * scale
                                            });
                    hovering = true;
                    break;
                }
            }
        }
        if (hoverAvaiable) {
            for (int i = 0; i < inventory.size(); i++) {
                if (inventory[i].isPressed(sf::Mouse::getPosition(*window)) && hero->getItemFromInventory(i).getId() >
                    0) {
                    hover.setString(texts_inv[i]);
                    hover.setPosition({
                                          inventory[i].getPosition().x - 85 * scale,
                                          inventory[i].getPosition().y + 34 * scale
                                      });
                    hover_frame.setPosition({
                                                inventory[i].getPosition().x - 95 * scale,
                                                inventory[i].getPosition().y + 27 * scale
                                            });
                    hovering = true;
                    break;
                }
            }
        }
        window->clear();
        window->draw(blacksmith_background);
        window->draw(gui);
        if (!blacksmithAvaiable.empty()) {
            for (auto id: blacksmithAvaiable) {
                window->draw(items[id]);
            }
        }
        if (!inventory.empty()) {
            for (int i = 0; i < inventory.size(); i++) {
                if (hero->getItemFromInventory(i).getId() > 0)
                    window->draw(items[i]);
            }
        }
        if (!eqp.empty()) {
            for (int i = 0; i < eqp.size(); i++) {
                if (eqp[i].first)
                    window->draw(eqp[i].second);
            }
        }
        window->draw(arrow_l);
        window->draw(arrow_r);
        window->draw(back);
        if (isDraggedFlag && isDragged >= 0) {
            window->draw(items[isDragged]);
        }
        if (hovering) {
            window->draw(hover_frame);
            window->draw(hover);
        }
        window->display();
    }
}

void game::mainMenu (character*& hero, sf::RenderWindow* window) {
    Button play(170.f, 150.f, "src\\textures\\background\\MainMenu\\ENG\\play_button.png");
    Button options(170.f, 200.f, "src\\textures\\background\\MainMenu\\ENG\\options_button.png");
    Button quit(470.f, 280.f, "src\\textures\\background\\MainMenu\\ENG\\quit_button.png");
    Button credits(30.f, 280.f, "src\\textures\\background\\MainMenu\\ENG\\credits_button.png");
    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window->close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            if (play.isPressed(mousePos)) {
                setLocation(Location::Saves);
                break;
            }
            else if (options.isPressed(mousePos)) {
                setLocation(Location::OptionsG);
                break;
            }
            else if (quit.isPressed(mousePos)) {
                setLocation(Location::Quit);
                break;
            }
        }

        window->clear();
        window->draw(play);
        window->draw(options);
        window->draw(quit);
        window->draw(credits);
        window->display();
    }
}

std::string getName (sf::RenderWindow* window, sf::Font& font) {
    sf::Texture frame;
    if (!frame.loadFromFile("src\\textures\\GUI\\324x44border.png")) {
        std::cerr << "Failed to load texture from file: " << "src\\textures\\GUI\\324x44border.png" << std::endl;
        throw std::runtime_error("Failed to load texture from file: src\\textures\\GUI\\324x44border.png");
    }
    sf::Sprite frame1(frame);
    frame1.setPosition({scale * 158.f, scale * 158.f});
    frame1.scale({scale, scale});
    std::string inputText = "";
    sf::Text text(font, "", int(scale * 24));
    text.setFillColor(sf::Color::Black);
    text.setPosition({scale * 166.f, scale * 162.f});

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window->close();
            }
            if (event->is<sf::Event::TextEntered>()) {
                auto textEvent = event->getIf<sf::Event::TextEntered>();
                auto unicode = textEvent->unicode;

                if (unicode == 13) {
                    return inputText;
                }
                else if (unicode == 8 && !inputText.empty()) {
                    inputText.pop_back();
                }
                else if (unicode >= 32 && unicode <= 126) {
                    if (inputText.length() < 10) {
                        inputText += static_cast<char>(unicode);
                    }
                }
                text.setString(inputText);
            }
        }
        sf::Vector2f bounds = text.getGlobalBounds().size;
        text.setPosition({scale * 320.f - bounds.x / 2, scale * 162.f});
        window->clear();
        window->draw(frame1);
        window->draw(text);
        window->display();
    }
    return inputText;
}

void game::createhero (character*& hero, sf::RenderWindow* window) {
    sf::Texture choose;
    if (!choose.loadFromFile("src\\textures\\background\\Saves\\choose class.png")) {
        std::cerr << "Failed to load texture from file: " << "src\\textures\\background\\Saves\\choose class.png" <<
                std::endl;
        throw
                std::runtime_error("Failed to load texture from file: src\\textures\\background\\Saves\\choose class.png");
    }
    std::string name = "BlankName";
    sf::Sprite ch(choose);
    Button mage(240.f, 100.f, "src\\textures\\background\\Saves\\classes\\mage.png");
    Button warr(300.f, 100.f, "src\\textures\\background\\Saves\\classes\\warrior.png");
    Button arch(360.f, 100.f, "src\\textures\\background\\Saves\\classes\\archer.png");
    ch.setPosition({scale * 170.f, scale * 200});
    ch.scale({scale, scale});
    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window->close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            if (mage.isPressed(mousePos)) {
                name = getName(window, font);
                hero = new Mage(name, mageStats);
                break;
            }
            else if (warr.isPressed(mousePos)) {
                name = getName(window, font);
                hero = new Warrior(name, warriorStats);
                break;
            }
            else if (arch.isPressed(mousePos)) {
                name = getName(window, font);
                hero = new Archer(name, archerStats);
                break;
            }
        }
        window->clear();
        window->draw(ch);
        window->draw(mage);
        window->draw(warr);
        window->draw(arch);
        window->display();
    }
}

bool isFileEmpty (std::string filename) {
    std::ifstream file(filename, std::ios::ate);
    if (!file) {
        std::cerr << "Nie udało się otworzyć pliku!" << std::endl;
        return true;
    }
    file.seekg(0, std::ios::end);
    return file.tellg() == 0;
}

void clearFile (std::string filename) {
    std::ofstream file(filename, std::ios::trunc);
    if (!file) {
        std::cerr << "Acces violation at path: " + filename << std::endl;
        throw std::runtime_error("Acces violation at path: " + filename);
    }
}

void game::saveRead (character*& hero, sf::RenderWindow* window, std::string filename) {
    if (!isFileEmpty(filename)) {
        if (hero->load_from_file(filename, hero)) {
            if (hero->prologueState())
                setLocation(Location::City);
            else
                lvl0(hero, window);
        }
    }
    else {
        createhero(hero, window);
        setLocation(Location::City);
        lvl0(hero, window);
    }
}

void game::saves (character*& hero, sf::RenderWindow* window) {
    Button s1(110.f, 100.f, "src\\textures\\background\\Saves\\save.png");
    Button s2(270.f, 100.f, "src\\textures\\background\\Saves\\save.png");
    Button s3(430.f, 100.f, "src\\textures\\background\\Saves\\save.png");
    Button back(170.f, 300.f, "src\\textures\\background\\Saves\\go_back.png");
    Button del1(110.f, 230.f, "src\\textures\\background\\MainMenu\\ENG\\delete.png");
    Button del2(270.f, 230.f, "src\\textures\\background\\MainMenu\\ENG\\delete.png");
    Button del3(430.f, 230.f, "src\\textures\\background\\MainMenu\\ENG\\delete.png");
    Button yes(364.f, 195.f, "src\\textures\\GUI\\checkbox_yes.png");
    Button no(274.f, 195.f, "src\\textures\\GUI\\checkbox_no.png");
    sf::Texture sure;
    if (!sure.loadFromFile("src\\textures\\background\\MainMenu\\ENG\\you_sure.png")) {
        std::cerr << "Failed to load texture from file: " << "src\\textures\\background\\MainMenu\\ENG\\you_sure.png" <<
                std::endl;
        throw
                std::runtime_error("Failed to load texture from file: src\\textures\\background\\MainMenu\\ENG\\you_sure.png");
    }
    sf::Sprite yousure(sure);
    yousure.scale({scale, scale});
    yousure.setPosition({scale * 270, scale * 128});
    bool del = false;
    bool delete1 = false;
    bool delete2 = false;
    bool delete3 = false;
    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window->close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            if (yes.isPressed(mousePos) && del == true) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                if (delete1 == true) {
                    clearFile("saves\\saveFile1.txt");
                    delete1 = false;
                    del = false;
                }
                if (delete2 == true) {
                    clearFile("saves\\saveFile2.txt");
                    delete2 = false;
                    del = false;
                }
                if (delete3 == true) {
                    clearFile("saves\\saveFile3.txt");
                    delete3 = false;
                    del = false;
                }
            }
            else if (no.isPressed(mousePos) && del) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                del = false;
            }
            else if (s1.isPressed(mousePos) && del == false) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                saveRead(hero, window, "saves\\saveFile1.txt");
                break;
            }
            else if (s2.isPressed(mousePos) && del == false) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                saveRead(hero, window, "saves\\saveFile2.txt");
                break;
            }
            else if (s3.isPressed(mousePos) && del == false) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                saveRead(hero, window, "saves\\saveFile3.txt");
                break;
            }
            else if (del1.isPressed(mousePos) && del == false) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                del = true;
                delete1 = true;
            }
            else if (del2.isPressed(mousePos) && del == false) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                del = true;
                delete2 = true;
            }
            else if (del3.isPressed(mousePos) && del == false) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                del = true;
                delete3 = true;
            }
            else if (back.isPressed(mousePos) && del == false) {
                setLocation(Location::MainMenu);
                break;
            }
        }

        window->clear();
        window->draw(s1);
        window->draw(s2);
        window->draw(s3);
        window->draw(back);
        window->draw(del1);
        window->draw(del2);
        window->draw(del3);
        if (del) {
            window->draw(yousure);
            window->draw(yes);
            window->draw(no);
        }
        window->display();
    }
}

void game::optionsG (sf::RenderWindow* window) {
    if (!option.loadFromFile()) {
        std::cerr << "Failed to load texture from file: " << "src\\options\\options.txt" << std::endl;
        throw std::runtime_error("Failed to load texture from file: src\\options\\options.txt");
    }
    Button general(66.f, 10.f, "src\\textures\\background\\Options\\ENG\\general.png");
    Button sound(247.f, 10.f, "src\\textures\\background\\Options\\ENG\\sound.png");
    Button graphics(435.f, 10.f, "src\\textures\\background\\Options\\ENG\\graphics.png");
    Button back(170.f, 300.f, "src\\textures\\background\\Saves\\go_back.png");
    sf::Texture language;
    sf::Texture tutorials;
    if (!language.loadFromFile("src\\textures\\background\\Options\\ENG\\language.png")) {
        std::cerr << "Failed to load texture from file: " << "src\\textures\\background\\Options\\ENG\\language.png" <<
                std::endl;
        throw
                std::runtime_error("Failed to load texture from file: src\\textures\\background\\Options\\ENG\\language.png");
    }
    if (!tutorials.loadFromFile("src\\textures\\background\\Options\\ENG\\tutorials.png")) {
        std::cerr << "Failed to load texture from file: " << "src\\textures\\background\\Options\\ENG\\tutorials.png" <<
                std::endl;
        throw
                std::runtime_error("Failed to load texture from file: src\\textures\\background\\Options\\ENG\\tutorials.png");
    }
    sf::Sprite lang(language);
    sf::Sprite tutorial(tutorials);
    lang.setPosition({scale * 15.f, scale * 70.f});
    tutorial.setPosition({scale * 15.f, scale * 120.f});
    lang.scale({scale, scale});
    tutorial.scale({scale, scale});
    Button checkboxOff(415.f, 120.f, "src\\textures\\GUI\\checkbox_no.png");
    Button checkboxOn(415.f, 120.f, "src\\textures\\GUI\\checkbox_yes.png");
    Button currentLng(370.f, 70.f, "src\\textures\\background\\Options\\ENG\\eng.png");
    Button nextLng(370.f, 105.f, "src\\textures\\background\\Options\\PL\\pl.png");
    if (option.getLanguage() == Language::PL) {
        currentLng.setTextureFile("src\\textures\\background\\Options\\PL\\pl.png");
        nextLng.setTextureFile("src\\textures\\background\\Options\\ENG\\eng.png");
    }
    bool choosingLanguage = false;
    bool checkbox = option.getTutorials();
    sf::Texture background;
    if (!background.loadFromFile("src\\textures\\background\\Options\\options_frame.png")) {
        std::cerr << "Failed to load texture from file: " << "src\\textures\\background\\Options\\options_frame.png" <<
                std::endl;
        throw
                std::runtime_error("Failed to load texture from file: src\\textures\\background\\Options\\options_frame.png");
    }
    sf::Sprite bg(background);
    bg.setPosition({0.f, scale * 45.f});
    bg.scale({scale, scale});

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window->close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            if (back.isPressed(mousePos) && !choosingLanguage) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                setLocation(Location::MainMenu);
                option.saveToFile();
                break;
            }
            else if (checkboxOn.isPressed(mousePos) && checkbox && !choosingLanguage) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                option.setTutorials(false);
                checkbox = false;
            }
            else if (checkboxOff.isPressed(mousePos) && !checkbox && !choosingLanguage) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                option.setTutorials(true);
                checkbox = true;
            }
            else if (currentLng.isPressed(mousePos) && !choosingLanguage) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                choosingLanguage = true;
            }
            else if (currentLng.isPressed(mousePos) && choosingLanguage) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                choosingLanguage = false;
            }
            else if (nextLng.isPressed(mousePos) && choosingLanguage) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                choosingLanguage = false;
                if (option.getLanguage() == Language::ENG) {
                    option.setLanguage(Language::PL);
                    currentLng.setTextureFile("src\\textures\\background\\Options\\PL\\pl.png");
                    nextLng.setTextureFile("src\\textures\\background\\Options\\ENG\\eng.png");
                }
                else {
                    option.setLanguage(Language::ENG);
                    currentLng.setTextureFile("src\\textures\\background\\Options\\ENG\\eng.png");
                    nextLng.setTextureFile("src\\textures\\background\\Options\\PL\\pl.png");
                }
            }
            else if (graphics.isPressed(mousePos) && !choosingLanguage) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                setLocation(Location::OptionsGraph);
                break;
            }
            else if (sound.isPressed(mousePos) && !choosingLanguage) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                setLocation(Location::OptionsS);
                break;
            }
        }

        window->clear();
        window->draw(bg);
        window->draw(general);
        window->draw(sound);
        window->draw(graphics);
        window->draw(back);
        window->draw(tutorial);
        window->draw(lang);
        window->draw(currentLng);
        if (!checkbox)
            window->draw(checkboxOff);
        else
            window->draw(checkboxOn);
        if (choosingLanguage) {
            window->draw(nextLng);
        }
        window->display();
    }
}

void game::optionsGraph (sf::RenderWindow* window) {
    Button general(66.f, 10.f, "src\\textures\\background\\Options\\ENG\\general.png");
    Button sound(247.f, 10.f, "src\\textures\\background\\Options\\ENG\\sound.png");
    Button graphics(435.f, 10.f, "src\\textures\\background\\Options\\ENG\\graphics.png");
    Button back(170.f, 300.f, "src\\textures\\background\\Saves\\go_back.png");
    sf::Texture lim;
    sf::Texture mode;
    sf::Texture resolution;
    if (!lim.loadFromFile("src\\textures\\background\\Options\\ENG\\FPS_limit.png")) {
        std::cerr << "Failed to load texture from file: " << "src\\textures\\background\\Options\\ENG\\FPS_limit.png" <<
                std::endl;
        throw
                std::runtime_error("Failed to load texture from file: src\\textures\\background\\Options\\ENG\\FPS_limit.png");
    }
    if (!mode.loadFromFile("src\\textures\\background\\Options\\ENG\\display_mode.png")) {
        std::cerr << "Failed to load texture from file: " << "src\\textures\\background\\Options\\ENG\\display_mode.png"
                << std::endl;
        throw
                std::runtime_error("Failed to load texture from file: src\\textures\\background\\Options\\ENG\\display_mode.png");
    }
    if (!resolution.loadFromFile("src\\textures\\background\\Options\\ENG\\resolution.png")) {
        std::cerr << "Failed to load texture from file: " << "src\\textures\\background\\Options\\ENG\\resolution.png"
                << std::endl;
        throw
                std::runtime_error("Failed to load texture from file: src\\textures\\background\\Options\\ENG\\resolution.png");
    }
    sf::Sprite FPS(lim);
    sf::Sprite display(mode);
    sf::Sprite res(resolution);
    FPS.setPosition({scale * 15.f, scale * 70.f});
    display.setPosition({scale * 15.f, scale * 120.f});
    res.setPosition({scale * 15.f, scale * 170.f});
    FPS.scale({scale, scale});
    display.scale({scale, scale});
    res.scale({scale, scale});

    Button currentFPS(395.f, 70.f, "src\\textures\\background\\Options\\ENG\\60.png");
    Button secondFPS(395.f, 105.f, "src\\textures\\background\\Options\\ENG\\30.png");
    Button thirdFPS(395.f, 140.f, "src\\textures\\background\\Options\\ENG\\140.png");
    if (option.getFPS() == FPS::_30) {
        currentFPS.setTextureFile("src\\textures\\background\\Options\\ENG\\30.png");
        secondFPS.setTextureFile("src\\textures\\background\\Options\\ENG\\60.png");
    }
    else if (option.getFPS() == FPS::_144) {
        currentFPS.setTextureFile("src\\textures\\background\\Options\\ENG\\140.png");
        thirdFPS.setTextureFile("src\\textures\\background\\Options\\ENG\\60.png");
    }
    Button currentMode(370.f, 120.f, "src\\textures\\background\\Options\\ENG\\fullscreen.png");
    Button secondMode(370.f, 155.f, "src\\textures\\background\\Options\\ENG\\borderless.png");
    Button thirdMode(370.f, 190.f, "src\\textures\\background\\Options\\ENG\\window.png");
    if (option.getMode() == Mode::borderless) {
        currentMode.setTextureFile("src\\textures\\background\\Options\\ENG\\borderless.png");
        secondMode.setTextureFile("src\\textures\\background\\Options\\ENG\\fullscreen.png");
    }
    else if (option.getMode() == Mode::windowed) {
        currentMode.setTextureFile("src\\textures\\background\\Options\\ENG\\window.png");
        secondMode.setTextureFile("src\\textures\\background\\Options\\ENG\\fullscreen.png");
        thirdMode.setTextureFile("src\\textures\\background\\Options\\ENG\\borderless.png");
    }
    Button currentRes(395.f, 170.f, "src\\textures\\background\\Options\\1080p.png");
    Button secondRes(395.f, 205.f, "src\\textures\\background\\Options\\360p.png");
    Button thirdRes(395.f, 240.f, "src\\textures\\background\\Options\\1440p.png");
    if (option.getResolution() == Resolution::p360) {
        currentRes.setTextureFile("src\\textures\\background\\Options\\360p.png");
        secondRes.setTextureFile("src\\textures\\background\\Options\\1080p.png");
    }
    else if (option.getResolution() == Resolution::p1440) {
        currentRes.setTextureFile("src\\textures\\background\\Options\\1440p.png");
        thirdRes.setTextureFile("src\\textures\\background\\Options\\1080p.png");
    }
    bool choosingFPS = false;
    bool choosingMode = false;
    bool choosingResolution = false;

    sf::Texture background;
    if (!background.loadFromFile("src\\textures\\background\\Options\\options_frame.png")) {
        std::cerr << "Failed to load texture from file: " << "src\\textures\\background\\Options\\options_frame.png" <<
                std::endl;
        throw
                std::runtime_error("Failed to load texture from file: src\\textures\\background\\Options\\options_frame.png");
    }
    sf::Sprite bg(background);
    bg.setPosition({0.f, scale * 45.f});
    bg.scale({scale, scale});

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window->close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            if (back.isPressed(mousePos) && !choosingFPS && !choosingMode && !choosingResolution) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                setLocation(Location::MainMenu);
                option.saveToFile();
                sf::Vector2u windowsize;
                if (option.getResolution() == Resolution::p1080) {
                    windowsize = {1920, 1080};
                    scale = 3.0f;
                }
                else if (option.getResolution() == Resolution::p1440) {
                    windowsize = {2560, 1440};
                    scale = 4.0f;
                }
                else {
                    windowsize = {640, 360};
                    scale = 1.0f;
                }
                if (option.getFPS() == FPS::_144)
                    window->setFramerateLimit(144);
                else if (option.getFPS() == FPS::_30)
                    window->setFramerateLimit(30);
                else
                    window->setFramerateLimit(60);
                if (option.getMode() == Mode::fullscreen)
                    window->create(sf::VideoMode(windowsize), "Gra 1.0", sf::Style::None, sf::State::Fullscreen);
                else if (option.getMode() == Mode::windowed)
                    window->create(sf::VideoMode(windowsize), "Gra 1.0", sf::Style::Default, sf::State::Windowed);
                else
                    window->create(sf::VideoMode(windowsize), "Gra 1.0", sf::Style::None, sf::State::Windowed);
                break;
            }
            else if (general.isPressed(mousePos) && !choosingFPS && !choosingMode && !choosingResolution) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                setLocation(Location::OptionsG);
                break;
            }
            else if (sound.isPressed(mousePos) && !choosingFPS && !choosingMode && !choosingResolution) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                setLocation(Location::OptionsS);
                break;
            }
            else if (currentFPS.isPressed(mousePos) && !choosingFPS && !choosingMode && !choosingResolution) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                choosingFPS = true;
            }
            else if (currentFPS.isPressed(mousePos) && choosingFPS && !choosingMode && !choosingResolution) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                choosingFPS = false;
            }
            else if (secondFPS.isPressed(mousePos) && choosingFPS && !choosingMode && !choosingResolution) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                choosingFPS = false;
                if (option.getFPS() == FPS::_60) {
                    option.setFPS(FPS::_30);
                    currentFPS.setTextureFile("src\\textures\\background\\Options\\ENG\\30.png");
                    secondFPS.setTextureFile("src\\textures\\background\\Options\\ENG\\60.png");
                    thirdFPS.setTextureFile("src\\textures\\background\\Options\\ENG\\140.png");
                    window->setFramerateLimit(30);
                }
                else if (option.getFPS() == FPS::_30) {
                    option.setFPS(FPS::_60);
                    currentFPS.setTextureFile("src\\textures\\background\\Options\\ENG\\60.png");
                    secondFPS.setTextureFile("src\\textures\\background\\Options\\ENG\\30.png");
                    window->setFramerateLimit(60);
                }
                else {
                    option.setFPS(FPS::_30);
                    currentFPS.setTextureFile("src\\textures\\background\\Options\\ENG\\30.png");
                    secondFPS.setTextureFile("src\\textures\\background\\Options\\ENG\\60.png");
                    thirdFPS.setTextureFile("src\\textures\\background\\Options\\ENG\\140.png");
                    window->setFramerateLimit(30);
                }
            }
            else if (thirdFPS.isPressed(mousePos) && choosingFPS && !choosingMode && !choosingResolution) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                choosingFPS = false;
                if (option.getFPS() == FPS::_60) {
                    option.setFPS(FPS::_144);
                    currentFPS.setTextureFile("src\\textures\\background\\Options\\ENG\\140.png");
                    thirdFPS.setTextureFile("src\\textures\\background\\Options\\ENG\\60.png");
                    window->setFramerateLimit(144);
                }
                else if (option.getFPS() == FPS::_30) {
                    option.setFPS(FPS::_144);
                    currentFPS.setTextureFile("src\\textures\\background\\Options\\ENG\\140.png");
                    secondFPS.setTextureFile("src\\textures\\background\\Options\\ENG\\30.png");
                    thirdFPS.setTextureFile("src\\textures\\background\\Options\\ENG\\60.png");
                    window->setFramerateLimit(144);
                }
                else {
                    option.setFPS(FPS::_60);
                    currentFPS.setTextureFile("src\\textures\\background\\Options\\ENG\\60.png");
                    thirdFPS.setTextureFile("src\\textures\\background\\Options\\ENG\\140.png");
                    window->setFramerateLimit(60);
                }
            }
            else if (currentMode.isPressed(mousePos) && !choosingFPS && !choosingMode && !choosingResolution) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                choosingMode = true;
            }
            else if (currentMode.isPressed(mousePos) && !choosingFPS && choosingMode && !choosingResolution) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                choosingMode = false;
            }
            else if (secondMode.isPressed(mousePos) && !choosingFPS && choosingMode && !choosingResolution) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                choosingMode = false;
                if (option.getMode() == Mode::borderless) {
                    option.setMode(Mode::fullscreen);
                    currentMode.setTextureFile("src\\textures\\background\\Options\\ENG\\fullscreen.png");
                    secondMode.setTextureFile("src\\textures\\background\\Options\\ENG\\borderless.png");
                }
                else if (option.getMode() == Mode::fullscreen) {
                    option.setMode(Mode::borderless);
                    currentMode.setTextureFile("src\\textures\\background\\Options\\ENG\\borderless.png");
                    secondMode.setTextureFile("src\\textures\\background\\Options\\ENG\\fullscreen.png");
                }
                else {
                    option.setMode(Mode::fullscreen);
                    currentMode.setTextureFile("src\\textures\\background\\Options\\ENG\\fullscreen.png");
                    secondMode.setTextureFile("src\\textures\\background\\Options\\ENG\\borderless.png");
                    thirdMode.setTextureFile("src\\textures\\background\\Options\\ENG\\window.png");
                }
            }
            else if (thirdMode.isPressed(mousePos) && !choosingFPS && choosingMode && !choosingResolution) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                choosingMode = false;
                if (option.getMode() == Mode::borderless) {
                    option.setMode(Mode::windowed);
                    currentMode.setTextureFile("src\\textures\\background\\Options\\ENG\\window.png");
                    secondMode.setTextureFile("src\\textures\\background\\Options\\ENG\\fullscreen.png");
                    thirdMode.setTextureFile("src\\textures\\background\\Options\\ENG\\borderless.png");
                }
                else if (option.getMode() == Mode::fullscreen) {
                    option.setMode(Mode::windowed);
                    currentMode.setTextureFile("src\\textures\\background\\Options\\ENG\\window.png");
                    secondMode.setTextureFile("src\\textures\\background\\Options\\ENG\\fullscreen.png");
                    thirdMode.setTextureFile("src\\textures\\background\\Options\\ENG\\borderless.png");
                }
                else {
                    option.setMode(Mode::borderless);
                    currentMode.setTextureFile("src\\textures\\background\\Options\\ENG\\borderless.png");
                    thirdMode.setTextureFile("src\\textures\\background\\Options\\ENG\\window.png");
                }
            }
            else if (currentRes.isPressed(mousePos) && !choosingFPS && !choosingMode && !choosingResolution) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                choosingResolution = true;
            }
            else if (currentRes.isPressed(mousePos) && !choosingFPS && !choosingMode && choosingResolution) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                choosingResolution = false;
            }
            else if (secondRes.isPressed(mousePos) && !choosingFPS && !choosingMode && choosingResolution) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                choosingResolution = false;
                if (option.getResolution() == Resolution::p360) {
                    option.setResolution(Resolution::p1080);
                    currentRes.setTextureFile("src\\textures\\background\\Options\\1080p.png");
                    secondRes.setTextureFile("src\\textures\\background\\Options\\360p.png");
                }
                else if (option.getResolution() == Resolution::p1080) {
                    option.setResolution(Resolution::p360);
                    currentRes.setTextureFile("src\\textures\\background\\Options\\360p.png");
                    secondRes.setTextureFile("src\\textures\\background\\Options\\1080p.png");
                }
                else {
                    option.setResolution(Resolution::p360);
                    currentRes.setTextureFile("src\\textures\\background\\Options\\360p.png");
                    secondRes.setTextureFile("src\\textures\\background\\Options\\1080p.png");
                    thirdRes.setTextureFile("src\\textures\\background\\Options\\1440p.png");
                }
            }
            else if (thirdRes.isPressed(mousePos) && !choosingFPS && !choosingMode && choosingResolution) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                choosingResolution = false;
                if (option.getResolution() == Resolution::p360) {
                    option.setResolution(Resolution::p1440);
                    currentRes.setTextureFile("src\\textures\\background\\Options\\1440p.png");
                    secondRes.setTextureFile("src\\textures\\background\\Options\\360p.png");
                    thirdRes.setTextureFile("src\\textures\\background\\Options\\1080p.png");
                }
                else if (option.getResolution() == Resolution::p1080) {
                    option.setResolution(Resolution::p1440);
                    currentRes.setTextureFile("src\\textures\\background\\Options\\1440p.png");
                    secondRes.setTextureFile("src\\textures\\background\\Options\\360p.png");
                    thirdRes.setTextureFile("src\\textures\\background\\Options\\1080p.png");
                }
                else {
                    option.setResolution(Resolution::p1080);
                    currentRes.setTextureFile("src\\textures\\background\\Options\\1080p.png");
                    thirdRes.setTextureFile("src\\textures\\background\\Options\\1440p.png");
                }
            }
        }

        window->clear();
        window->draw(bg);
        window->draw(general);
        window->draw(sound);
        window->draw(graphics);
        window->draw(back);
        window->draw(FPS);
        window->draw(display);
        window->draw(res);
        window->draw(currentFPS);
        window->draw(currentRes);
        window->draw(currentMode);
        if (choosingFPS && !choosingMode && !choosingResolution) {
            window->draw(secondFPS);
            window->draw(thirdFPS);
        }
        if (choosingMode && !choosingFPS && !choosingResolution) {
            window->draw(secondMode);
            window->draw(thirdMode);
        }
        if (choosingResolution && !choosingFPS && !choosingMode) {
            window->draw(secondRes);
            window->draw(thirdRes);
        }
        window->display();
    }
}

void game::optionsS (sf::RenderWindow* window) {
    Button general(66.f, 10.f, "src\\textures\\background\\Options\\ENG\\general.png");
    Button sound(247.f, 10.f, "src\\textures\\background\\Options\\ENG\\sound.png");
    Button graphics(435.f, 10.f, "src\\textures\\background\\Options\\ENG\\graphics.png");
    Button back(170.f, 300.f, "src\\textures\\background\\Saves\\go_back.png");
    sf::Texture enviroment;
    sf::Texture effect;
    sf::Texture music;
    sf::Texture main;
    sf::Texture background;
    if (!enviroment.loadFromFile("src\\textures\\background\\Options\\ENG\\enviromental_sound_volume.png")) {
        std::cerr << "Failed to load texture from file: " <<
                "src\\textures\\background\\Options\\ENG\\enviromental_sound_volume.png" << std::endl;
        throw
                std::runtime_error("Failed to load texture from file: src\\textures\\background\\Options\\ENG\\enviromental_sound_volume.png");
    }
    if (!effect.loadFromFile("src\\textures\\background\\Options\\ENG\\sound_effects_volume.png")) {
        std::cerr << "Failed to load texture from file: " <<
                "src\\textures\\background\\Options\\ENG\\sound_effects_volume.png" << std::endl;
        throw
                std::runtime_error("Failed to load texture from file: src\\textures\\background\\Options\\ENG\\sound_effects_volume.png");
    }
    if (!music.loadFromFile("src\\textures\\background\\Options\\ENG\\music_volume.png")) {
        std::cerr << "Failed to load texture from file: " << "src\\textures\\background\\Options\\ENG\\music_volume.png"
                << std::endl;
        throw
                std::runtime_error("Failed to load texture from file: src\\textures\\background\\Options\\ENG\\music_volume.png");
    }
    if (!main.loadFromFile("src\\textures\\background\\Options\\ENG\\master_volume.png")) {
        std::cerr << "Failed to load texture from file: " <<
                "src\\textures\\background\\Options\\ENG\\master_volume.png" << std::endl;
        throw
                std::runtime_error("Failed to load texture from file: src\\textures\\background\\Options\\ENG\\master_volume.png");
    }
    if (!background.loadFromFile("src\\textures\\background\\Options\\options_frame.png")) {
        std::cerr << "Failed to load texture from file: " << "src\\textures\\background\\Options\\options_frame.png" <<
                std::endl;
        throw
                std::runtime_error("Failed to load texture from file: src\\textures\\background\\Options\\options_frame.png");
    }
    sf::Sprite env(enviroment);
    sf::Sprite eff(effect);
    sf::Sprite mus(music);
    sf::Sprite g(main);
    sf::Sprite bg(background);
    g.setPosition({scale * 15.f, scale * 70.f});
    env.setPosition({scale * 15.f, scale * 250.f});
    eff.setPosition({scale * 15.f, scale * 120.f});
    mus.setPosition({scale * 15.f, scale * 200.f});
    bg.setPosition({0.f, scale * 45.f});
    env.scale({scale, scale});
    eff.scale({scale, scale});
    mus.scale({scale, scale});
    g.scale({scale, scale});
    bg.scale({scale, scale});

    Slider master_slider(340.f, 70.f);
    Slider env_slider(340.f, 265.f);
    Slider effect_slider(340.f, 135.f);
    Slider music_slider(340.f, 200.f);

    master_slider.setSlider(option.getmasterVolume());
    env_slider.setSlider(option.getenviromentVolume());
    effect_slider.setSlider(option.geteffectsVolume());
    music_slider.setSlider(option.getmusicVolume());

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window->close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            if (back.isPressed(mousePos)) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                setLocation(Location::MainMenu);
                option.saveToFile();
                break;
            }
            else if (general.isPressed(mousePos)) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                setLocation(Location::OptionsG);
                break;
            }
            else if (graphics.isPressed(mousePos)) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                setLocation(Location::OptionsGraph);
                break;
            }
            else if (master_slider.isPressed(mousePos)) {
                mousePos = sf::Mouse::getPosition(*window);
                int volume;
                master_slider.slide(mousePos, volume, 0, 100);
                option.setmasterVolume(volume);
            }
            else if (env_slider.isPressed(mousePos)) {
                mousePos = sf::Mouse::getPosition(*window);
                int volume;
                env_slider.slide(mousePos, volume, 0, 100);
                option.setenviromentVolume(volume);
            }
            else if (effect_slider.isPressed(mousePos)) {
                mousePos = sf::Mouse::getPosition(*window);
                int volume;
                effect_slider.slide(mousePos, volume, 0, 100);
                option.seteffectsVolume(volume);
            }
            else if (music_slider.isPressed(mousePos)) {
                mousePos = sf::Mouse::getPosition(*window);
                int volume;
                music_slider.slide(mousePos, volume, 0, 100);
                option.setmusicVolume(volume);
            }
        }

        window->clear();
        window->draw(bg);
        window->draw(general);
        window->draw(sound);
        window->draw(graphics);
        window->draw(back);
        window->draw(env);
        window->draw(g);
        window->draw(eff);
        window->draw(mus);
        window->draw(master_slider);
        window->draw(env_slider);
        window->draw(effect_slider);
        window->draw(music_slider);
        window->display();
    }
}

void game::worldMap (character*& hero) {
    while (true) {
        Time.timeFlow();
        Time.printTime();
        std::cout << "Chose your destination:\n\n0. Main Menu\n\n1. City" << "\n2. Whispering Woods " <<
                isUnlockedPrint(Location::Forest) << "\n3.(TBA) Mud-flooded Swamp " << isUnlockedPrint(Location::Swamp)
                << "\n4.(TBA) Howling Maw Cavern " << isUnlockedPrint(Location::Caves) << "\n5.(TBA) Ice Peaks " <<
                isUnlockedPrint(Location::IcePeaks) << "\n6.(TBA) Lava-Flooded Volcano " <<
                isUnlockedPrint(Location::Volcano) << "\n7.(TBA) Unholy Graveyard " <<
                isUnlockedPrint(Location::Graveyard) << "\n8.(TBA) Ocean of Trial " << isUnlockedPrint(Location::Ocean)
                << std::endl;
        int loc;
        std::cin >> loc;
        if (loc == 0) {
            setLocation(Location::MainMenu);
            break;
        }
        if (loc == 1) {
            setLocation(Location::City);
            std::cout << "You have entered to the city." << std::endl;
            break;
        }
        else if (loc == 2) {
            setLocation(Location::Forest);
            std::cout << "You have entered to Whispering Woods. Watch out for what hides in the shadows..." <<
                    std::endl;
            //forest(hero);

            break;
        }
        else if (loc == 3 && isUnlocked(Location::Caves)) {
            setLocation(Location::Caves);
            std::cout << "You have entered to the Howling Maw Cavern." << std::endl;


            break;
        }
        else if (loc == 3 && !isUnlocked(Location::Caves)) {
            std::cout << "Location Locked." << std::endl;
        }
        else if (loc == 4 && isUnlocked(Location::IcePeaks)) {
            setLocation(Location::IcePeaks);
            std::cout << "You have entered the Ice Peaks." << std::endl;


            break;
        }
        else if (loc == 4 && !isUnlocked(Location::IcePeaks)) {
            std::cout << "Location Locked." << std::endl;
        }
        else if (loc == 5 && isUnlocked(Location::Volcano)) {
            setLocation(Location::Volcano);
            std::cout << "You have entered the Lava-Flooded Volcano." << std::endl;


            break;
        }
        else if (loc == 5 && !isUnlocked(Location::Volcano)) {
            std::cout << "Location Locked." << std::endl;
        }
        else if (loc == 6 && isUnlocked(Location::Graveyard)) {
            setLocation(Location::Graveyard);
            std::cout << "You have entered to the Unholy Graveyard." << std::endl;


            break;
        }
        else if (loc == 6 && !isUnlocked(Location::Graveyard)) {
            std::cout << "Location Locked." << std::endl;
        }
        else if (loc == 7 && isUnlocked(Location::Ocean)) {
            setLocation(Location::Ocean);
            std::cout << "You have entered the Ocean of Trial." << std::endl;


            break;
        }
        else if (loc == 7 && !isUnlocked(Location::Ocean)) {
            std::cout << "Location Locked." << std::endl;
        }
    }
}

void game::city (character*& hero, sf::RenderWindow* window) {
    AllTimeGUI gui(hero);
    Button forge(60.f, 170.f, "src\\textures\\background\\City\\Buildings\\blacksmith.png");
    Button tavern_building(420.f, 190.f, "src\\textures\\background\\City\\Buildings\\tavern.png");
    Button gate(246.f, 100.f, "src\\textures\\background\\City\\Buildings\\city_gate.png");
    Button church_building(360.f, 143.f, "src\\textures\\background\\City\\Buildings\\church.png");

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window->close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            if (forge.isPressed(mousePos)) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                blacksmith(hero, window);
            }
            if (church_building.isPressed(mousePos)) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                setLocation(Location::Church);
                break;
            }
            if (gate.isPressed(mousePos)) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                worldMap(hero);
                break;
            }
            if (tavern_building.isPressed(mousePos)) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                tavern(hero, window);
            }
        }
        window->clear();
        window->draw(gate);
        window->draw(church_building);
        window->draw(forge);
        window->draw(tavern_building);
        window->draw(gui);
        window->display();
    }
}

int game::fight3 (character*& hero, character*& enemy1, character*& enemy2, character*& enemy3) {
    std::vector<character*> enemies = {enemy1, enemy2, enemy3};
    std::vector<character*> turn = {enemy1, enemy2, enemy3, hero};
    std::sort(turn.begin(), turn.end(), [] (character* a, character* b) {
        if (a == nullptr)
            return false;
        if (b == nullptr)
            return true;
        return a->getSpeed() > b->getSpeed();
    });

    while (hero->currenthp > 0) {
        hero->regen();
        if (hero->getHPRegpotT() > 0) {
            hero->potionregen();
            hero->setHPRegpotT(-1);
        }
        if (hero->getManapotT() > 0) {
            hero->manaregen();
            hero->setManapotT(-1);
        }
        while (true) {
            int action;
            std::cout << "Choose your action:\n\n1. Attack" << std::endl;
            if (hero->getPotionCD() == 0 && hero->getLvl() >= 2)
                std::cout << "2. Drink Potion" << std::endl;
            std::cin >> action;
            int enemynb;
            if (action == 1) {
                if (enemies.size() >= 2) {
                    while (true) {
                        std::cout << "\nChoose enemy to attack:" << std::endl;

                        for (size_t i = 0; i < enemies.size(); ++i) {
                            if (enemies[i] != nullptr) {
                                std::cout << i + 1 << ". " << enemies[i]->getName() << " (current HP: " << enemies[i]->
                                        currenthp << ")" << std::endl;
                            }
                        }
                        std::cin >> enemynb;
                        if (enemies.size() == 2 && (enemynb == 1 || enemynb == 2))
                            break;
                        else if (enemies.size() == 3 && (enemynb == 1 || enemynb == 2 || enemynb == 3))
                            break;
                    }
                }
                else
                    enemynb = 1;

                if (enemies[0] != nullptr)
                    enemies[0]->atktypenb = std::rand() % 3 + 1;
                if (enemies[1] != nullptr)
                    enemies[1]->atktypenb = std::rand() % 3 + 1;
                if (enemies[2] != nullptr)
                    enemies[2]->atktypenb = std::rand() % 3 + 1;

                for (size_t turnnb = 0; turnnb < turn.size(); turnnb++) {
                    if (turn[turnnb] == hero) {
                        heroaction(enemies[enemynb - 1], hero);

                        if (enemies[enemynb - 1]->currenthp <= 0) {
                            std::cout << std::endl;
                            hero->printstatcurrent();
                            std::cout << std::endl;
                            fightEnd(hero, enemies[enemynb - 1]);

                            enemies[enemynb - 1]->printstatcurrent();
                            enemies[enemynb - 1] = nullptr;
                            enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [] (character* character) {
                                return character == nullptr || character->currenthp <= 0;
                            }), enemies.end());
                            turn.erase(std::remove_if(turn.begin(), turn.end(), [] (character* character) {
                                return character == nullptr || character->currenthp <= 0;
                            }), turn.end());

                            if (std::all_of(enemies.begin(), enemies.end(), [] (character* e) {
                                return e == nullptr;
                            })) {
                                hero->setFastAction(false);
                                hero->setHPRegpotT(-hero->getHPRegpotT());
                                hero->setManapotT(-hero->getManapotT());
                                return 1;
                            }
                        }


                        if (hero->currenthp <= 0) {
                            hero->setFastAction(false);
                            hero->setHPRegpotT(-hero->getHPRegpotT());
                            hero->setManapotT(-hero->getManapotT());
                            return 0;
                        }
                    }
                    else if (turn[turnnb] != nullptr) {
                        enemyaction(turn[turnnb], hero);
                        if (hero->currenthp <= 0) {
                            return 0;
                        }
                    }
                }
                break;
            }
            else
                if (action == 2 && hero->getPotionCD() == 0 && hero->getLvl() >= 2) {}
        }
    }
    return 0;
}
