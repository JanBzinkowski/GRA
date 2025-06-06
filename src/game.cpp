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
#include "LvlUpPopup.h"
#include "HealthBar.h"
#include "Slider.h"
#include "itemMap.h"
#define PotionTime 3


extern std::unordered_map<int, enemyStats> enemies;


Enemy* game::createEnemy (const enemyStats& stats) {
    switch (stats.Class) {
        case enemyClasses::EnemyWarrior:
            return new EnemyWarrior(stats.name, stats.stats);
        case enemyClasses::EnemyMage:
            return new EnemyMage(stats.name, stats.stats);
        case enemyClasses::EnemyArcher:
            return new EnemyArcher(stats.name, stats.stats);
        default:
            throw std::runtime_error("Unknown enemy class");
    }
}

bool game::areShopsOpen () const {
    if (time.gettime().x >= 7 && time.gettime().x < 22)
        return true;
    return false;
}

void game::loss () {
    hero->setCurrentGold(hero->getCurrentGold() / 2);
    hero->pray();
}

bool game::enemyenc (int indexmin, int indexmax, int exp, int gold, int maxlvl, sf::RenderWindow*& window, sf::Sprite background) {
    int i = 0;
    std::uniform_int_distribution<> dist(indexmin, indexmax);
    int index = dist(gen);
    Enemy* enemy = createEnemy(enemies.at(index));
    if (enemy == nullptr) {
        std::cerr << "Error: Enemy creation failed." << std::endl;
        return false;
    }
    enemy->setEXPDrop(exp);
    enemy->setGoldDrop(gold);
    while (enemy->getLvl() < hero->getLvl() && enemy->getLvl() <= maxlvl) {
        enemy->enemyLvlUp();
        enemy->setCurrentHP(enemy->getMaxHP());
    }
    int res = fight(enemy, window);
    bool lvl_up_flag_1=false;
    bool lvl_up_flag_2=false;
    if (res == 0) {
        loss();
        return false;
    }
    else if (res == 2) {
        lvl_up_flag_1 = true;
    }

    HUD gui(hero, &time, window);

    LvlUpPopup lvl_up_popup(hero, font, option, window);
    lvl_up_popup.updateText(window);

    Button arrow_l(52.f, 145.f, window, "..\\src\\textures\\GUI\\arrow_key_left.png");
    Button arrow_r(588.f, 145.f, window, "..\\src\\textures\\GUI\\arrow_key_right.png");

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window->close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            if (lvl_up_flag_1) {
                    while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                    lvl_up_popup.updateText(window, true);
                    lvl_up_flag_1 = false;
                lvl_up_flag_2 = true;
            }
            else if (lvl_up_flag_2) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                lvl_up_flag_2 = false;
            }
            else if (arrow_l.isPressed(mousePos) && !lvl_up_flag_1 && !lvl_up_flag_2) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                setLocation(Location::City);
                return false;
            }
            else if (arrow_r.isPressed(mousePos) && !lvl_up_flag_1 && !lvl_up_flag_2) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                return true;
            }
        }
        window->clear();
        window->draw(background);
        window->draw(gui);
        if (lvl_up_flag_1 || lvl_up_flag_2) {
            window->draw(lvl_up_popup);
        }
        else {
            window->draw(arrow_l);
            window->draw(arrow_r);
        }
        window->display();
    }
    return true;
}

bool game::enemyenc3 (int indexmin, int indexmax, int exp, int gold, int maxlvl, sf::RenderWindow* window, sf::Sprite background) {
    std::uniform_int_distribution<> dist(indexmin, indexmax);
    int index = dist(gen);
    Enemy* enemy1 = createEnemy(enemies.at(index));
    enemy1->setEXPDrop(exp);
    enemy1->setGoldDrop(gold);
    while (enemy1->getLvl() < hero->getLvl() || enemy1->getLvl() >= maxlvl) {
        enemy1->enemyLvlUp();
        enemy1->setCurrentHP(enemy1->getMaxHP());
    }
    index = dist(gen);
    Enemy* enemy2 = createEnemy(enemies.at(index));
    enemy2->setEXPDrop(exp);
    enemy2->setGoldDrop(gold);
    while (enemy2->getLvl() < hero->getLvl() || enemy2->getLvl() >= maxlvl) {
        enemy2->enemyLvlUp();
        enemy2->setCurrentHP(enemy2->getMaxHP());
    }
    index = dist(gen);
    Enemy* enemy3 = createEnemy(enemies.at(index));
    enemy3->setEXPDrop(exp);
    enemy3->setGoldDrop(gold);
    while (enemy3->getLvl() < hero->getLvl() || enemy3->getLvl() >= maxlvl) {
        enemy3->enemyLvlUp();
        enemy3->setCurrentHP(enemy3->getMaxHP());
    }

    bool lvl_up_flag_1=false;
    bool lvl_up_flag_2=false;
    int res = fight3(enemy1, enemy2, enemy3, window);
    if (res == 0) {
        loss();
        enemy1 = nullptr;
        enemy2 = nullptr;
        enemy3 = nullptr;
        return false;
    }
    else if (res == 2) {
        lvl_up_flag_1 = true;
    }

    HUD gui(hero, &time, window);

    LvlUpPopup lvl_up_popup(hero, font, option, window);
    lvl_up_popup.updateText(window);

    Button arrow_l(52.f, 145.f, window, "..\\src\\textures\\GUI\\arrow_key_left.png");
    Button arrow_r(588.f, 145.f, window, "..\\src\\textures\\GUI\\arrow_key_right.png");

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window->close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            if (lvl_up_flag_1) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                lvl_up_popup.updateText(window, true);
                lvl_up_flag_1 = false;
                lvl_up_flag_2 = true;
            }
            else if (lvl_up_flag_2) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                lvl_up_flag_2 = false;
            }
            else if (arrow_l.isPressed(mousePos) && !lvl_up_flag_1 && !lvl_up_flag_2) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                setLocation(Location::City);
                enemy1 = nullptr;
                enemy2 = nullptr;
                enemy3 = nullptr;
                return false;
            }
            else if (arrow_r.isPressed(mousePos) && !lvl_up_flag_1 && !lvl_up_flag_2) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                enemy1 = nullptr;
                enemy2 = nullptr;
                enemy3 = nullptr;
                return true;
            }
        }
        window->clear();
        window->draw(background);
        if (lvl_up_flag_1 || lvl_up_flag_2) {
            window->draw(lvl_up_popup);
        }
        else {
            window->draw(arrow_l);
            window->draw(arrow_r);
        }
        window->draw(gui);
        window->display();
    }
    enemy1 = nullptr;
    enemy2 = nullptr;
    enemy3 = nullptr;
    return true;
}

void game::lvl0 (sf::RenderWindow* window) {
    time.pause();
    Enemy* enemy1 = createEnemy(enemies.at(0));
    enemy1->setEXPDrop(30);
    enemy1->setGoldDrop(10);

    if (fight(enemy1, window) == 0) {
        if (getLocation() != Location::MainMenu && getLocation() != Location::Quit) {
            hero->expInc(30);
            hero->lvlup();
            hero->goldInc(20);
            hero->pray();
        }
        else
            return;
    }
    else {
        Enemy* enemy2 = createEnemy(enemies.at(1));
        enemy2->setEXPDrop(20);
        enemy2->setGoldDrop(10);
        Enemy* enemy3 = createEnemy(enemies.at(2));
        enemy3->setEXPDrop(20);
        enemy3->setGoldDrop(10);
        Enemy* enemy4 = createEnemy(enemies.at(3));
        enemy4->setEXPDrop(20);
        enemy4->setGoldDrop(10);

        if (fight3(enemy2, enemy3, enemy4, window) == 0) {
            if (getLocation() != Location::MainMenu && getLocation() != Location::Quit) {
                hero->goldInc(20);
                hero->pray();
            }
            else
                return;
        }
        else {
            hero->goldInc(20);
        }
        hero->prologueSet(true);
        enemy2 = nullptr;
        enemy3 = nullptr;
        enemy4 = nullptr;
    }
    setLocation(Location::City);
    hero->citySet(true);
    hero->churchSet(true);
    hero->tavernSet(true);
    hero->blacksmithSet(true);
    hero->mapSet(true);
    delete enemy1;
    time.resetTimeMorning();
    time.resume();
}

void game::forest (sf::RenderWindow* window) {
    sf::Texture background;
    if (!background.loadFromFile("..\\src\\textures\\GUI\\20x20frame.png")) {
        std::cerr << "Failed to load texture from file: ..\\src\\textures\\GUI\\20x20frame.png" << std::endl;
        throw std::runtime_error("Failed to load texture from file: ..\\src\\textures\\GUI\\20x20frame.png");
    }
    sf::Sprite bg(background);
    if (!enemyenc(4, 6, 6, 10, 10, window, bg))
        return;
    if (!enemyenc(4, 6, 6, 10, 10, window, bg))
        return;
    if (!enemyenc(4, 8, 10, 15, 10, window, bg))
        return;
    if (!enemyenc(4, 8, 10, 15, 10, window, bg))
        return;

    if (!enemyenc3(9, 12, 14, 20, 10, window, bg))
        return;

    if (!enemyenc(7, 12, 14, 20, 10, window, bg))
        return;
    if (!enemyenc(7, 12, 14, 20, 10, window, bg))
        return;
    if (!enemyenc(7, 12, 14, 20, 10, window, bg))
        return;
    if (!enemyenc(7, 12, 14, 20, 10, window, bg))
        return;
    if (!enemyenc(13, 13, 22, 30, 10, window, bg))
        return;
    if (!isUnlocked(Location::Swamp)) {
        unlockLocations(Location::Swamp);
    }
}

int game::heroaction (Enemy*& enemy, Hero*& hero) {
    int damage;
    if (hero->getClass() == "Mage") {
        damage = enemy->getDamaged(hero, DamageType::MagicEnergy);
    }
    else {
        damage = enemy->getDamaged(hero, DamageType::Physical);
    }
    hero->setFastAction(false);
    return damage;
}

int game::enemyaction (Enemy*& enemy, Hero*& hero) {
    int damage;
    if (enemy == nullptr)
        return 0;
    if (enemy->getClass() == "EnemyMage")
        damage = hero->getDamaged(enemy, DamageType::MagicEnergy);
    else
        damage = hero->getDamaged(enemy, DamageType::Physical);
    return damage;
}

