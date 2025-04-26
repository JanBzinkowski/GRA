#include "character.h"
#include "damage.h"
#include "Warrior.h"
#include "Mage.h"
#include "Archer.h"
#include <conio.h>
#include "button.h"


extern std::unordered_map<int, itemStats> itemData;

void character::startClock () {
    gameplay_time.start();
}

void character::restartClock () {
    gameplay_time.reset();
}

sf::Time character::getPlaytime () {
    playtime += gameplay_time.getElapsedTime();
    restartClock();
    return playtime;
}

void character::setPlaytime (sf::Time time) {
    playtime = time;
}

void character::setSave (const std::string fileName) {
    save = fileName;
}


const std::string character::getSave () {
    return save;
}


void character::printstatcurrent () {
    if (currenthp <= 0)
        currenthp = 0;
    std::cout << getName() << "'s stats:" << "\nCurrent HP: " << currenthp << /*"\nObecna mana: "<<currentmana<<*/"\n"
            << std::endl;
}

void character::updateStats (itemStats stats, bool equip) {
    int mod = equip? 1 : -1;
    stat.ad += stats.ad * mod;
    stat.basehp += stats.hp * mod;
    stat.mana += stats.mana * mod;
    stat.def += stats.def * mod;
    stat.speed += stats.speed * mod;
}

int character::getInvSize () const {
    return heroInv.getInvSize();
}

int character::get1stAvaiableIndex () const {
    return heroInv.get1stAvailableSlot();
}

bool character::isAvailable (const int slot) const {
    return heroInv.isAvaiable(slot);
}

void character::swapItems (size_t i, size_t x) {
    heroInv.swapItems(i, x);
}