int game::fight (Enemy*& enemy, sf::RenderWindow* window) {
    HUD gui(hero, &time, window);
    sf::Clock clockHero;
    sf::Clock clockEnemy;
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

    HealthBar enemyBar(395.f, 130.f, window, enemy);

    Button heroGraphics(100.f, 150.f, window, hero->getPath());
    Button enemyGraphics(400.f, 150.f, window, enemy->getPath());
    int damage_hero;
    int damage_enemy;
    sf::Text DealtToHero(font, "", 24 * scale);
    sf::Text DealtToEnemy(font, "", 24 * scale);
    DealtToEnemy.setFillColor(sf::Color::Red);
    DealtToHero.setFillColor(sf::Color::Red);
    DealtToEnemy.setPosition({400.f * scale, 150.f * scale});
    DealtToHero.setPosition({100.f * scale, 150.f * scale});
    sf::Clock dealt_to_hero;
    sf::Clock dealt_to_enemy;

    sf::Clock end_fight;
    bool fight_end = false;
    bool win = false;

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window->close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            if (gui.isLightAtkClicked(mousePos) && !heroChosen && heroAction) {
                hero->setAtkTypeNB(1);
                heroChosen = true;
            }
            else if (gui.isMediumAtkClicked(mousePos) && !heroChosen && heroAction) {
                hero->setAtkTypeNB(2);
                heroChosen = true;
            }
            else if (gui.isHeavyAtkClicked(mousePos) && !heroChosen && heroAction) {
                hero->setAtkTypeNB(3);
                heroChosen = true;
            }
            else if (gui.isFastActionPotionClicked(mousePos) && !heroChosen && heroAction && hero->getActionpot() > 0) {
                hero->setFastAction(true);
                hero->setActionpot(-1);
                potionCD = 4;
            }
            else if (gui.isRegenPotionClicked(mousePos) && !heroChosen && heroAction && hero->getHPRegpot() > 0) {
                hero->setHPRegpot(-1);
                hero->setHPRegpotT(PotionTime);
                potionCD = 4;
            }
            else if (gui.isManaPotionClicked(mousePos) && !heroChosen && heroAction && hero->getManapot() > 0) {
                hero->setManapot(-1);
                hero->setManapotT(PotionTime);
                potionCD = 4;
            }
            else if (gui.isHpPotionClicked(mousePos) && !heroChosen && heroAction && hero->getHPpot() > 0) {
                hero->setHPpot(-1);
                hero->instaHP();
                potionCD = 4;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            while (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape));
            if (!pauseMenu(window)) {
                if (getLocation() != Location::Quit) {
                    setLocation(Location::MainMenu);
                }
                return 0;
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
                hero->regen();
                hero->setHPRegpotT(-1);
            }
            if (hero->getManapotT() > 0) {
                hero->manaRegen();
                hero->setManapotT(-1);
            }
            regenHandled = true;
        }
        if (heroAction && !fight_end && heroChosen && clockEnemy.getElapsedTime().asSeconds() > 2) {
            if (!hero->getFastAction()) {
                heroAction = false;
                clockHero.restart();
                turnHero = true;
            }
            damage_enemy = heroaction(enemy, hero);
            dealt_to_enemy.restart();
            DealtToEnemy.setString("-" + std::to_string(damage_enemy));
            potionCD--;
            heroChosen = false;
            if (enemy->getCurrentHP() <= 0) {
                fightEnd(enemy);
                win = true;
                fight_end = true;
                end_fight.restart();
            }
        }

        if (!fight_end && !heroAction && clockHero.getElapsedTime().asSeconds() >= 2) {
            enemy->setAtkTypeNB(rand() % 3);
            damage_hero = enemyaction(enemy, hero);
            dealt_to_hero.restart();
            DealtToHero.setString("-" + std::to_string(damage_hero));
            potionCD--;
            heroAction = true;
            turnEnemy = true;
            if (hero->getCurrentHP() <= 0) {
                fight_end = true;
                end_fight.restart();
            }
            clockEnemy.restart();
        }
        if (fight_end && end_fight.getElapsedTime().asSeconds() > 2) {
            hero->setFastAction(false);
            hero->setHPRegpotT(-hero->getHPRegpotT());
            hero->setManapotT(-hero->getManapotT());
            enemy = nullptr;
            delete enemy;
            if (win) {
                if(hero->lvlup())
                    return 2;
                return 1;
            }
            return 0;
        }

        window->clear();
        window->draw(gui);
        window->draw(heroGraphics);
        window->draw(enemyGraphics);
        enemyBar.updateRed();
        window->draw(enemyBar);
        if (dealt_to_hero.getElapsedTime().asSeconds() < 2) {
            window->draw(DealtToHero);
        }
        if (dealt_to_enemy.getElapsedTime().asSeconds() < 2)
            window->draw(DealtToEnemy);
        window->display();
    }
    delete enemy;
    return 0;
}

int game::fight3 (Enemy*& enemy1, Enemy*& enemy2, Enemy*& enemy3, sf::RenderWindow* window) {
    Enemy* heroTurn = new EnemyWarrior("x", hero->getStats());
    std::vector<Enemy*> enemies = {enemy1, enemy2, enemy3};
    std::vector<Enemy*> turn = {enemy1, enemy2, enemy3, heroTurn};
    std::sort(turn.begin(), turn.end(), [] (Character* a, Character* b) {
        if (a == nullptr)
            return false;
        if (b == nullptr)
            return true;
        return a->getSpeed() > b->getSpeed();
    });

    HUD gui(hero, &time, window);
    sf::Clock clockHero;
    clockHero.start();
    sf::Clock clockEnemy;
    clockEnemy.start();
    int turnOrder = 0;
    int chosen_enemy;
    int potionCD = 0;
    bool heroAction = false;
    bool heroChosen = false;
    bool regenHandled = true;
    bool turnHero = false;
    bool chooseEnemy = true;

    Enemy* enemy = nullptr;

    HealthBar enemyBar1(395.f, 130.f, window, enemy1);
    HealthBar enemyBar2(495.f, 130.f, window, enemy2);
    HealthBar enemyBar3(295.f, 130.f, window, enemy3);

    Button heroGraphics(100.f, 150.f, window, hero->getPath());
    Button enemy1Graphics(400.f, 150.f, window, enemy1->getPath());
    Button enemy2Graphics(500.f, 150.f, window, enemy2->getPath());
    Button enemy3Graphics(300.f, 150.f, window, enemy3->getPath());

    int damage_hero;
    int damage_enemy;
    sf::Text DealtToHero(font, "", 24 * scale);
    sf::Text DealtToEnemy1(font, "", 24 * scale);
    sf::Text DealtToEnemy2(font, "", 24 * scale);
    sf::Text DealtToEnemy3(font, "", 24 * scale);
    DealtToEnemy1.setFillColor(sf::Color::Red);
    DealtToEnemy2.setFillColor(sf::Color::Red);
    DealtToEnemy3.setFillColor(sf::Color::Red);
    DealtToHero.setFillColor(sf::Color::Red);
    DealtToEnemy1.setPosition({400.f * scale, 150.f * scale});
    DealtToEnemy2.setPosition({500.f * scale, 150.f * scale});
    DealtToEnemy3.setPosition({300.f * scale, 150.f * scale});
    DealtToHero.setPosition({100.f * scale, 150.f * scale});
    sf::Clock dealt_to_hero;
    sf::Clock dealt_to_enemy1;
    sf::Clock dealt_to_enemy2;
    sf::Clock dealt_to_enemy3;

    sf::Clock end_fight;
    bool fight_end = false;
    bool win = false;

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window->close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            if (gui.isLightAtkClicked(mousePos) && !heroChosen && heroAction) {
                hero->setAtkTypeNB(1);
                heroChosen = true;
                chooseEnemy = true;
            }
            else if (gui.isMediumAtkClicked(mousePos) && !heroChosen && heroAction) {
                hero->setAtkTypeNB(2);
                heroChosen = true;
                chooseEnemy = true;
            }
            else if (gui.isHeavyAtkClicked(mousePos) && !heroChosen && heroAction) {
                hero->setAtkTypeNB(3);
                heroChosen = true;
                chooseEnemy = true;
            }
            else if (gui.isFastActionPotionClicked(mousePos) && !heroChosen && heroAction && hero->getActionpot() > 0) {
                hero->setFastAction(true);
                hero->setActionpot(-1);
                potionCD = 4;
            }
            else if (gui.isRegenPotionClicked(mousePos) && !heroChosen && heroAction && hero->getHPRegpot() > 0) {
                hero->setHPRegpot(-1);
                hero->setHPRegpotT(PotionTime);
                potionCD = 4;
            }
            else if (gui.isManaPotionClicked(mousePos) && !heroChosen && heroAction && hero->getManapot() > 0) {
                hero->setManapot(-1);
                hero->setManapotT(PotionTime);
                potionCD = 4;
            }
            else if (gui.isHpPotionClicked(mousePos) && !heroChosen && heroAction && hero->getHPpot() > 0) {
                hero->setHPpot(-1);
                hero->instaHP();
                potionCD = 4;
            }
            else if (enemy1 != nullptr && heroAction && heroChosen && chooseEnemy && enemy1Graphics.isPressed(mousePos)) {
                enemy = enemy1;
                chooseEnemy = false;
                chosen_enemy = 0;
            }
            else if (enemy2 != nullptr && heroAction && heroChosen && chooseEnemy && enemy2Graphics.isPressed(mousePos)) {
                enemy = enemy2;
                chooseEnemy = false;
                chosen_enemy = 1;
            }
            else if (enemy3 != nullptr && heroAction && heroChosen && chooseEnemy && enemy3Graphics.isPressed(mousePos)) {
                enemy = enemy3;
                chooseEnemy = false;
                chosen_enemy = 2;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            while (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape));
            if (!pauseMenu(window)) {
                if (getLocation() != Location::Quit) {
                    setLocation(Location::MainMenu);
                }
                return 0;
            }
        }

        if (turnOrder >= turn.size()) {
            turnOrder = 0;
        }

        if (turn[turnOrder] == heroTurn) {
            heroAction = true;
        }

        if (turnHero && turnOrder == 0) {
            regenHandled = false;
            turnHero = false;
        }

        if (!regenHandled) {
            hero->regen();
            if (hero->getHPRegpotT() > 0) {
                hero->regen();
                hero->setHPRegpotT(-1);
            }
            if (hero->getManapotT() > 0) {
                hero->manaRegen();
                hero->setManapotT(-1);
            }
            regenHandled = true;
        }
        if (heroAction && !fight_end && !chooseEnemy && clockEnemy.getElapsedTime().asSeconds() > 2) {
            if (!hero->getFastAction()) {
                heroAction = false;
                clockHero.restart();
                turnHero = true;
            }
            damage_enemy = heroaction(enemy, hero);
            if (enemy == enemy1) {
                DealtToEnemy1.setString("-" + std::to_string(damage_enemy));
                dealt_to_enemy1.restart();
            }
            else if (enemy == enemy2) {
                DealtToEnemy2.setString("-" + std::to_string(damage_enemy));
                dealt_to_enemy2.restart();
            }
            else {
                DealtToEnemy3.setString("-" + std::to_string(damage_enemy));
                dealt_to_enemy3.restart();
            }
            potionCD--;
            turnOrder++;
            heroChosen = false;
            chooseEnemy = true;
            if (enemy->getCurrentHP() <= 0) {
                fightEnd(enemy);
                enemies[chosen_enemy] = nullptr;
                turn.erase(std::remove(turn.begin(), turn.end(), enemy), turn.end());
                if (turn.size() == 1) {
                    win = true;
                    fight_end = true;
                    end_fight.restart();
                }
            }
        }
        if (!fight_end && !heroAction && clockHero.getElapsedTime().asSeconds() > 2 && clockEnemy.getElapsedTime().asSeconds() > 2) {
            enemy = turn[turnOrder];
            enemy->setAtkTypeNB(rand() % 3);
            damage_hero = enemyaction(enemy, hero);
            dealt_to_hero.restart();
            DealtToHero.setString("-" + std::to_string(damage_hero));
            if (hero->getCurrentHP() <= 0) {
                fight_end = true;
                end_fight.restart();
            }
            clockEnemy.restart();
            turnOrder++;
        }

        if (fight_end && end_fight.getElapsedTime().asSeconds() > 2) {
            hero->setFastAction(false);
            hero->setHPRegpotT(-hero->getHPRegpotT());
            hero->setManapotT(-hero->getManapotT());
            enemy = nullptr;
            delete enemy;
            if (win) {
                if(hero->lvlup())
                    return 2;
                return 1;
            }
            return 0;
        }

        window->clear();
        window->draw(gui);
        window->draw(heroGraphics);
        if (enemy1 != nullptr) {
            window->draw(enemy1Graphics);
            enemyBar1.updateRed();
            window->draw(enemyBar1);
        }
        if (enemy2 != nullptr) {
            window->draw(enemy2Graphics);
            enemyBar2.updateRed();
            window->draw(enemyBar2);
        }
        if (enemy3 != nullptr) {
            window->draw(enemy3Graphics);
            enemyBar3.updateRed();
            window->draw(enemyBar3);
        }
        if (dealt_to_hero.getElapsedTime().asSeconds() < 2) {
            window->draw(DealtToHero);
        }
        if (dealt_to_enemy1.getElapsedTime().asSeconds() < 2) {
            window->draw(DealtToEnemy1);
        }
        if (dealt_to_enemy2.getElapsedTime().asSeconds() < 2) {
            window->draw(DealtToEnemy2);
        }
        if (dealt_to_enemy3.getElapsedTime().asSeconds() < 2) {
            window->draw(DealtToEnemy3);
        }
        window->display();
    }
    delete enemy;
    return 0;
}

void game::fightEnd (Enemy*& enemy) {
    if (enemy->getCurrentHP() <= 0) {
        hero->expInc(enemy->getEXPDrop());
        hero->goldInc(enemy->getGoldDrop());
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
    if (time.getNewDayBlacksmith()) {
        BlacksmithNewItems = true;
        time.setNewDayBlacksmith(false);
    }
    else {
        BlacksmithNewItems = false;
    }
}

void game::church (sf::RenderWindow* window) {
    time.pause();
    Button back(593.f, 44.f, window, "..\\src\\textures\\GUI\\x.png");
    Button hppot(122.f, 200.f, window, "..\\src\\textures\\GUI\\20x20frame.png");
    Button regenpot(244.f, 200.f, window, "..\\src\\textures\\GUI\\20x20frame.png");
    Button manapot(366.f, 200.f, window, "..\\src\\textures\\GUI\\20x20frame.png");
    Button actionpot(488.f, 200.f, window, "..\\src\\textures\\GUI\\20x20frame.png");
    Button pray(320.f, 70.f, window, "..\\src\\textures\\GUI\\20x20frame.png");
    Button h(128.f, 206.f, window, "..\\src\\textures\\GUI\\AllTimeGui\\potions\\hp_potion20x20.png");\
    Button r(250.f, 206.f, window, "..\\src\\textures\\GUI\\AllTimeGui\\potions\\regen_potion20x20.png");
    Button m(372.f, 206.f, window, "..\\src\\textures\\GUI\\AllTimeGui\\potions\\mana_potion20x20.png");
    Button a(494.f, 206.f, window, "..\\src\\textures\\GUI\\AllTimeGui\\potions\\action_potion20x20.png");

    if (hero->getLvl() < 2)
        h.setNewTexturePath("..\\src\\textures\\GUI\\AllTimeGui\\potions\\gui_lock20x20.png");
    if (hero->getLvl() < 3)
        r.setNewTexturePath("..\\src\\textures\\GUI\\AllTimeGui\\potions\\gui_lock20x20.png");
    if (hero->getLvl() < 5)
        m.setNewTexturePath("..\\src\\textures\\GUI\\AllTimeGui\\potions\\gui_lock20x20.png");
    if (hero->getLvl() < 8)
        a.setNewTexturePath("..\\src\\textures\\GUI\\AllTimeGui\\potions\\gui_lock20x20.png");


    HUD gui(hero, &time, window);
    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window->close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            if (back.isPressed(mousePos)) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                setLocation(Location::City);
                break;
            }
            else if (pray.isPressed(mousePos) && hero->getCurrentGold() >= 5) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                hero->pray();
                hero->goldInc(-5);
            }
            else if (hppot.isPressed(mousePos)) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                if (hero->getLvl() >= 2 && hero->getCurrentGold() >= 15) {
                    hero->goldInc(-15);
                    hero->setHPpot(1);
                }
            }
            else if (regenpot.isPressed(mousePos)) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                if (hero->getLvl() >= 3 && hero->getCurrentGold() >= 10) {
                    hero->goldInc(-10);
                    hero->setHPRegpot(1);
                }
            }
            else if (manapot.isPressed(mousePos)) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                if (hero->getLvl() >= 5 && hero->getCurrentGold() >= 15) {
                    hero->goldInc(-15);
                    hero->setManapot(1);
                }
            }
            else if (actionpot.isPressed(mousePos)) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                if (hero->getLvl() >= 8 && hero->getCurrentGold() >= 30) {
                    hero->goldInc(-30);
                    hero->setActionpot(1);
                }
            }
        }
        window->clear();
        window->draw(back);

        window->draw(hppot);
        window->draw(regenpot);
        window->draw(manapot);
        window->draw(actionpot);
        window->draw(pray);

        window->draw(h);
        window->draw(r);
        window->draw(m);
        window->draw(a);

        window->draw(gui);
        window->display();
    }
    time.timeFlow();
    time.resume();
}

void game::tavern (sf::RenderWindow* window) {
    time.pause();
    Button back(593.f, 44.f, window, "..\\src\\textures\\GUI\\x.png");
    Button sleep(100.f, 100.f, window, "..\\src\\textures\\GUI\\32x32border.png");
    Button drink(400.f, 100.f, window, "..\\src\\textures\\GUI\\32x32border.png");
    HUD gui(hero, &time, window);

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window->close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            if (back.isPressed(mousePos)) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                break;
            }
            else if (sleep.isPressed(mousePos)) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                if (hero->getCurrentGold() >= 5) {
                    hero->goldInc(-5);
                    hero->save_to_file();
                    saveBlacksmithInv();
                    time.resetTimeMorning();
                    break;
                }
            }
            else if (drink.isPressed(mousePos)) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                if (hero->getCurrentGold() >= 1) {
                    hero->goldInc(-1);
                }
            }
        }
        window->clear();
        window->draw(back);
        window->draw(sleep);
        window->draw(drink);
        window->draw(gui);
        window->display();
    }
    time.timeFlow();
    time.resume();
}