void character::displayEqp () const {
    std::cout << "Equipment:\n" << std::endl;
    if (helmetslot) {
        itemStats stats = helmetslot->getStats();
        std::cout << "1. Helmet: " << stats.name << ",Item LVL: " << stats.itemLvl;
        if (stats.hp > 0)
            std::cout << ", HP: " << stats.hp;
        if (stats.def > 0)
            std::cout << ", DEF: " << stats.def;
        if (stats.ad > 0)
            std::cout << ", AD: " << stats.ad;
        if (stats.mana > 0)
            std::cout << ", Mana: " << stats.mana;
        if (stats.speed > 0)
            std::cout << ", Speed: " << stats.speed;
        std::cout << ")" << std::endl;
    }
    else
        std::cout << "1. Helmet: NONE" << std::endl;
    if (chestplateslot) {
        itemStats stats = chestplateslot->getStats();
        std::cout << "2. Chestplate: " << stats.name << ",Item LVL: " << stats.itemLvl;
        if (stats.hp > 0)
            std::cout << ", HP: " << stats.hp;
        if (stats.def > 0)
            std::cout << ", DEF: " << stats.def;
        if (stats.ad > 0)
            std::cout << ", AD: " << stats.ad;
        if (stats.mana > 0)
            std::cout << ", Mana: " << stats.mana;
        if (stats.speed > 0)
            std::cout << ", Speed: " << stats.speed;
        std::cout << ")" << std::endl;
    }
    else
        std::cout << "2. Chestplate: NONE" << std::endl;
    if (necklaceslot) {
        itemStats stats = necklaceslot->getStats();
        std::cout << "3. Necklace: " << stats.name << ", (Item LVL: " << stats.itemLvl;
        if (stats.hp > 0)
            std::cout << ", HP: " << stats.hp;
        if (stats.def > 0)
            std::cout << ", DEF: " << stats.def;
        if (stats.ad > 0)
            std::cout << ", AD: " << stats.ad;
        if (stats.mana > 0)
            std::cout << ", Mana: " << stats.mana;
        if (stats.speed > 0)
            std::cout << ", Speed: " << stats.speed;
        std::cout << ")" << std::endl;
    }
    else
        std::cout << "3. Necklace: NONE" << std::endl;
    if (glovesslot) {
        itemStats stats = glovesslot->getStats();
        std::cout << "4. Gloves: " << stats.name << ", (Item LVL: " << stats.itemLvl;
        if (stats.hp > 0)
            std::cout << ", HP: " << stats.hp;
        if (stats.def > 0)
            std::cout << ", DEF: " << stats.def;
        if (stats.ad > 0)
            std::cout << ", AD: " << stats.ad;
        if (stats.mana > 0)
            std::cout << ", Mana: " << stats.mana;
        if (stats.speed > 0)
            std::cout << ", Speed: " << stats.speed;
        std::cout << ")" << std::endl;
    }
    else
        std::cout << "4. Gloves: NONE" << std::endl;
    if (ringslot) {
        itemStats stats = ringslot->getStats();
        std::cout << "5. Ring: " << stats.name << ", (Item LVL: " << stats.itemLvl;
        if (stats.hp > 0)
            std::cout << ", HP: " << stats.hp;
        if (stats.def > 0)
            std::cout << ", DEF: " << stats.def;
        if (stats.ad > 0)
            std::cout << ", AD: " << stats.ad;
        if (stats.mana > 0)
            std::cout << ", Mana: " << stats.mana;
        if (stats.speed > 0)
            std::cout << ", Speed: " << stats.speed;
        std::cout << ")" << std::endl;
    }
    else
        std::cout << "5. Ring: NONE" << std::endl;
    if (leggingsslot) {
        itemStats stats = leggingsslot->getStats();
        std::cout << "6. Leeggings: " << stats.name << ", (Item LVL: " << stats.itemLvl;
        if (stats.hp > 0)
            std::cout << ", HP: " << stats.hp;
        if (stats.def > 0)
            std::cout << ", DEF: " << stats.def;
        if (stats.ad > 0)
            std::cout << ", AD: " << stats.ad;
        if (stats.mana > 0)
            std::cout << ", Mana: " << stats.mana;
        if (stats.speed > 0)
            std::cout << ", Speed: " << stats.speed;
        std::cout << ")" << std::endl;
    }
    else
        std::cout << "6. Leggings: NONE" << std::endl;
    if (bootsslot) {
        itemStats stats = bootsslot->getStats();
        std::cout << "7. Boots: " << stats.name << ", (Item LVL: " << stats.itemLvl;
        if (stats.hp > 0)
            std::cout << ", HP: " << stats.hp;
        if (stats.def > 0)
            std::cout << ", DEF: " << stats.def;
        if (stats.ad > 0)
            std::cout << ", AD: " << stats.ad;
        if (stats.mana > 0)
            std::cout << ", Mana: " << stats.mana;
        if (stats.speed > 0)
            std::cout << ", Speed: " << stats.speed;
        std::cout << ")" << std::endl;
    }
    else
        std::cout << "7. Boots: NONE" << std::endl;
    if (weaponslot) {
        itemStats stats = weaponslot->getStats();
        std::cout << "8. Weapon: " << stats.name << ", (Item LVL: " << stats.itemLvl;
        if (stats.hp > 0)
            std::cout << ", HP: " << stats.hp;
        if (stats.def > 0)
            std::cout << ", DEF: " << stats.def;
        if (stats.ad > 0)
            std::cout << ", AD: " << stats.ad;
        if (stats.mana > 0)
            std::cout << ", Mana: " << stats.mana;
        if (stats.speed > 0)
            std::cout << ", Speed: " << stats.speed;
        std::cout << ")" << std::endl;
    }
    else
        std::cout << "8. Weapon: NONE" << std::endl;
}

Item character::getItemFromInventory (int slot) const {
    return heroInv.inventory[slot];
}

bool character::checkIfEqp (itemType type) const {
    switch (type) {
        case itemType::Helmet: {
            if (helmetslot)
                return true;
            break;
        }
        case itemType::Chestplate: {
            if (chestplateslot)
                return true;
            break;
        }
        case itemType::Necklace: {
            if (necklaceslot)
                return true;
            break;
        }
        case itemType::Gloves: {
            if (glovesslot)
                return true;
            break;
        }
        case itemType::Ring: {
            if (ringslot)
                return true;
            break;
        }
        case itemType::Leggings: {
            if (leggingsslot)
                return true;
            break;
        }
        case itemType::Boots: {
            if (bootsslot)
                return true;
            break;
        }
        case itemType::Weapon: {
            if (weaponslot)
                return true;
            break;
        }
        default:
            return false;
    }
    return false;
}