void game::itemRandomize (std::mt19937& gen) {
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

void game::blacksmith (sf::RenderWindow* window) {
    int g=0;
    time.pause();
    updateBlacksmith();
    itemRandomize(gen);

    sf::FloatRect shop_rect({377.f * scale, 199.f * scale}, {130.f * scale, 81.f * scale});

    sf::Texture blacksmith_bg;
    if (!blacksmith_bg.loadFromFile("..\\src\\textures\\GUI\\gui_blacksmith.png")) {
        std::cerr << "Failed to load texture from file: ..\\src\\textures\\GUI\\gui_blacksmith.png" << std::endl;
        throw std::runtime_error("Failed to load texture from file: ..\\src\\textures\\GUI\\gui_blacksmith.png");
    }
    sf::Texture hoverFrame;
    if (!hoverFrame.loadFromFile("..\\src\\textures\\GUI\\192x80border.png")) {
        std::cerr << "Failed to load texture from file: ..\\src\\textures\\GUI\\192x80border.png" << std::endl;
        throw std::runtime_error("Failed to load texture from file: ..\\src\\textures\\GUI\\192x80border.png");
    }

    sf::Sprite blacksmith_background(blacksmith_bg);
    sf::Sprite hover_frame(hoverFrame);
    sf::Sprite hover_frame_compare(hoverFrame);
    hover_frame_compare.scale({scale, scale});
    blacksmith_background.scale({scale, scale});
    hover_frame.scale({scale, scale});

    HUD gui(hero, &time, window);

    Button arrow_l(281.f, 95.f, window, "..\\src\\textures\\GUI\\arrow_key_left.png");
    Button arrow_r(588.f, 95.f, window, "..\\src\\textures\\GUI\\arrow_key_right.png");
    Button back(593.f, 44.f, window, "..\\src\\textures\\GUI\\x.png");

    std::vector<Button> items;
    float startX = 377;
    float startY = 199;
    int spacingX = 49;
    int spacingY = 49;
    for (int i = 0; i < 6; ++i) {
        float x = startX + (i % 3) * spacingX;
        float y = startY + (i / 3) * spacingY;
        items.emplace_back(x, y, window, blacksmithInv[i].getPath());
    }

    std::vector<Button> backpack;
    int startXinv = 304;
    int startYinv = 91;
    int spacingXinv = 49;
    for (int i = 0; i < hero->getInvSize(); ++i) {
        int x = startXinv + spacingXinv * i;
        if (hero->getItemFromInventory(i).getId() > 0) {
            backpack.emplace_back(x, startYinv, window, hero->getItemFromInventory(i).getPath());
        }
        else {
            backpack.emplace_back(x, startYinv, window, "..\\src\\textures\\items\\Buty.png");
        }
    }

    std::vector<std::string> texts;
    for (int i = 0; i < 6; ++i) {
        texts.push_back(blacksmithInv[i].getData());
    }

    std::vector<std::string> texts_inv;
    for (int i = 0; i < hero->getInvSize(); ++i) {
        if (hero->getItemFromInventory(i).getId() > 0) {
            texts_inv.push_back(hero->getItemFromInventory(i).getData());
        }
        else {
            texts_inv.push_back(Item(0).getData());
        }
    }

    std::vector<std::pair<bool, Button>> eqp;
    std::vector<std::string> texts_eqp;
    std::vector<itemType> types = {itemType::Helmet, itemType::Chestplate, itemType::Leggings, itemType::Necklace, itemType::Gloves, itemType::Boots, itemType::Weapon, itemType::Ring};

    std::vector<float> xs = {59.f, 59.f, 59.f, 206.f, 206.f, 206.f, 108.f, 157.f};
    std::vector<float> ys = {91.f, 140.f, 189.f, 91.f, 140.f, 189.f, 238.f, 238.f};

    for (size_t i = 0; i < types.size(); ++i) {
        bool has = hero->checkIfEqp(types[i]);
        Item item = has? hero->getItemFromEqp(types[i]) : Item(0);
        eqp.emplace_back(has, Button(xs[i], ys[i], window, item.getPath()));
        texts_eqp.push_back(item.getData());
    }

    sf::Text hover(font);
    hover.setFillColor(sf::Color::Black);
    hover.setCharacterSize(8 * scale);
    sf::Text hover_compare(font);
    hover_compare.setFillColor(sf::Color::Black);
    hover_compare.setCharacterSize(8 * scale);
    bool hovering = false;
    bool hovering_compare = false;
    bool hoverAvaiable = true;

    bool money = false;
    sf::Text notEnoughMoney(font);
    sf::Clock noMoneyTime;
    noMoneyTime.start();
    std::string noMoney;
    if (option.getLanguage() == Language::PL) {
        noMoney = "Nie masz wystarczająco złotych monet";
    }
    else if (option.getLanguage() == Language::ENG) {
        noMoney = "Not enough gold coins";
    }
    noMoneyTime.restart();
    sf::String utf32noMoney = sf::String::fromUtf8(noMoney.begin(), noMoney.end());
    notEnoughMoney.setString(utf32noMoney);
    notEnoughMoney.setCharacterSize(24 * scale);
    notEnoughMoney.setFillColor(sf::Color::Red);

    int isDragged = -1;
    int isDraggedInv = -1;
    int isDraggedEqp = -1;
    bool isDraggedFlag = false;
    while (window->isOpen()) {
        hovering = false;
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window->close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            if (back.isPressed(mousePos) && !isDraggedFlag) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                break;
            }
            if (!blacksmithAvaiable.empty() && !isDraggedFlag && shop_rect.contains(static_cast<sf::Vector2f>(mousePos))) {
                for (int i = 0; i < blacksmithAvaiable.size(); i++) {
                    int x = blacksmithAvaiable[i];
                    if (items[x].isPressed(mousePos)) {
                        startX = items[x].getPosition().x;
                        startY = items[x].getPosition().y;
                        isDragged = x;
                        isDraggedFlag = true;
                        hoverAvaiable = false;
                        break;
                    }
                }
            }
            else if (!isDraggedFlag) {
                bool check = true;
                for (int i = 0; i < backpack.size(); i++) {
                    if (backpack[i].isPressed(mousePos) && hero->getItemFromInventory(i).getId() > 0) {
                        startX = backpack[i].getPosition().x;
                        startY = backpack[i].getPosition().y;
                        isDraggedFlag = true;
                        isDraggedInv = i;
                        hoverAvaiable = false;
                        check = false;
                        break;
                    }
                }
                if (check) {
                    for (int i = 0; i < eqp.size(); i++) {
                        if (eqp[i].second.isPressed(mousePos) && hero->checkIfEqp(types[i])) {
                            startX = eqp[i].second.getPosition().x;
                            startY = eqp[i].second.getPosition().y;
                            isDraggedFlag = true;
                            isDraggedEqp = i;
                            hoverAvaiable = false;
                            break;
                        }
                    }
                }
            }
        }
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && isDraggedFlag && isDragged >= 0 && hero->getCurrentGold() >= blacksmithInv[isDragged].getStats().price) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            bool checkEqp = true;
            for (int i = 0; i < backpack.size(); i++) {
                if (backpack[i].isPressed(mousePos) && hero->isAvailable(i)) {
                    hero->addToInv(blacksmithInv[isDragged], i);
                    hero->goldInc(-blacksmithInv[isDragged].getStats().price);
                    for (int z = 0; z < blacksmithAvaiable.size(); z++) {
                        if (blacksmithAvaiable[z] == isDragged) {
                            blacksmithAvaiable.erase(blacksmithAvaiable.begin() + z);
                        }
                    }
                    backpack[i].setNewTexturePath(blacksmithInv[isDragged].getPath());
                    texts_inv[i] = blacksmithInv[isDragged].getData();
                    checkEqp = false;
                    break;
                }
            }
            if (checkEqp) {
                for (int i = 0; i < eqp.size(); ++i) {
                    if (eqp[i].second.isPressed(mousePos)) {
                        if ((blacksmithInv[isDragged].getType() == types[i]) && (hero->checkIfEqp(types[i]) == hero->getAvaiableAmount() > 0)) {
                            if (hero->checkIfEqp(types[i])) {
                                backpack[hero->get1stAvaiableIndex()].setNewTexturePath(hero->getItemFromEqp(types[i]).getPath());
                                texts_inv[hero->get1stAvaiableIndex()] = hero->getItemFromEqp(types[i]).getData();
                            }
                            hero->equipItem(blacksmithInv[isDragged]);
                            hero->goldInc(-blacksmithInv[isDragged].getStats().price);
                            for (int z = 0; z < blacksmithAvaiable.size(); z++) {
                                if (blacksmithAvaiable[z] == isDragged) {
                                    blacksmithAvaiable.erase(blacksmithAvaiable.begin() + z);
                                }
                            }
                            eqp[i].first = true;
                            eqp[i].second.setNewTexturePath(blacksmithInv[isDragged].getPath());
                            texts_eqp[i] = blacksmithInv[isDragged].getData();
                        }
                        break;
                    }
                }
            }
            isDraggedFlag = false;
            items[isDragged].setPosition({startX / scale, startY / scale});
            isDragged = -1;
            hoverAvaiable = true;
        }
        else if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && isDraggedFlag && isDragged >= 0 && hero->getCurrentGold() < blacksmithInv[isDragged].getStats().price) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            money = true;
            notEnoughMoney.setPosition({mousePos.x - 145 * scale, mousePos.y - 12 * scale});
            noMoneyTime.restart();
            isDraggedFlag = false;
            items[isDragged].setPosition({startX / scale, startY / scale});
            isDragged = -1;
            hoverAvaiable = true;
        }
        else if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && isDraggedFlag && isDraggedInv >= 0) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            bool checkEqp = true;
            bool checkShop = checkShop = shop_rect.contains(static_cast<sf::Vector2f>(mousePos));
            if (!checkShop)
                for (int i = 0; i < backpack.size(); i++) {
                    if (backpack[i].isPressed(mousePos)) {
                        if (isDraggedInv != i) {
                            hero->swapItems(isDraggedInv, i);
                            backpack[i].setNewTexturePath(hero->getItemFromInventory(i).getPath());
                            texts_inv[i] = hero->getItemFromInventory(i).getData();
                            backpack[isDraggedInv].setNewTexturePath(hero->getItemFromInventory(isDraggedInv).getPath());
                            texts_inv[isDraggedInv] = hero->getItemFromInventory(isDraggedInv).getData();
                            checkEqp = false;
                            break;
                        }
                    }
                }
            if (checkEqp && !checkShop) {
                for (int i = 0; i < eqp.size(); ++i) {
                    if (eqp[i].second.isPressed(mousePos)) {
                        if (hero->getItemFromInventory(isDraggedInv).getType() == types[i]) {
                            if (hero->checkIfEqp(types[i])) {
                                backpack[isDraggedInv].setNewTexturePath(hero->getItemFromEqp(types[i]).getPath());
                                texts_inv[isDraggedInv] = hero->getItemFromEqp(types[i]).getData();
                            }
                            eqp[i].first = true;
                            eqp[i].second.setNewTexturePath(hero->getItemFromInventory(isDraggedInv).getPath());
                            texts_eqp[i] = hero->getItemFromInventory(isDraggedInv).getData();
                            hero->equipFromInv(isDraggedInv);
                        }
                        break;
                    }
                }
            }
            else if (checkShop) {
                hero->goldInc(hero->getItemFromInventory(isDraggedInv).getStats().price);
                hero->removeFromInv(isDraggedInv);
                backpack[isDraggedInv].setNewTexturePath(hero->getItemFromInventory(isDraggedInv).getPath());
                texts_inv[isDraggedInv] = hero->getItemFromInventory(isDraggedInv).getData();
            }
            backpack[isDraggedInv].setPosition({startX / scale, startY / scale});
            isDraggedFlag = false;
            isDraggedInv = -1;
            hoverAvaiable = true;
        }
        else if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && isDraggedFlag && isDraggedEqp >= 0) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            bool checkShop = shop_rect.contains(static_cast<sf::Vector2f>(mousePos));
            if (!checkShop) {
                for (int i = 0; i < backpack.size(); i++) {
                    if (backpack[i].isPressed(mousePos) && hero->isAvailable(i)) {
                        hero->unequip(types[isDraggedEqp], i);
                        backpack[i].setNewTexturePath(hero->getItemFromInventory(i).getPath());
                        texts_inv[i] = hero->getItemFromInventory(i).getData();
                        eqp[isDraggedEqp].first = false;
                        break;
                    }
                }
            }
            else if (checkShop) {
                hero->goldInc(hero->getItemFromEqp(types[isDraggedEqp]).getStats().price);
                hero->removeFromEqp(types[isDraggedEqp]);
                eqp[isDraggedEqp].first = false;
            }
            eqp[isDraggedEqp].second.setPosition({startX / scale, startY / scale});
            isDraggedFlag = false;
            isDraggedEqp = -1;
            hoverAvaiable = true;
        }

        if (isDraggedFlag && isDragged >= 0) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            items[isDragged].setPosition({mousePos.x / scale - 14, mousePos.y / scale - 14});
        }
        if (isDraggedFlag && isDraggedInv >= 0) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            backpack[isDraggedInv].setPosition({mousePos.x / scale - 14, mousePos.y / scale - 14});
        }
        if (isDraggedFlag && isDraggedEqp >= 0) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            eqp[isDraggedEqp].second.setPosition({mousePos.x / scale - 14, mousePos.y / scale - 14});
        }
        if (hoverAvaiable) {
            int hovered_blacksmith = -1;
            int hovered_inventory = -1;
            int hovered_equipment = -1;
            if (!blacksmithAvaiable.empty() && shop_rect.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window)))) {
                hovered_blacksmith = hoverFrameSetBlacksmith(hover, hover_frame, items, texts, hovering, window);
            }
            if (hovered_blacksmith < 0)
                hovered_inventory = hoverFrameSetInventory(hover, hover_frame, backpack, texts_inv, hovering, window);
            if (hovered_blacksmith < 0 && hovered_inventory < 0)
                hovered_equipment = hoverFrameSetEquipmentLoop(hover, hover_frame, eqp, texts_eqp, hovering, window);
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::RShift)) && (hovered_blacksmith >= 0 || hovered_inventory >= 0)) {
                if (hovered_blacksmith >= 0 && hero->checkIfEqp(blacksmithInv[hovered_blacksmith].getType())) {
                    int i;
                    for (i = 0; i < types.size(); i++)
                        if (types[i] == blacksmithInv[hovered_blacksmith].getType())
                            break;
                    hoverFrameSetEquipmentSlot(hover_compare, hover_frame_compare, eqp[i], texts_eqp, hovering_compare, i);
                }
                else if (hovered_inventory >= 0 && hero->checkIfEqp(blacksmithInv[hovered_inventory].getType())) {
                    int i;
                    for (i = 0; i < types.size(); i++)
                        if (types[i] == hero->getItemFromInventory(hovered_inventory).getType())
                            break;
                    hoverFrameSetEquipmentSlot(hover_compare, hover_frame_compare, eqp[i], texts_eqp, hovering_compare, i);
                }
            }
            else {
                hovering_compare = false;
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
        for (int i = 0; i < backpack.size(); i++) {
            if (hero->getItemFromInventory(i).getId() > 0)
                window->draw(backpack[i]);
        }
        for (int i = 0; i < eqp.size(); i++) {
            if (eqp[i].first)
                window->draw(eqp[i].second);
        }
        window->draw(arrow_l);
        window->draw(arrow_r);
        window->draw(back);
        if (isDraggedFlag && isDragged >= 0) {
            window->draw(items[isDragged]);
        }
        else if (isDraggedFlag && isDraggedInv >= 0) {
            window->draw(backpack[isDraggedInv]);
        }
        else if (isDraggedFlag && isDraggedEqp >= 0) {
            window->draw(eqp[isDraggedEqp].second);
        }
        if (hovering) {
            window->draw(hover_frame);
            window->draw(hover);
        }
        if (hovering_compare) {
            window->draw(hover_frame_compare);
            window->draw(hover_compare);
        }
        if (money) {
            if (noMoneyTime.getElapsedTime().asSeconds() >= 2.0f) {
                money = false;
            }
            else
                window->draw(notEnoughMoney);
        }
        window->display();
    }
    time.timeFlow();
    time.resume();
}

int game::hoverFrameSetBlacksmith (sf::Text& hover, sf::Sprite& frame, std::vector<Button>& slots, std::vector<std::string>& texts, bool& flag, sf::RenderWindow* window) {
    for (int i = 0; i < slots.size(); i++) {
        int x = blacksmithAvaiable[i];
        if (slots[x].isPressed(sf::Mouse::getPosition(*window))) {
            hover.setString(texts[x]);
            hover.setPosition({slots[x].getPosition().x - 85 * scale, slots[x].getPosition().y + 34 * scale});
            frame.setPosition({slots[x].getPosition().x - 95 * scale, slots[x].getPosition().y + 27 * scale});
            flag = true;
            return x;
        }
    }
    return -1;
}

int game::hoverFrameSetInventory (sf::Text& hover, sf::Sprite& frame, std::vector<Button>& slots, std::vector<std::string>& texts, bool& flag, sf::RenderWindow* window) {
    for (int i = 0; i < slots.size(); i++) {
        if (slots[i].isPressed(sf::Mouse::getPosition(*window)) && hero->getItemFromInventory(i).getId() > 0) {
            hover.setString(texts[i]);
            hover.setPosition({slots[i].getPosition().x - 85 * scale, slots[i].getPosition().y + 34 * scale});
            frame.setPosition({slots[i].getPosition().x - 95 * scale, slots[i].getPosition().y + 27 * scale});
            flag = true;
            return i;
        }
    }
    return -1;
}

int game::hoverFrameSetEquipmentLoop (sf::Text& hover, sf::Sprite& frame, std::vector<std::pair<bool, Button>>& eqp, std::vector<std::string>& texts, bool& flag, sf::RenderWindow* window) {
    for (int i = 0; i < eqp.size(); i++) {
        if (hoverFrameSetEquipment(hover, frame, eqp[i], texts, flag, window, i)) {
            return i;
        }
    }
    return -1;
}

bool game::hoverFrameSetEquipment (sf::Text& hover, sf::Sprite& frame, std::pair<bool, Button>& eqp, std::vector<std::string>& texts, bool& flag, sf::RenderWindow* window, int& index) {
    if (eqp.second.isPressed(sf::Mouse::getPosition(*window)) && eqp.first) {
        hoverFrameSetEquipmentSlot(hover, frame, eqp, texts, flag, index);
        return true;
    }
    return false;
}

void game::hoverFrameSetEquipmentSlot (sf::Text& hover, sf::Sprite& frame, std::pair<bool, Button>& eqp, std::vector<std::string>& texts, bool& flag, int index) {
    hover.setString(texts[index]);
    sf::Vector2f pos = {eqp.second.getPosition().x - 85 * scale, eqp.second.getPosition().y + 34 * scale};
    if (pos.x - 10 < 0)
        pos.x += -(pos.x - 20 * scale);
    hover.setPosition(pos);
    frame.setPosition({pos.x - 10 * scale, pos.y - 7 * scale});
    flag = true;
}

std::string game::getBlacksmithInvPath () {
    std::string filename;
    if (hero->getSave() == "..\\saves\\saveFile1\\saveFile1.txt")
        filename = "..\\saves\\saveFile1\\saveBlack1.txt";
    else if (hero->getSave() == "..\\saves\\saveFile2\\saveFile2.txt")
        filename = "..\\saves\\saveFile2\\saveBlack2.txt";
    else if (hero->getSave() == "..\\saves\\saveFile3\\saveFile3.txt")
        filename = "..\\saves\\saveFile3\\saveBlack3.txt";
    return filename;
}

void game::saveBlacksmithInv () {
    std::string filename = getBlacksmithInvPath();
    std::ofstream file(filename, std::ios::out | std::ios::trunc);
    BlacksmithNewItems = true;
    itemRandomize(gen);
    time.setNewDayBlacksmith(false);
    if (file.is_open()) {
        for (int i = 0; i < 6; i++) {
            itemStats item = blacksmithInv[i].getStats();
            file << blacksmithInv[i].getId() << "\n" << item.hp << "\n" << item.ad << "\n" << item.def << "\n" << item.mana << "\n" << item.speed << "\n";
        }
        file.close();
    }
    else
        std::cerr << "Error: Unable to open file " << filename << std::endl;
}

void game::loadBlacksmithInv () {
    std::string filename = getBlacksmithInvPath();
    std::ifstream file(filename, std::ios::in);
    if (file.is_open()) {
        blacksmithAvaiable.clear();
        for (int i = 0; i < 6; i++) {
            int id;
            file >> id;
            itemStats stats = itemDataMap.at(id);
            file >> stats.hp;
            file >> stats.ad;
            file >> stats.def;
            file >> stats.mana;
            file >> stats.speed;
            blacksmithAvaiable.push_back(i);
            blacksmithInv[i] = Item(id, stats);
        }
        file.close();
        BlacksmithNewItems = false;
        time.setNewDayBlacksmith(false);
    }
    else
        std::cerr << "Error: Unable to open file " << filename << std::endl;
}


void game::inventory (sf::RenderWindow* window) {
    time.pause();
    sf::Texture inv_background;
    if (!inv_background.loadFromFile("..\\src\\textures\\GUI\\gui_equipment.png")) {
        std::cerr << "Failed to load texture from file: ..\\src\\textures\\GUI\\gui_equipment.png" << std::endl;
        throw std::runtime_error("Failed to load texture from file: ..\\src\\textures\\GUI\\gui_equipment.png");
    }
    sf::Texture hoverFrame;
    if (!hoverFrame.loadFromFile("..\\src\\textures\\GUI\\192x80border.png")) {
        std::cerr << "Failed to load texture from file: ..\\src\\textures\\GUI\\192x80border.png" << std::endl;
        throw std::runtime_error("Failed to load texture from file: ..\\src\\textures\\GUI\\192x80border.png");
    }
    sf::Sprite inv_bg(inv_background);
    sf::Sprite hover_frame(hoverFrame);
    sf::Sprite hover_frame_compare(hoverFrame);
    hover_frame_compare.scale({scale, scale});
    inv_bg.scale({scale, scale});
    hover_frame.scale({scale, scale});

    HUD gui(hero, &time, window);

    Button back(593.f, 44.f, window, "..\\src\\textures\\GUI\\x.png");

    std::vector<Button> inventory;
    int startXinv = 304;
    int startYinv = 91;
    int spacingXinv = 49;
    for (int i = 0; i < hero->getInvSize(); ++i) {
        int x = startXinv + spacingXinv * i;
        if (hero->getItemFromInventory(i).getId() > 0)
            inventory.emplace_back(x, startYinv, window, hero->getItemFromInventory(i).getPath());
        else
            inventory.emplace_back(x, startYinv, window, "..\\src\\textures\\items\\Buty.png");
    }

    std::vector<std::string> texts_inv;
    for (int i = 0; i < hero->getInvSize(); ++i) {
        if (hero->getItemFromInventory(i).getId() > 0) {
            texts_inv.push_back(hero->getItemFromInventory(i).getData());
        }
        else {
            texts_inv.push_back(Item(0).getData());
        }
    }

    std::vector<std::pair<bool, Button>> eqp;
    std::vector<std::string> texts_eqp;
    std::vector<itemType> types = {itemType::Helmet, itemType::Chestplate, itemType::Leggings, itemType::Necklace, itemType::Gloves, itemType::Boots, itemType::Weapon, itemType::Ring};

    std::vector<float> xs = {59.f, 59.f, 59.f, 206.f, 206.f, 206.f, 108.f, 157.f};
    std::vector<float> ys = {91.f, 140.f, 189.f, 91.f, 140.f, 189.f, 238.f, 238.f};

    for (size_t i = 0; i < types.size(); ++i) {
        bool has = hero->checkIfEqp(types[i]);
        Item item = has? hero->getItemFromEqp(types[i]) : Item(0);
        eqp.emplace_back(has, Button(xs[i], ys[i], window, item.getPath()));
        texts_eqp.push_back(item.getData());
    }


    sf::Text hover(font);
    hover.setFillColor(sf::Color::Black);
    hover.setCharacterSize(8 * scale);
    sf::Text hover_compare(font);
    hover_compare.setFillColor(sf::Color::Black);
    hover_compare.setCharacterSize(8 * scale);
    bool hovering = false;
    bool hovering_compare = false;
    bool hoverAvaiable = true;

    int isDraggedInv = -1;
    int isDraggedEqp = -1;
    bool isDraggedFlag = false;
    while (window->isOpen()) {
        hovering = false;
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window->close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            if (back.isPressed(mousePos) && !isDraggedFlag) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                break;
            }
            if (!isDraggedFlag) {
                bool checkEqp = true;
                for (int i = 0; i < inventory.size(); i++) {
                    if (inventory[i].isPressed(mousePos) && hero->getItemFromInventory(i).getId() > 0) {
                        startXinv = inventory[i].getPosition().x;
                        startYinv = inventory[i].getPosition().y;
                        isDraggedFlag = true;
                        isDraggedInv = i;
                        hoverAvaiable = false;
                        checkEqp = false;
                        break;
                    }
                }
                if (checkEqp) {
                    for (int i = 0; i < eqp.size(); i++) {
                        if (eqp[i].second.isPressed(mousePos) && hero->checkIfEqp(types[i])) {
                            startXinv = eqp[i].second.getPosition().x;
                            startYinv = eqp[i].second.getPosition().y;
                            isDraggedFlag = true;
                            isDraggedEqp = i;
                            hoverAvaiable = false;
                            break;
                        }
                    }
                }
            }
        }
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && isDraggedFlag && isDraggedInv >= 0) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            bool checkEqp = true;

            for (int i = 0; i < inventory.size(); i++) {
                if (inventory[i].isPressed(mousePos)) {
                    if (isDraggedInv != i) {
                        hero->swapItems(isDraggedInv, i);
                        inventory[i].setNewTexturePath(hero->getItemFromInventory(i).getPath());
                        texts_inv[i] = hero->getItemFromInventory(i).getData();
                        inventory[isDraggedInv].setNewTexturePath(hero->getItemFromInventory(isDraggedInv).getPath());
                        texts_inv[isDraggedInv] = hero->getItemFromInventory(isDraggedInv).getData();
                        checkEqp = false;
                        break;
                    }
                }
            }
            if (checkEqp) {
                for (int i = 0; i < eqp.size(); ++i) {
                    if (eqp[i].second.isPressed(mousePos)) {
                        if (hero->getItemFromInventory(isDraggedInv).getType() == types[i]) {
                            if (hero->checkIfEqp(types[i])) {
                                inventory[isDraggedInv].setNewTexturePath(hero->getItemFromEqp(types[i]).getPath());
                                texts_inv[isDraggedInv] = hero->getItemFromEqp(types[i]).getData();
                            }
                            eqp[i].first = true;
                            eqp[i].second.setNewTexturePath(hero->getItemFromInventory(isDraggedInv).getPath());
                            texts_eqp[i] = hero->getItemFromInventory(isDraggedInv).getData();
                            hero->equipFromInv(isDraggedInv);
                        }
                        break;
                    }
                }
            }
            inventory[isDraggedInv].setPosition({startXinv / scale, startYinv / scale});
            isDraggedFlag = false;
            isDraggedInv = -1;
            hoverAvaiable = true;
        }
        else if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && isDraggedFlag && isDraggedEqp >= 0) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            for (int i = 0; i < inventory.size(); i++) {
                if (inventory[i].isPressed(mousePos) && hero->isAvailable(i)) {
                    hero->unequip(types[isDraggedEqp], i);
                    inventory[i].setNewTexturePath(hero->getItemFromInventory(i).getPath());
                    texts_inv[i] = hero->getItemFromInventory(i).getData();
                    eqp[isDraggedEqp].first = false;
                    break;
                }
            }
            eqp[isDraggedEqp].second.setPosition({startXinv / scale, startYinv / scale});
            isDraggedFlag = false;
            isDraggedEqp = -1;
            hoverAvaiable = true;
        }

        if (isDraggedFlag && isDraggedInv >= 0) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            inventory[isDraggedInv].setPosition({mousePos.x / scale - 14, mousePos.y / scale - 14});
        }
        if (isDraggedFlag && isDraggedEqp >= 0) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            eqp[isDraggedEqp].second.setPosition({mousePos.x / scale - 14, mousePos.y / scale - 14});
        }

        if (hoverAvaiable) {
            int hovered_inventory = -1;
            int hovered_equipment = -1;
            hovered_inventory = hoverFrameSetInventory(hover, hover_frame, inventory, texts_inv, hovering, window);
            if (hovered_inventory < 0)
                hovered_equipment = hoverFrameSetEquipmentLoop(hover, hover_frame, eqp, texts_eqp, hovering, window);
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::RShift)) && hovered_inventory >= 0) {
                if (hero->checkIfEqp(blacksmithInv[hovered_inventory].getType())) {
                    int i;
                    for (i = 0; i < types.size(); i++)
                        if (types[i] == hero->getItemFromInventory(hovered_inventory).getType())
                            break;
                    hoverFrameSetEquipmentSlot(hover_compare, hover_frame_compare, eqp[i], texts_eqp, hovering_compare, i);
                }
            }
            else {
                hovering_compare = false;
            }
        }

        window->clear();
        window->draw(inv_bg);
        window->draw(gui);
        for (int i = 0; i < inventory.size(); i++) {
            if (hero->getItemFromInventory(i).getId() > 0)
                window->draw(inventory[i]);
        }
        for (int i = 0; i < eqp.size(); i++) {
            if (eqp[i].first)
                window->draw(eqp[i].second);
        }
        window->draw(back);
        if (isDraggedFlag && isDraggedInv >= 0) {
            window->draw(inventory[isDraggedInv]);
        }
        else if (isDraggedFlag && isDraggedEqp >= 0) {
            window->draw(eqp[isDraggedEqp].second);
        }
        if (hovering) {
            window->draw(hover_frame);
            window->draw(hover);
        }
        if (hovering_compare) {
            window->draw(hover_frame_compare);
            window->draw(hover_compare);
        }
        window->display();
    }
    time.timeFlow();
    time.resume();
}