Item character::getItemFromEqp (itemType type) const {
    switch (type) {
        case itemType::Helmet: {
            if (helmetslot)
                return *helmetslot;
            break;
        }
        case itemType::Chestplate: {
            if (chestplateslot)
                return *chestplateslot;
            break;
        }
        case itemType::Necklace: {
            if (necklaceslot)
                return *necklaceslot;
            break;
        }
        case itemType::Gloves: {
            if (glovesslot)
                return *glovesslot;
            break;
        }
        case itemType::Ring: {
            if (ringslot)
                return *ringslot;
            break;
        }
        case itemType::Leggings: {
            if (leggingsslot)
                return *leggingsslot;
            break;
        }
        case itemType::Boots: {
            if (bootsslot)
                return *bootsslot;
            break;
        }
        case itemType::Weapon: {
            if (weaponslot)
                return *weaponslot;
            break;
        }
        default:
            return Item(0);
    }
    return Item(0);
}


void character::addToInv (const Item& item, const int slot) {
    heroInv.addItem(item, slot);
}

void character::removeFromInv (const int slot) {
    heroInv.removeItem(slot);
}


void character::equipItem (const Item& item) {
    itemType type = item.getType();
    unequip(type);
    switch (type) {
        case itemType::Helmet: {
            helmetslot = item;
            break;
        }
        case itemType::Chestplate: {
            chestplateslot = item;
            break;
        }
        case itemType::Necklace: {
            necklaceslot = item;
            break;
        }
        case itemType::Gloves: {
            glovesslot = item;
            break;
        }
        case itemType::Ring: {
            ringslot = item;
            break;
        }
        case itemType::Leggings: {
            leggingsslot = item;
            break;
        }
        case itemType::Boots: {
            bootsslot = item;
            break;
        }
        case itemType::Weapon: {
            weaponslot = item;
            break;
        }
    }
    itemStats stats = item.getStats();
    updateStats(stats, true);
}

void character::equipFromInv (const int& slot) {
    bool remove = false;
    Item item = heroInv.getItemByIndex(slot);
    itemType type = item.getType();
    if (checkIfEqp(type))
        unequip(type, slot);
    else
        remove = true;
    switch (type) {
        case itemType::Helmet: {
            helmetslot = item;
            break;
        }
        case itemType::Chestplate: {
            chestplateslot = item;
            break;
        }
        case itemType::Necklace: {
            necklaceslot = item;
            break;
        }
        case itemType::Gloves: {
            glovesslot = item;
            break;
        }
        case itemType::Ring: {
            ringslot = item;
            break;
        }
        case itemType::Leggings: {
            leggingsslot = item;
            break;
        }
        case itemType::Boots: {
            bootsslot = item;
            break;
        }
        case itemType::Weapon: {
            weaponslot = item;
            break;
        }
    }
    itemStats stats = item.getStats();
    updateStats(stats, true);
    if (remove)
        removeFromInv(slot);
}

void character::unequip (const itemType type, int slot) {
    if (slot < 0)
        slot = heroInv.get1stAvailableSlot();
    itemStats stats = Item(0).getStats();
    switch (type) {
        case itemType::Helmet: {
            if (helmetslot) {
                stats = helmetslot->getStats();
                heroInv.inventory[slot] = *helmetslot;
                helmetslot.reset();
            }
            break;
        }
        case itemType::Chestplate: {
            if (chestplateslot) {
                stats = chestplateslot->getStats();
                heroInv.inventory[slot] = *chestplateslot;
                chestplateslot.reset();
            }
            break;
        }
        case itemType::Necklace: {
            if (necklaceslot) {
                stats = necklaceslot->getStats();
                heroInv.inventory[slot] = *necklaceslot;
                necklaceslot.reset();
            }
            break;
        }
        case itemType::Gloves: {
            if (glovesslot) {
                stats = glovesslot->getStats();
                heroInv.inventory[slot] = *glovesslot;
                glovesslot.reset();
            }
            break;
        }
        case itemType::Ring: {
            if (ringslot) {
                stats = ringslot->getStats();
                heroInv.inventory[slot] = *ringslot;
                ringslot.reset();
            }
            break;
        }
        case itemType::Leggings: {
            if (leggingsslot) {
                stats = leggingsslot->getStats();
                heroInv.inventory[slot] = *leggingsslot;
                leggingsslot.reset();
            }
            break;
        }
        case itemType::Boots: {
            if (bootsslot) {
                stats = bootsslot->getStats();
                heroInv.inventory[slot] = *bootsslot;
                bootsslot.reset();
            }
            break;
        }
        case itemType::Weapon: {
            if (weaponslot) {
                stats = weaponslot->getStats();
                heroInv.inventory[slot] = *weaponslot;
                weaponslot.reset();
            }
            break;
        }
        default: {
            return;
        }
    }
    updateStats(stats, false);
}

void character::removeFromEqp (const itemType type) {
    Item item(0);
    switch (type) {
        case itemType::Helmet: {
            item = *helmetslot;
            helmetslot = std::nullopt;
            break;
        }
        case itemType::Chestplate: {
            item = *chestplateslot;
            chestplateslot = std::nullopt;
            break;
        }
        case itemType::Necklace: {
            item = *necklaceslot;
            necklaceslot = std::nullopt;
            break;
        }
        case itemType::Gloves: {
            item = *glovesslot;
            glovesslot = std::nullopt;
            break;
        }
        case itemType::Ring: {
            item = *ringslot;
            ringslot = std::nullopt;
            break;
        }
        case itemType::Leggings: {
            item = *leggingsslot;
            leggingsslot = std::nullopt;
            break;
        }
        case itemType::Boots: {
            item = *bootsslot;
            bootsslot = std::nullopt;
            break;
        }
        case itemType::Weapon: {
            item = *weaponslot;
            weaponslot = std::nullopt;
            break;
        }
    }
    updateStats(item.getStats(), false);
}


void character::lvlup () {
    int exp_treshold = 5 * pow(stat.lvl, 2.2) + 25;
    if (exp >= exp_treshold) {
        exp -= exp_treshold;
        stat.lvl++;
        std::cout << "\nCongratulations! You have leveled up to level " << stat.lvl << "!\n" << std::endl;
        std::cout << "Atk: " << stat.ad << " + " << incstats.adinc << std::endl;
        std::cout << "Def: " << stat.def << " + " << incstats.definc << std::endl;
        std::cout << "HP: " << stat.basehp << " + " << incstats.basehpinc * stat.lvl << std::endl;
        std::cout << "Mana: " << stat.mana << " + " << incstats.manainc << std::endl;
        std::cout << "Gold Coins: " << currentgold << " + " << 5 * stat.lvl << std::endl;
        std::cout << "\nHP and mana restored." << std::endl;

        stat.ad += incstats.adinc;
        stat.basehp += incstats.basehpinc * stat.lvl;
        stat.def += incstats.definc;
        stat.mana += incstats.manainc;
        currentgold += 5 * stat.lvl;
        currenthp = stat.basehp;
        currentmana = stat.mana;
        if (stat.lvl == 2) {
            std::cout <<
                    "\n-------------------------------------------------------------------------------------------------------------------------------"
                    << std::endl;
            std::cout << "\n\nYou have unlocked:\n  - Potions\n  - Items" << std::endl;
        }
        if (stat.lvl == 5) {
            std::cout <<
                    "\n-------------------------------------------------------------------------------------------------------------------------------"
                    << std::endl;
            std::cout << "\n\nYou have unlocked:\n  - Potion of Mana Regeneration" << std::endl;
        }
        if (stat.lvl == 8) {
            std::cout <<
                    "\n-------------------------------------------------------------------------------------------------------------------------------"
                    << std::endl;
            std::cout << "\n\nYou have unlocked:\n  - Potion of Fast Action\n  - Uncommon Items" << std::endl;
        }
    }
}