void game::mainMenu (sf::RenderWindow* window) {
    Button play(170.f, 150.f, window, "..\\src\\textures\\background\\MainMenu\\PL\\graj_button.png");
    Button options(170.f, 200.f, window, "..\\src\\textures\\background\\MainMenu\\PL\\opcje_button.png");
    Button quit(470.f, 280.f, window, "..\\src\\textures\\background\\MainMenu\\PL\\wyjdz_button.png");
    Button credits(30.f, 280.f, window, "..\\src\\textures\\background\\MainMenu\\PL\\podziekowania_button.png");
    if (option.getLanguage() == Language::ENG) {
        play.setNewTexturePath("..\\src\\textures\\background\\MainMenu\\ENG\\play_button.png");
        options.setNewTexturePath("..\\src\\textures\\background\\MainMenu\\ENG\\options_button.png");
        quit.setNewTexturePath("..\\src\\textures\\background\\MainMenu\\ENG\\quit_button.png");
        credits.setNewTexturePath("..\\src\\textures\\background\\MainMenu\\ENG\\credits_button.png");
    }
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
                optionsG(window);
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
    if (!frame.loadFromFile("..\\src\\textures\\GUI\\324x44border.png")) {
        std::cerr << "Failed to load texture from file: " << "..\\src\\textures\\GUI\\324x44border.png" << std::endl;
        throw std::runtime_error("Failed to load texture from file: ..\\src\\textures\\GUI\\324x44border.png");
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

void game::createhero (sf::RenderWindow* window) {
    sf::Texture choose;
    if (option.getLanguage() == Language::ENG && !choose.loadFromFile("..\\src\\textures\\background\\Saves\\choose class.png")) {
        std::cerr << "Failed to load texture from file: " << "..\\src\\textures\\background\\Saves\\choose class.png" << std::endl;
        throw std::runtime_error("Failed to load texture from file: ..\\src\\textures\\background\\Saves\\choose class.png");
    }
    else if (option.getLanguage() == Language::PL && !choose.loadFromFile("..\\src\\textures\\background\\Saves\\wybierz klase.png")) {
        std::cerr << "Failed to load texture from file: " << "..\\src\\textures\\background\\Saves\\wybierz klase.png" << std::endl;
        throw std::runtime_error("Failed to load texture from file: ..\\src\\textures\\background\\Saves\\wybierz klase.png");
    }
    std::string name = "BlankName";
    sf::Sprite ch(choose);
    Button mage(240.f, 100.f, window, "..\\src\\textures\\background\\Saves\\classes\\mage.png");
    Button warr(300.f, 100.f, window, "..\\src\\textures\\background\\Saves\\classes\\warrior.png");
    Button arch(360.f, 100.f, window, "..\\src\\textures\\background\\Saves\\classes\\archer.png");
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
        std::cerr << "Nie udało się otworzyć pliku: " << filename << std::endl;
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

void game::saveRead (sf::RenderWindow* window, std::string filename) {
    if (!isFileEmpty(filename)) {
        if (hero->load_from_file(filename, hero)) {
            if (hero->prologueState()) {
                setLocation(Location::City);
                loadBlacksmithInv();
                time.resetTimeMorning();
            }
            else
                lvl0(window);
        }
    }
    else {
        createhero(window);
        setLocation(Location::City);
        lvl0(window);
    }
}

std::string game::getTextSave (std::string filename) {
    std::string t;
    if (!isFileEmpty(filename)) {
        std::ifstream file(filename);
        std::string temp;
        int tempint;
        if (option.getLanguage() == Language::ENG)
            t = "Class:\n  ";
        else if (option.getLanguage() == Language::PL)
            t = "Klasa:\n  ";
        file >> temp;
        if (option.getLanguage() == Language::ENG)
            t += temp;
        else if (option.getLanguage() == Language::PL) {
            if (temp == "Mage")
                t += " Mag";
            else if (temp == "Warrior")
                t += " Wojownik";
            else if (temp == "Archer")
                t += " Łucznik";
        }
        file >> temp;
        if (option.getLanguage() == Language::ENG)
            t += "\nName:\n  ";
        else if (option.getLanguage() == Language::PL)
            t += "\nImię:\n  ";
        t += temp;
        file >> tempint;
        int hour = tempint / 60 / 60;
        int minute = tempint / 60 % 60;
        if (option.getLanguage() == Language::ENG)
            t += "\nPlaytime:\n  ";
        else if (option.getLanguage() == Language::PL)
            t += "\nCzas gry:\n  ";
        t += (hour < 10? "0" : "") + std::to_string(hour) + ":" + (minute < 10? "0" : "") + std::to_string(minute);
        file.close();
    }
    else if (option.getLanguage() == Language::ENG) {
        t = "   Empty...\n   Click to\n     start \n     a new\n   jurney!";
    }
    else if (option.getLanguage() == Language::PL) {
        t = "   Pusto...\nKliknij, aby\n    zacząć \n      nową\n przygodę!";
    }
    return t;
}

void game::saves (sf::RenderWindow* window) {
    Button s1(110.f, 100.f, window, "..\\src\\textures\\background\\Saves\\save.png");
    Button s2(270.f, 100.f, window, "..\\src\\textures\\background\\Saves\\save.png");
    Button s3(430.f, 100.f, window, "..\\src\\textures\\background\\Saves\\save.png");

    Button back(170.f, 300.f, window, "..\\src\\textures\\background\\Saves\\powrot.png");
    Button del1(110.f, 230.f, window, "..\\src\\textures\\background\\MainMenu\\PL\\usun.png");
    Button del2(270.f, 230.f, window, "..\\src\\textures\\background\\MainMenu\\PL\\usun.png");
    Button del3(430.f, 230.f, window, "..\\src\\textures\\background\\MainMenu\\PL\\usun.png");
    if (option.getLanguage() == Language::ENG) {
        back.setNewTexturePath("..\\src\\textures\\background\\Saves\\go_back.png");
        del1.setNewTexturePath("..\\src\\textures\\background\\MainMenu\\ENG\\delete.png");
        del2.setNewTexturePath("..\\src\\textures\\background\\MainMenu\\ENG\\delete.png");
        del3.setNewTexturePath("..\\src\\textures\\background\\MainMenu\\ENG\\delete.png");
    }
    Button yes(364.f, 195.f, window, "..\\src\\textures\\GUI\\checkbox_yes.png");
    Button no(274.f, 195.f, window, "..\\src\\textures\\GUI\\checkbox_no.png");
    sf::Texture sure;
    if (!sure.loadFromFile("..\\src\\textures\\background\\MainMenu\\ENG\\you_sure.png") && option.getLanguage() == Language::ENG) {
        std::cerr << "Failed to load texture from file: " << "..\\src\\textures\\background\\MainMenu\\ENG\\you_sure.png" << std::endl;
        throw std::runtime_error("Failed to load texture from file: ..\\src\\textures\\background\\MainMenu\\ENG\\you_sure.png");
    }
    else if (!sure.loadFromFile("..\\src\\textures\\background\\MainMenu\\PL\\jestes_pewien.png") && option.getLanguage() == Language::PL) {
        std::cerr << "Failed to load texture from file: " << "..\\src\\textures\\background\\MainMenu\\ENG\\jestes_pewien.png" << std::endl;
        throw std::runtime_error("Failed to load texture from file: ..\\src\\textures\\background\\MainMenu\\ENG\\jestes_pewien.png");
    }
    sf::Sprite yousure(sure);
    yousure.scale({scale, scale});
    yousure.setPosition({scale * 270, scale * 128});

    std::string t1 = getTextSave("..\\saves\\saveFile1\\saveFile1.txt");
    std::string t2 = getTextSave("..\\saves\\saveFile2\\saveFile2.txt");
    std::string t3 = getTextSave("..\\saves\\saveFile3\\saveFile3.txt");
    sf::String utf32Str1 = sf::String::fromUtf8(t1.begin(), t1.end());
    sf::String utf32Str2 = sf::String::fromUtf8(t2.begin(), t2.end());
    sf::String utf32Str3 = sf::String::fromUtf8(t3.begin(), t3.end());
    sf::Text save1t(font, utf32Str1, 16 * scale);
    sf::Text save2t(font, utf32Str2, 16 * scale);
    sf::Text save3t(font, utf32Str3, 16 * scale);
    save1t.setPosition({121.f * scale, 108.f * scale});
    save2t.setPosition({281.f * scale, 108.f * scale});
    save3t.setPosition({441.f * scale, 108.f * scale});
    save1t.setFillColor(sf::Color::Black);
    save2t.setFillColor(sf::Color::Black);
    save3t.setFillColor(sf::Color::Black);

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
                    clearFile("..\\saves\\saveFile1\\saveFile1.txt");
                    clearFile("..\\saves\\saveFile1\\saveBlack1.txt");
                    delete1 = false;
                    del = false;
                }
                if (delete2 == true) {
                    clearFile("..\\saves\\saveFile2\\saveFile2.txt");
                    clearFile("..\\saves\\saveFile2\\saveBlack2.txt");
                    delete2 = false;
                    del = false;
                }
                if (delete3 == true) {
                    clearFile("..\\saves\\saveFile3\\saveFile3.txt");
                    clearFile("..\\saves\\saveFile3\\saveBlack3.txt");
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
                saveRead(window, "..\\saves\\saveFile1\\saveFile1.txt");
                break;
            }
            else if (s2.isPressed(mousePos) && del == false) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                saveRead(window, "..\\saves\\saveFile2\\saveFile2.txt");
                break;
            }
            else if (s3.isPressed(mousePos) && del == false) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                saveRead(window, "..\\saves\\saveFile3\\saveFile3.txt");
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
        window->draw(save1t);
        window->draw(save2t);
        window->draw(save3t);
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
        std::cerr << "Failed to load texture from file: " << "..\\src\\options\\options.txt" << std::endl;
        throw std::runtime_error("Failed to load texture from file: ..\\src\\options\\options.txt");
    }
    Button general(66.f, 10.f, window, "..\\src\\textures\\background\\Options\\PL\\ogolne.png");
    Button sound(247.f, 10.f, window, "..\\src\\textures\\background\\Options\\PL\\dzwiek.png");
    Button graphics(435.f, 10.f, window, "..\\src\\textures\\background\\Options\\PL\\grafika.png");
    Button back(170.f, 300.f, window, "..\\src\\textures\\background\\Saves\\powrot.png");
    std::string languagePath = "..\\src\\textures\\background\\Options\\PL\\jezyk.png";
    std::string tutorialsPath = "..\\src\\textures\\background\\Options\\PL\\samouczki.png";
    if (option.getLanguage() == Language::ENG) {
        general.setNewTexturePath("..\\src\\textures\\background\\Options\\ENG\\general.png");
        sound.setNewTexturePath("..\\src\\textures\\background\\Options\\ENG\\sound.png");
        graphics.setNewTexturePath("..\\src\\textures\\background\\Options\\ENG\\graphics.png");
        back.setNewTexturePath("..\\src\\textures\\background\\Saves\\go_back.png");
        languagePath = "..\\src\\textures\\background\\Options\\ENG\\language.png";
        tutorialsPath = "..\\src\\textures\\background\\Options\\ENG\\tutorials.png";
    }
    sf::Texture language;
    sf::Texture tutorials;
    if (!language.loadFromFile(languagePath)) {
        std::cerr << "Failed to load texture from file: " << languagePath << std::endl;
        throw std::runtime_error("Failed to load texture from file: " + languagePath);
    }
    if (!tutorials.loadFromFile(tutorialsPath)) {
        std::cerr << "Failed to load texture from file: " << tutorialsPath << std::endl;
        throw std::runtime_error("Failed to load texture from file: " + tutorialsPath);
    }
    sf::Sprite lang(language);
    sf::Sprite tutorial(tutorials);
    lang.setPosition({scale * 15.f, scale * 70.f});
    tutorial.setPosition({scale * 15.f, scale * 120.f});
    lang.scale({scale, scale});
    tutorial.scale({scale, scale});
    Button checkboxOff(415.f, 120.f, window, "..\\src\\textures\\GUI\\checkbox_no.png");
    Button checkboxOn(415.f, 120.f, window, "..\\src\\textures\\GUI\\checkbox_yes.png");
    Button currentLng(370.f, 70.f, window, "..\\src\\textures\\background\\Options\\ENG\\eng.png");
    Button nextLng(370.f, 105.f, window, "..\\src\\textures\\background\\Options\\PL\\pl.png");
    if (option.getLanguage() == Language::PL) {
        currentLng.setNewTexturePath("..\\src\\textures\\background\\Options\\PL\\pl.png");
        nextLng.setNewTexturePath("..\\src\\textures\\background\\Options\\ENG\\eng.png");
    }
    bool choosingLanguage = false;
    bool checkbox = option.getTutorials();
    sf::Texture background;
    if (!background.loadFromFile("..\\src\\textures\\background\\Options\\options_frame.png")) {
        std::cerr << "Failed to load texture from file: " << "..\\src\\textures\\background\\Options\\options_frame.png" << std::endl;
        throw std::runtime_error("Failed to load texture from file: ..\\src\\textures\\background\\Options\\options_frame.png");
    }
    sf::Sprite bg(background);
    bg.setPosition({0.f, scale * 45.f});
    bg.scale({scale, scale});

    Location previousLocation = getLocation();

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window->close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            if (back.isPressed(mousePos) && !choosingLanguage) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
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
                    currentLng.setNewTexturePath("..\\src\\textures\\background\\Options\\PL\\pl.png");
                    nextLng.setNewTexturePath("..\\src\\textures\\background\\Options\\ENG\\eng.png");
                }
                else {
                    option.setLanguage(Language::ENG);
                    currentLng.setNewTexturePath("..\\src\\textures\\background\\Options\\ENG\\eng.png");
                    nextLng.setNewTexturePath("..\\src\\textures\\background\\Options\\PL\\pl.png");
                }
            }
            else if (graphics.isPressed(mousePos) && !choosingLanguage) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                setLocation(Location::OptionsGraph);
                option.saveToFile();
            }
            else if (sound.isPressed(mousePos) && !choosingLanguage) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                setLocation(Location::OptionsS);
                option.saveToFile();
            }
        }

        if (getLocation() == Location::OptionsS) {
            if (!optionsS(window))
                break;
        }
        else if (getLocation() == Location::OptionsGraph) {
            if (!optionsGraph(window))
                break;
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
    setLocation(previousLocation);
}