void character::enemyLvlUp () {
    stat.lvl++;
    stat.ad += incstats.adinc;
    stat.basehp += incstats.basehpinc * stat.lvl;
    stat.def += incstats.definc;
}

void character::hpcheck () {
    if (currenthp <= 0) {
        currenthp = 0;
        printstatcurrent();
        std::cout <<
                "\nYou fainted. Someone has got you back to the city, but he took 50% of your resources as a thank you."
                << std::endl;
        currentgold /= 2;
        currenthp = stat.basehp;
        currentmana += stat.mana;
    }
}

void character::pray () {
    currenthp = stat.basehp;
}

float character::getAtkChance (character*& atk, character& def) const {
    int lvldif = (atk->getLvl()) - (def.getLvl());
    float chance;
    if (atktypenb == 1) {
        chance = 0.95f + 0.3 * lvldif;
        if (chance > 1.0f)
            chance = 1.0f;
        return chance;
    }
    if (atktypenb == 2) {
        chance = 0.75f + 0.3 * lvldif;
        if (chance > 1.0f)
            chance = 1.0f;
        return chance;
    }
    if (atktypenb == 3) {
        chance = 0.50f + 0.3 * lvldif;
        if (chance > 1.0f)
            chance = 1.0f;
        return chance;
    }
    return 0;
}

float character::getMultDmg () const {
    if (atktypenb == 1) {
        return 1;
    }
    if (atktypenb == 2) {
        return 1.3f;
    }
    if (atktypenb == 3) {
        return 1.8f;
    }
    return 0;
}

void character::goldInc (int gold) {
    currentgold += gold;
}

void character::expInc (int experience) {
    exp += experience;
}

int character::getMaxHP () const {
    return stat.basehp;
}

int character::getLvl () const {
    return stat.lvl;
}

int character::getAd () const {
    return stat.ad;
}

int character::getDef () const {
    return stat.def;
}

int character::getMaxMana () const {
    return stat.mana;
}

std::string character::getName () const {
    return name;
}

std::string character::getPath () const {
    return stat.path;
}

int character::getSpeed () const {
    return stat.speed;
}

int character::getMaxHPinc () const {
    return incstats.basehpinc;
}

int character::getAdInc () const {
    return incstats.adinc;
}

int character::getDefInc () const {
    return incstats.definc;
}

int character::getMaxManaInc () const {
    return incstats.manainc;
}

int character::getSpeedInc () const {
    return incstats.speedinc;
}

void character::getDamaged (character*& atk, const DamageType& type) {
    int thenhp = currenthp;
    dmgcalc calc;
    int dmg = calc.damage(atk, *this, type);
    currenthp -= dmg;
    if (currenthp < 0)
        currenthp = 0;
    std::cout << name << " got damaged by " << atk->getName() << " for " << thenhp - currenthp << "HP." << std::endl;
}

void character::regen () {
    currenthp += (getLvl() * getLvl() / 2);
    if (currenthp > getMaxHP())
        currenthp = getMaxHP();
}

void character::potionregen () {
    currenthp += (getLvl() * getLvl() / 2);
    if (currenthp > getMaxHP())
        currenthp = getMaxHP();
}

void character::instaHP () {
    currenthp += (getMaxHP() / 4);
    if (currenthp > getMaxHP())
        currenthp = getMaxHP();
}

void character::manaregen () {
    currentmana += getLvl();
    if (currentmana > getMaxMana())
        currentmana = getMaxMana();
}

void character::potionmanaregen () {
    currentmana += getLvl() / 2;
    if (currentmana > getMaxMana())
        currentmana = getMaxMana();
}

float character::getResistance (const DamageType& type) const {
    auto it = resistance.find(type);
    return it != resistance.end()? it->second : 1.0f;
}

void character::setResist (const DamageType& type, float resist) {
    resistance[type] = resist;
}

void character::setGoldworth (int worth) {
    goldworth += worth;
}

void character::setExpworth (int worth) {
    expworth += worth;
}