bool game::optionsGraph (sf::RenderWindow* window) {
    Button general(66.f, 10.f, window, "..\\src\\textures\\background\\Options\\PL\\ogolne.png");
    Button sound(247.f, 10.f, window, "..\\src\\textures\\background\\Options\\PL\\dzwiek.png");
    Button graphics(435.f, 10.f, window, "..\\src\\textures\\background\\Options\\PL\\grafika.png");
    Button back(170.f, 300.f, window, "..\\src\\textures\\background\\Saves\\powrot.png");
    std::string limPath = "..\\src\\textures\\background\\Options\\PL\\limit_FPS.png";
    std::string modePath = "..\\src\\textures\\background\\Options\\PL\\tryb_wyswietlania.png";
    std::string resolutionPath = "..\\src\\textures\\background\\Options\\PL\\rozdzielcosc.png";
    if (option.getLanguage() == Language::ENG) {
        general.setNewTexturePath("..\\src\\textures\\background\\Options\\ENG\\general.png");
        sound.setNewTexturePath("..\\src\\textures\\background\\Options\\ENG\\sound.png");
        graphics.setNewTexturePath("..\\src\\textures\\background\\Options\\ENG\\graphics.png");
        back.setNewTexturePath("..\\src\\textures\\background\\Saves\\go_back.png");
        limPath = "..\\src\\textures\\background\\Options\\ENG\\FPS_limit.png";
        modePath = "..\\src\\textures\\background\\Options\\ENG\\display_mode.png";
        resolutionPath = "..\\src\\textures\\background\\Options\\ENG\\resolution.png";
    }
    sf::Texture lim;
    sf::Texture mode;
    sf::Texture resolution;


    if (!lim.loadFromFile(limPath)) {
        std::cerr << "Failed to load texture from file: " << limPath << std::endl;
        throw std::runtime_error("Failed to load texture from file: " + limPath);
    }
    if (!mode.loadFromFile(modePath)) {
        std::cerr << "Failed to load texture from file: " << modePath << std::endl;
        throw std::runtime_error("Failed to load texture from file: " + modePath);
    }
    if (!resolution.loadFromFile(resolutionPath)) {
        std::cerr << "Failed to load texture from file: " << resolutionPath << std::endl;
        throw std::runtime_error("Failed to load texture from file: " + resolutionPath);
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

    Button currentFPS(395.f, 70.f, window, "..\\src\\textures\\background\\Options\\ENG\\60.png");
    Button secondFPS(395.f, 105.f, window, "..\\src\\textures\\background\\Options\\ENG\\30.png");
    Button thirdFPS(395.f, 140.f, window, "..\\src\\textures\\background\\Options\\ENG\\140.png");
    if (option.getFPS() == FPS::_30) {
        currentFPS.setNewTexturePath("..\\src\\textures\\background\\Options\\ENG\\30.png");
        secondFPS.setNewTexturePath("..\\src\\textures\\background\\Options\\ENG\\60.png");
    }
    else if (option.getFPS() == FPS::_144) {
        currentFPS.setNewTexturePath("..\\src\\textures\\background\\Options\\ENG\\140.png");
        thirdFPS.setNewTexturePath("..\\src\\textures\\background\\Options\\ENG\\60.png");
    }
    std::string f1;
    std::string f2;
    std::string f3;
    if (option.getLanguage() == Language::ENG) {
        f1 = "..\\src\\textures\\background\\Options\\ENG\\fullscreen.png";
        f2 = "..\\src\\textures\\background\\Options\\ENG\\borderless.png";
        f3 = "..\\src\\textures\\background\\Options\\ENG\\window.png";
    }
    else if (option.getLanguage() == Language::PL) {
        f1 = "..\\src\\textures\\background\\Options\\ENG\\fullscreen.png";
        f2 = "..\\src\\textures\\background\\Options\\ENG\\borderless.png";
        f3 = "..\\src\\textures\\background\\Options\\PL\\okno.png";
    }

    Button currentMode(370.f, 120.f, window, f1);
    Button secondMode(370.f, 155.f, window, f2);
    Button thirdMode(370.f, 190.f, window, f3);
    if (option.getMode() == Mode::borderless) {
        currentMode.setNewTexturePath(f2);
        secondMode.setNewTexturePath(f1);
    }
    else if (option.getMode() == Mode::windowed) {
        currentMode.setNewTexturePath(f3);
        secondMode.setNewTexturePath(f1);
        thirdMode.setNewTexturePath(f2);
    }
    Button currentRes(395.f, 170.f, window, "..\\src\\textures\\background\\Options\\1080p.png");
    Button secondRes(395.f, 205.f, window, "..\\src\\textures\\background\\Options\\360p.png");
    Button thirdRes(395.f, 240.f,window, "..\\src\\textures\\background\\Options\\1440p.png");
    if (option.getResolution() == Resolution::p360) {
        currentRes.setNewTexturePath("..\\src\\textures\\background\\Options\\360p.png");
        secondRes.setNewTexturePath("..\\src\\textures\\background\\Options\\1080p.png");
    }
    else if (option.getResolution() == Resolution::p1440) {
        currentRes.setNewTexturePath("..\\src\\textures\\background\\Options\\1440p.png");
        thirdRes.setNewTexturePath("..\\src\\textures\\background\\Options\\1080p.png");
    }
    bool choosingFPS = false;
    bool choosingMode = false;
    bool choosingResolution = false;

    sf::Texture background;
    if (!background.loadFromFile("..\\src\\textures\\background\\Options\\options_frame.png")) {
        std::cerr << "Failed to load texture from file: " << "..\\src\\textures\\background\\Options\\options_frame.png" << std::endl;
        throw std::runtime_error("Failed to load texture from file: ..\\src\\textures\\background\\Options\\options_frame.png");
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
                setLocation(Location::OptionsG);
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
                return false;
            }
            else if (general.isPressed(mousePos) && !choosingFPS && !choosingMode && !choosingResolution) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                setLocation(Location::OptionsG);
                option.saveToFile();
                return true;
            }
            else if (sound.isPressed(mousePos) && !choosingFPS && !choosingMode && !choosingResolution) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                setLocation(Location::OptionsS);
                option.saveToFile();
                return true;
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
                    currentFPS.setNewTexturePath("..\\src\\textures\\background\\Options\\ENG\\30.png");
                    secondFPS.setNewTexturePath("..\\src\\textures\\background\\Options\\ENG\\60.png");
                    thirdFPS.setNewTexturePath("..\\src\\textures\\background\\Options\\ENG\\140.png");
                    window->setFramerateLimit(30);
                }
                else if (option.getFPS() == FPS::_30) {
                    option.setFPS(FPS::_60);
                    currentFPS.setNewTexturePath("..\\src\\textures\\background\\Options\\ENG\\60.png");
                    secondFPS.setNewTexturePath("..\\src\\textures\\background\\Options\\ENG\\30.png");
                    window->setFramerateLimit(60);
                }
                else {
                    option.setFPS(FPS::_30);
                    currentFPS.setNewTexturePath("..\\src\\textures\\background\\Options\\ENG\\30.png");
                    secondFPS.setNewTexturePath("..\\src\\textures\\background\\Options\\ENG\\60.png");
                    thirdFPS.setNewTexturePath("..\\src\\textures\\background\\Options\\ENG\\140.png");
                    window->setFramerateLimit(30);
                }
            }
            else if (thirdFPS.isPressed(mousePos) && choosingFPS && !choosingMode && !choosingResolution) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                choosingFPS = false;
                if (option.getFPS() == FPS::_60) {
                    option.setFPS(FPS::_144);
                    currentFPS.setNewTexturePath("..\\src\\textures\\background\\Options\\ENG\\140.png");
                    thirdFPS.setNewTexturePath("..\\src\\textures\\background\\Options\\ENG\\60.png");
                    window->setFramerateLimit(144);
                }
                else if (option.getFPS() == FPS::_30) {
                    option.setFPS(FPS::_144);
                    currentFPS.setNewTexturePath("..\\src\\textures\\background\\Options\\ENG\\140.png");
                    secondFPS.setNewTexturePath("..\\src\\textures\\background\\Options\\ENG\\30.png");
                    thirdFPS.setNewTexturePath("..\\src\\textures\\background\\Options\\ENG\\60.png");
                    window->setFramerateLimit(144);
                }
                else {
                    option.setFPS(FPS::_60);
                    currentFPS.setNewTexturePath("..\\src\\textures\\background\\Options\\ENG\\60.png");
                    thirdFPS.setNewTexturePath("..\\src\\textures\\background\\Options\\ENG\\140.png");
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
                    currentMode.setNewTexturePath(f1);
                    secondMode.setNewTexturePath(f2);
                }
                else if (option.getMode() == Mode::fullscreen) {
                    option.setMode(Mode::borderless);
                    currentMode.setNewTexturePath(f2);
                    secondMode.setNewTexturePath(f1);
                }
                else {
                    option.setMode(Mode::fullscreen);
                    currentMode.setNewTexturePath(f1);
                    secondMode.setNewTexturePath(f2);
                    thirdMode.setNewTexturePath(f3);
                }
            }
            else if (thirdMode.isPressed(mousePos) && !choosingFPS && choosingMode && !choosingResolution) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                choosingMode = false;
                if (option.getMode() == Mode::borderless) {
                    option.setMode(Mode::windowed);
                    currentMode.setNewTexturePath(f3);
                    secondMode.setNewTexturePath(f1);
                    thirdMode.setNewTexturePath(f2);
                }
                else if (option.getMode() == Mode::fullscreen) {
                    option.setMode(Mode::windowed);
                    currentMode.setNewTexturePath(f3);
                    secondMode.setNewTexturePath(f1);
                    thirdMode.setNewTexturePath(f2);
                }
                else {
                    option.setMode(Mode::borderless);
                    currentMode.setNewTexturePath(f2);
                    thirdMode.setNewTexturePath(f3);
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
                    currentRes.setNewTexturePath("..\\src\\textures\\background\\Options\\1080p.png");
                    secondRes.setNewTexturePath("..\\src\\textures\\background\\Options\\360p.png");
                }
                else if (option.getResolution() == Resolution::p1080) {
                    option.setResolution(Resolution::p360);
                    currentRes.setNewTexturePath("..\\src\\textures\\background\\Options\\360p.png");
                    secondRes.setNewTexturePath("..\\src\\textures\\background\\Options\\1080p.png");
                }
                else {
                    option.setResolution(Resolution::p360);
                    currentRes.setNewTexturePath("..\\src\\textures\\background\\Options\\360p.png");
                    secondRes.setNewTexturePath("..\\src\\textures\\background\\Options\\1080p.png");
                    thirdRes.setNewTexturePath("..\\src\\textures\\background\\Options\\1440p.png");
                }
            }
            else if (thirdRes.isPressed(mousePos) && !choosingFPS && !choosingMode && choosingResolution) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                choosingResolution = false;
                if (option.getResolution() == Resolution::p360) {
                    option.setResolution(Resolution::p1440);
                    currentRes.setNewTexturePath("..\\src\\textures\\background\\Options\\1440p.png");
                    secondRes.setNewTexturePath("..\\src\\textures\\background\\Options\\360p.png");
                    thirdRes.setNewTexturePath("..\\src\\textures\\background\\Options\\1080p.png");
                }
                else if (option.getResolution() == Resolution::p1080) {
                    option.setResolution(Resolution::p1440);
                    currentRes.setNewTexturePath("..\\src\\textures\\background\\Options\\1440p.png");
                    secondRes.setNewTexturePath("..\\src\\textures\\background\\Options\\360p.png");
                    thirdRes.setNewTexturePath("..\\src\\textures\\background\\Options\\1080p.png");
                }
                else {
                    option.setResolution(Resolution::p1080);
                    currentRes.setNewTexturePath("..\\src\\textures\\background\\Options\\1080p.png");
                    thirdRes.setNewTexturePath("..\\src\\textures\\background\\Options\\1440p.png");
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
    return false;
}