int character::getGoldworth () const {
    return goldworth;
}

int character::getExpworth () const {
    return expworth;
}

void character::prologueSet (bool isPrologue) {
    prologue = isPrologue;
}

bool character::prologueState () const {
    return prologue;
}

void character::citySet (bool isCity) {
    firstcity = isCity;
}

bool character::cityState () const {
    return firstcity;
}

void character::blacksmithSet (bool isBlacksmith) {
    firstblacksmith = isBlacksmith;
}

bool character::blacksmithState () const {
    return firstblacksmith;
}

void character::churchSet (bool isChurch) {
    firstchurch = isChurch;
}

bool character::churchState () const {
    return firstchurch;
}

void character::tavernSet (bool isTavern) {
    firsttavern = isTavern;
}

bool character::tavernState () const {
    return firsttavern;
}

void character::mapSet (bool isMap) {
    firstmap = isMap;
}

bool character::mapState () const {
    return firstmap;
}

void character::setHPpot (int x) {
    healthpotion += x;
}

int character::getHPpot () const {
    return healthpotion;
}

void character::setManapot (int x) {
    manapotion += x;
}

int character::getManapot () const {
    return manapotion;
}

void character::setHPRegpot (int x) {
    regenpotion += x;
}

int character::getHPRegpot () const {
    return regenpotion;
}

void character::setManapotT (int x) {
    manapotionT += x;
}

int character::getManapotT () const {
    return manapotionT;
}

void character::setHPRegpotT (int x) {
    regenpotionT += x;
}

int character::getHPRegpotT () const {
    return regenpotionT;
}

void character::setActionpot (int x) {
    actionPot += x;
}

int character::getActionpot () const {
    return actionPot;
}

void character::setFastAction (bool isFastAction) {
    fastaction = isFastAction;
}

bool character::getFastAction () const {
    return fastaction;
}

void character::setPotionCD () {
    potionCD = 3;
}

int character::getPotionCD () const {
    return potionCD;
}

int character::getExtraSlot () const {
    return extraSlot;
}

void character::setExtraSlot (int extra) {
    extraSlot = extra;
}