bool game::optionsS (sf::RenderWindow* window) {
    Button general(66.f, 10.f, window, "..\\src\\textures\\background\\Options\\PL\\ogolne.png");
    Button sound(247.f, 10.f, window, "..\\src\\textures\\background\\Options\\PL\\dzwiek.png");
    Button graphics(435.f, 10.f, window, "..\\src\\textures\\background\\Options\\PL\\grafika.png");
    Button back(170.f, 300.f, window, "..\\src\\textures\\background\\Saves\\powrot.png");
    std::string enviromentPath = "..\\src\\textures\\background\\Options\\PL\\glosnosc_dzwiekow_otoczenia.png";
    std::string effectPath = "..\\src\\textures\\background\\Options\\PL\\glosnosc_efektow_dzwiekowych.png";
    std::string musicPath = "..\\src\\textures\\background\\Options\\PL\\glosnosc_muzyki.png";
    std::string mainPath = "..\\src\\textures\\background\\Options\\PL\\glosnosc_glowna.png";
    if (option.getLanguage() == Language::ENG) {
        general.setNewTexturePath("..\\src\\textures\\background\\Options\\ENG\\general.png");
        sound.setNewTexturePath("..\\src\\textures\\background\\Options\\ENG\\sound.png");
        graphics.setNewTexturePath("..\\src\\textures\\background\\Options\\ENG\\graphics.png");
        back.setNewTexturePath("..\\src\\textures\\background\\Saves\\go_back.png");
        enviromentPath = "..\\src\\textures\\background\\Options\\ENG\\enviromental_sound_volume.png";
        effectPath = "..\\src\\textures\\background\\Options\\ENG\\sound_effects_volume.png";
        musicPath = "..\\src\\textures\\background\\Options\\ENG\\music_volume.png";
        mainPath = "..\\src\\textures\\background\\Options\\ENG\\master_volume.png";
    }
    sf::Texture enviroment;
    sf::Texture effect;
    sf::Texture music;
    sf::Texture main;
    sf::Texture background;
    if (!enviroment.loadFromFile(enviromentPath)) {
        std::cerr << "Failed to load texture from file: " << enviromentPath << std::endl;
        throw std::runtime_error("Failed to load texture from file: " + enviromentPath);
    }
    if (!effect.loadFromFile(effectPath)) {
        std::cerr << "Failed to load texture from file: " << effectPath << std::endl;
        throw std::runtime_error("Failed to load texture from file: " + effectPath);
    }
    if (!music.loadFromFile(musicPath)) {
        std::cerr << "Failed to load texture from file: " << musicPath << std::endl;
        throw std::runtime_error("Failed to load texture from file: " + musicPath);
    }
    if (!main.loadFromFile(mainPath)) {
        std::cerr << "Failed to load texture from file: " << mainPath << std::endl;
        throw std::runtime_error("Failed to load texture from file: " + mainPath);
    }
    if (!background.loadFromFile("..\\src\\textures\\background\\Options\\options_frame.png")) {
        std::cerr << "Failed to load texture from file: " << "..\\src\\textures\\background\\Options\\options_frame.png" << std::endl;
        throw std::runtime_error("Failed to load texture from file: ..\\src\\textures\\background\\Options\\options_frame.png");
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
                setLocation(Location::OptionsG);
                option.saveToFile();
                return false;
            }
            else if (general.isPressed(mousePos)) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                setLocation(Location::OptionsG);
                option.saveToFile();
                return true;
            }
            else if (graphics.isPressed(mousePos)) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                setLocation(Location::OptionsGraph);
                option.saveToFile();
                return true;
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
    return false;
}

bool game::pauseMenu (sf::RenderWindow* window) {
    Button options(170.f, 200.f, window, "..\\src\\textures\\background\\MainMenu\\PL\\opcje_button.png");
    Button quit(270.f, 280.f, window, "..\\src\\textures\\background\\MainMenu\\PL\\wyjdz_button.png");
    Button back(593.f, 44.f, window, "..\\src\\textures\\GUI\\x.png");
    if (option.getLanguage() == Language::ENG) {
        options.setNewTexturePath("..\\src\\textures\\background\\MainMenu\\ENG\\options_button.png");
        quit.setNewTexturePath("..\\src\\textures\\background\\MainMenu\\ENG\\quit_button.png");
    }
    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window->close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            if (back.isPressed(mousePos)) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                setLocation(Location::City);
                return true;
            }
            else if (options.isPressed(mousePos)) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                optionsG(window);
            }
            else if (quit.isPressed(mousePos)) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                setLocation(Location::Quit);
                return false;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            while (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape));
            setLocation(Location::City);
            return true;
        }

        window->clear();
        window->draw(options);
        window->draw(quit);
        window->draw(back);
        window->display();
    }
    return false;
}

void game::worldMap (sf::RenderWindow* window) {
    Button back(593.f, 44.f, window, "..\\src\\textures\\GUI\\x.png");
    Button forestButton(100.f, 100.f, window, "..\\src\\textures\\GUI\\32x32border.png");
    Button cavesButton(200.f, 100.f, window, "..\\src\\textures\\GUI\\32x32border.png");
    Button icePeaksButton(300.f, 100.f, window, "..\\src\\textures\\GUI\\32x32border.png");
    Button swampButton(400.f, 100.f, window, "..\\src\\textures\\GUI\\32x32border.png");
    Button volcanoButton(500.f, 100.f, window, "..\\src\\textures\\GUI\\32x32border.png");

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window->close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            if (back.isPressed(mousePos)) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                setLocation(Location::City);
                break;
            }
            else if (forestButton.isPressed(mousePos) && isUnlocked(Location::Forest)) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                forest(window);
                if (getLocation() != Location::MainMenu && getLocation() != Location::Quit)
                    setLocation(Location::City);
                break;
            }
            else if (cavesButton.isPressed(mousePos) && isUnlocked(Location::Caves)) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                //caves(hero);
                if (getLocation() != Location::MainMenu && getLocation() != Location::Quit)
                    setLocation(Location::City);
                break;
            }
        }
        time.timeFlow();
        window->clear();
        window->draw(back);
        window->draw(forestButton);
        window->draw(cavesButton);
        window->draw(icePeaksButton);
        window->draw(swampButton);
        window->draw(volcanoButton);
        window->display();
    }
    //     else if (loc == 6 && !isUnlocked(Location::Graveyard)) {
    //         std::cout << "Location Locked." << std::endl;
    //     }
    //     else if (loc == 7 && isUnlocked(Location::Ocean)) {
    //         setLocation(Location::Ocean);
    //         std::cout << "You have entered the Ocean of Trial." << std::endl;
    //
    //
    //         break;
    //     }
    //     else if (loc == 7 && !isUnlocked(Location::Ocean)) {
    //         std::cout << "Location Locked." << std::endl;
    //     }
}

void game::city (sf::RenderWindow* window) {
    HUD gui(hero, &time, window);
    Button forge(60.f, 170.f, window, "..\\src\\textures\\background\\City\\Buildings\\blacksmith.png");
    Button tavern_building(420.f, 190.f, window, "..\\src\\textures\\background\\City\\Buildings\\tavern.png");
    Button gate(246.f, 100.f, window, "..\\src\\textures\\background\\City\\Buildings\\city_gate.png");
    Button church_building(360.f, 143.f, window, "..\\src\\textures\\background\\City\\Buildings\\church.png");
    Button inv(15.f, 45.f, window, "..\\src\\textures\\GUI\\32x32border.png");

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window->close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            if (inv.isPressed(mousePos)) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                inventory(window);
            }
            else if (forge.isPressed(mousePos)) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                blacksmith(window);
            }
            else if (church_building.isPressed(mousePos)) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                setLocation(Location::Church);
                break;
            }
            else if (gate.isPressed(mousePos)) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                setLocation(Location::Map);
                break;
            }
            else if (tavern_building.isPressed(mousePos)) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                tavern(window);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            while (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape));
            if (!pauseMenu(window)) {
                if (getLocation() != Location::Quit) {
                    setLocation(Location::MainMenu);
                }
                break;
            }
        }
        time.timeFlow();
        window->clear();
        window->draw(gate);
        window->draw(church_building);
        window->draw(forge);
        window->draw(tavern_building);
        window->draw(gui);
        window->draw(inv);
        window->display();
    }
}