void character::save_to_file (character*& hero) {
    std::string filename = hero->getSave();
    std::ofstream file(filename);
    int play = hero->getPlaytime().asSeconds();
    if (file.is_open()) {
        file << hero->getClass() << "\n" << hero->getName() << "\n" << play << "\n" << hero->getLvl() << "\n" << hero->
                getMaxHP() << "\n" << hero->getAd() << "\n" << hero->getDef() << "\n" << hero->getMaxMana() << "\n" <<
                hero->getSpeed() << "\n" << hero->getMaxHPinc() << "\n" << hero->getAdInc() << "\n" << hero->getDefInc()
                << "\n" << hero->getMaxManaInc() << "\n" << hero->getSpeedInc() << "\n" << hero->currentgold << "\n" <<
                hero->currenthp << "\n" << hero->currentmana << "\n" << hero->exp << "\n" << hero->prologueState() <<
                "\n" << hero->getHPpot() << "\n" << hero->getHPRegpot() << "\n" << hero->getManapot() << "\n" << hero->
                getActionpot() << "\n" << hero->getResistance(DamageType::MagicEnergy) << "\n" << hero->
                getResistance(DamageType::MagicFire) << "\n" << hero->getResistance(DamageType::MagicIce) << "\n" <<
                hero->getResistance(DamageType::MagicEarth) << "\n" << hero->getResistance(DamageType::MagicWater) <<
                "\n" << hero->getResistance(DamageType::MagicPoison) << "\n" << hero->
                getResistance(DamageType::MagicAir) << "\n" << hero->getResistance(DamageType::Physical) << "\n" << hero
                ->getResistance(DamageType::Enviroment) << "\n" << hero->getExtraSlot() << "\n";

        int invSize = hero->heroInv.getInvSize() - hero->heroInv.getAvaiableAmount();
        file << invSize << "\n";

        const auto& inv = hero->heroInv.inventory;

        for (size_t i = 0; i < inv.size(); ++i) {
            const Item& item = inv[i];
            if (item.getId() > 0) {
                file << i << "\n" << item.getId() << "\n" << item.stats.hp << "\n" << item.stats.ad << "\n" << item.
                        stats.def << "\n" << item.stats.mana << "\n" << item.stats.speed << "\n";
            }
        }

        if (helmetslot) {
            file << "x\n" << helmetslot->getId() << "\n" << helmetslot->stats.hp << "\n" << helmetslot->stats.ad << "\n"
                    << helmetslot->stats.def << "\n" << helmetslot->stats.mana << "\n" << helmetslot->stats.speed <<
                    "\n";
        }
        else
            file << "NOHELMET\n";

        if (necklaceslot) {
            file << "x\n" << necklaceslot->getId() << "\n" << necklaceslot->stats.hp << "\n" << necklaceslot->stats.ad
                    << "\n" << necklaceslot->stats.def << "\n" << necklaceslot->stats.mana << "\n" << necklaceslot->
                    stats.speed << "\n";
        }
        else
            file << "NONECKLACE\n";

        if (chestplateslot) {
            file << "x\n" << chestplateslot->getId() << "\n" << chestplateslot->stats.hp << "\n" << chestplateslot->
                    stats.ad << "\n" << chestplateslot->stats.def << "\n" << chestplateslot->stats.mana << "\n" <<
                    chestplateslot->stats.speed << "\n";
        }
        else
            file << "NOCHEST\n";

        if (glovesslot) {
            file << "x\n" << glovesslot->getId() << "\n" << glovesslot->stats.hp << "\n" << glovesslot->stats.ad << "\n"
                    << glovesslot->stats.def << "\n" << glovesslot->stats.mana << "\n" << glovesslot->stats.speed <<
                    "\n";
        }
        else
            file << "NOGLOVES\n";

        if (ringslot) {
            file << "x\n" << ringslot->getId() << "\n" << ringslot->stats.hp << "\n" << ringslot->stats.ad << "\n" <<
                    ringslot->stats.def << "\n" << ringslot->stats.mana << "\n" << ringslot->stats.speed << "\n";
        }
        else
            file << "NORING\n";

        if (leggingsslot) {
            file << "x\n" << leggingsslot->getId() << "\n" << leggingsslot->stats.hp << "\n" << leggingsslot->stats.ad
                    << "\n" << leggingsslot->stats.def << "\n" << leggingsslot->stats.mana << "\n" << leggingsslot->
                    stats.speed << "\n";
        }
        else
            file << "NOLEGS\n";

        if (bootsslot) {
            file << "x\n" << bootsslot->getId() << "\n" << bootsslot->stats.hp << "\n" << bootsslot->stats.ad << "\n" <<
                    bootsslot->stats.def << "\n" << bootsslot->stats.mana << "\n" << bootsslot->stats.speed << "\n";
        }
        else
            file << "NOBOOTS\n";

        if (weaponslot) {
            file << "x\n" << weaponslot->getId() << "\n" << weaponslot->stats.hp << "\n" << weaponslot->stats.ad << "\n"
                    << weaponslot->stats.def << "\n" << weaponslot->stats.mana << "\n" << weaponslot->stats.speed <<
                    "\n";
        }
        else
            file << "NOWEAPON\n";

        file.close();
    }
    else {
        std::cout << "Saving gamestate ERROR" << std::endl;
    }
}


bool character::load_from_file (const std::string filename, character*& hero) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string className;
        std::string name;
        stats charStats;
        statsincrese incStats;
        int playtime;

        file >> className >> name >> playtime >> charStats.lvl >> charStats.basehp >> charStats.ad >> charStats.def >>
                charStats.mana >> charStats.speed >> incStats.basehpinc >> incStats.adinc >> incStats.definc >> incStats
                .manainc >> incStats.speedinc;

        if (className == "Warrior") {
            hero = new Warrior(name, charStats);
        }
        else if (className == "Mage") {
            hero = new Mage(name, charStats);
        }
        else if (className == "Archer") {
            hero = new Archer(name, charStats);
        }
        else {
            std::cerr << "Error: Unknown class name '" << className << "'!" << std::endl;
            return false;
        }
        bool isPrologue;
        int x, y, z, a;
        file >> hero->currentgold >> hero->currenthp >> hero->currentmana >> hero->exp >> isPrologue >> x >> y >> z >>
                a;
        hero->setHPpot(x);
        hero->setHPRegpot(y);
        hero->setManapot(z);
        hero->setActionpot(a);
        hero->prologueSet(isPrologue);
        hero->setPlaytime(sf::seconds(playtime));
        float energy, fire, ice, earth, water, poison, air, phys, env;
        file >> energy >> fire >> ice >> earth >> water >> poison >> air >> phys >> env;
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
        int extra;
        file >> extra;
        hero->setExtraSlot(extra);
        file >> invSize;
        for (int i = 0; i < invSize; i++) {
            int slot;
            file >> slot;
            int id;
            file >> id;
            Item item(id);
            file >> item.stats.hp;
            file >> item.stats.ad;
            file >> item.stats.def;
            file >> item.stats.mana;
            file >> item.stats.speed;
            hero->heroInv.addItem(item, slot);
        }
        std::string isSlot;
        file >> isSlot;
        if (isSlot == "NOHELMET");
        else {
            int id;
            file >> id;
            Item helmet(id);
            file >> helmet.stats.hp >> helmet.stats.ad >> helmet.stats.def >> helmet.stats.mana >> helmet.stats.speed;
            hero->helmetslot = std::make_optional<Item>(helmet);
        }
        file >> isSlot;
        if (isSlot == "NONECKLACE");
        else {
            int id;
            file >> id;
            Item necklace(id);
            file >> necklace.stats.hp >> necklace.stats.ad >> necklace.stats.def >> necklace.stats.mana >> necklace.
                    stats.speed;
            hero->necklaceslot = std::make_optional<Item>(necklace);
        }
        file >> isSlot;
        if (isSlot == "NOCHEST");
        else {
            int id;
            file >> id;
            Item chest(id);
            file >> chest.stats.hp >> chest.stats.ad >> chest.stats.def >> chest.stats.mana >> chest.stats.speed;
            hero->chestplateslot = std::make_optional<Item>(chest);
        }
        file >> isSlot;
        if (isSlot == "NOGLOVES");
        else {
            int id;
            file >> id;
            Item gloves(id);
            file >> gloves.stats.hp >> gloves.stats.ad >> gloves.stats.def >> gloves.stats.mana >> gloves.stats.speed;
            hero->glovesslot = std::make_optional<Item>(gloves);
        }
        file >> isSlot;
        if (isSlot == "NORING");
        else {
            int id;
            file >> id;
            Item ring(id);
            file >> ring.stats.hp >> ring.stats.ad >> ring.stats.def >> ring.stats.mana >> ring.stats.speed;
            hero->ringslot = std::make_optional<Item>(ring);
        }
        file >> isSlot;
        if (isSlot == "NOLEGS");
        else {
            int id;
            file >> id;
            Item leg(id);
            file >> leg.stats.hp >> leg.stats.ad >> leg.stats.def >> leg.stats.mana >> leg.stats.speed;
            hero->leggingsslot = std::make_optional<Item>(leg);
        }
        file >> isSlot;
        if (isSlot == "NOBOOTS");
        else {
            int id;
            file >> id;
            Item boots(id);
            file >> boots.stats.hp >> boots.stats.ad >> boots.stats.def >> boots.stats.mana >> boots.stats.speed;
            hero->bootsslot = std::make_optional<Item>(boots);
        }
        file >> isSlot;
        if (isSlot == "NOWEAPON");
        else {
            int id;
            file >> id;
            Item weapon(id);
            file >> weapon.stats.hp >> weapon.stats.ad >> weapon.stats.def >> weapon.stats.mana >> weapon.stats.speed;
            hero->weaponslot = std::make_optional<Item>(weapon);
        }
        hero->setSave(filename);
        hero->startClock();
        file.close();
        return true;
    }
    else {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return false;
    }
}
