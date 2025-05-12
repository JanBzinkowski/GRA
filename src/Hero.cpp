#include "Hero.h"
#include "Warrior.h"
#include "Archer.h"
#include "Mage.h"
#include "damage.h"
#include <fstream>

std::string Hero::getClass () const {
    return "Hero";
}

void Hero::setCurrentMana (int mana) {
    currentmana = mana;
}

void Hero::incCurrentMana (int inc) {
    currentmana += inc;
}

int Hero::getCurrentMana () const {
    return currentmana;
}

void Hero::startClock () {
    gameplay_time.start();
}

void Hero::restartClock () {
    gameplay_time.reset();
}

sf::Time Hero::getPlaytime () {
    playtime += gameplay_time.getElapsedTime();
    restartClock();
    return playtime;
}

void Hero::setPlaytime (sf::Time time) {
    playtime = time;
}

void Hero::setSave (const std::string fileName) {
    save = fileName;
}

const std::string Hero::getSave () {
    return save;
}

int Hero::get1stAvaiableIndex () const {
    return heroInv.get1stAvailableSlot();
}

int Hero::getAvaiableAmount () const {
    return heroInv.getAvaiableAmount();
}

bool Hero::isAvailable (const int slot) const {
    return heroInv.isAvaiable(slot);
}

void Hero::swapItems (size_t i, size_t x) {
    heroInv.swapItems(i, x);
}

int Hero::getInvSize () const {
    return heroInv.getInvSize();
}

Item Hero::getItemFromEqp (itemType type) const {
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

Item Hero::getItemFromInventory (int slot) const {
    return heroInv.m_inventory[slot];
}

void Hero::removeFromEqp (const itemType type) {
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

void Hero::addToInv (const Item& item, const int slot) {
    heroInv.addItem(item, slot);
}

void Hero::removeFromInv (const int slot) {
    heroInv.removeItem(slot);
}

void Hero::equipItem (const Item& item) {
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

void Hero::equipFromInv (const int& slot) {
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

bool Hero::checkIfEqp (itemType type) const {
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

void Hero::unequip (const itemType type, int slot) {
    if (slot < 0)
        slot = heroInv.get1stAvailableSlot();
    itemStats stats = Item(0).getStats();
    switch (type) {
        case itemType::Helmet: {
            if (helmetslot) {
                stats = helmetslot->getStats();
                heroInv.m_inventory[slot] = *helmetslot;
                helmetslot.reset();
                heroInv.removeAvaiableSlot(slot);
            }
            break;
        }
        case itemType::Chestplate: {
            if (chestplateslot) {
                stats = chestplateslot->getStats();
                heroInv.m_inventory[slot] = *chestplateslot;
                chestplateslot.reset();
                heroInv.removeAvaiableSlot(slot);
            }
            break;
        }
        case itemType::Necklace: {
            if (necklaceslot) {
                stats = necklaceslot->getStats();
                heroInv.m_inventory[slot] = *necklaceslot;
                necklaceslot.reset();
                heroInv.removeAvaiableSlot(slot);
            }
            break;
        }
        case itemType::Gloves: {
            if (glovesslot) {
                stats = glovesslot->getStats();
                heroInv.m_inventory[slot] = *glovesslot;
                glovesslot.reset();
                heroInv.removeAvaiableSlot(slot);
            }
            break;
        }
        case itemType::Ring: {
            if (ringslot) {
                stats = ringslot->getStats();
                heroInv.m_inventory[slot] = *ringslot;
                ringslot.reset();
                heroInv.removeAvaiableSlot(slot);
            }
            break;
        }
        case itemType::Leggings: {
            if (leggingsslot) {
                stats = leggingsslot->getStats();
                heroInv.m_inventory[slot] = *leggingsslot;
                leggingsslot.reset();
                heroInv.removeAvaiableSlot(slot);
            }
            break;
        }
        case itemType::Boots: {
            if (bootsslot) {
                stats = bootsslot->getStats();
                heroInv.m_inventory[slot] = *bootsslot;
                bootsslot.reset();
                heroInv.removeAvaiableSlot(slot);
            }
            break;
        }
        case itemType::Weapon: {
            if (weaponslot) {
                stats = weaponslot->getStats();
                heroInv.m_inventory[slot] = *weaponslot;
                weaponslot.reset();
                heroInv.removeAvaiableSlot(slot);
            }
            break;
        }
        default: {
            return;
        }
    }
    updateStats(stats, false);
}

void Hero::updateStats (itemStats stats, bool equip) {
    int mod = equip? 1 : -1;
    Stats hero_stats = getStats();
    hero_stats.ad += stats.ad * mod;
    hero_stats.base_hp += stats.hp * mod;
    hero_stats.mana += stats.mana * mod;
    hero_stats.def += stats.def * mod;
    hero_stats.speed += stats.speed * mod;
}

void Hero::lvlup () {
    Stats stat = getStats();
    StatsIncrese incstats = getStatsInc();
    int exp_treshold = 5 * pow(stat.lvl, 2.2) + 25;
    if (exp >= exp_treshold) {
        exp -= exp_treshold;
        stat.lvl++;
        std::cout << "\nCongratulations! You have leveled up to level " << stat.lvl << "!\n" << std::endl;
        std::cout << "Atk: " << stat.ad << " + " << incstats.ad_inc << std::endl;
        std::cout << "Def: " << stat.def << " + " << incstats.def_inc << std::endl;
        std::cout << "HP: " << stat.base_hp << " + " << incstats.base_HP_inc * stat.lvl << std::endl;
        std::cout << "Mana: " << stat.mana << " + " << incstats.mana_inc << std::endl;
        std::cout << "Gold Coins: " << current_gold << " + " << 5 * stat.lvl << std::endl;
        std::cout << "\nHP and mana restored." << std::endl;

        stat.ad += incstats.ad_inc;
        stat.base_hp += incstats.base_HP_inc * stat.lvl;
        stat.def += incstats.def_inc;
        stat.mana += incstats.mana_inc;
        current_gold += 5 * stat.lvl;
        setCurrentHP(stat.base_hp);
        currentmana = stat.mana;
        if (stat.lvl == 2) {
            std::cout << "\n-------------------------------------------------------------------------------------------------------------------------------" << std::endl;
            std::cout << "\n\nYou have unlocked:\n  - Potions\n  - Items" << std::endl;
        }
        if (stat.lvl == 5) {
            std::cout << "\n-------------------------------------------------------------------------------------------------------------------------------" << std::endl;
            std::cout << "\n\nYou have unlocked:\n  - Potion of Mana Regeneration" << std::endl;
        }
        if (stat.lvl == 8) {
            std::cout << "\n-------------------------------------------------------------------------------------------------------------------------------" << std::endl;
            std::cout << "\n\nYou have unlocked:\n  - Potion of Fast Action\n  - Uncommon Items" << std::endl;
        }
    }
}

int Hero::getDamaged (Enemy*& enemy, const DamageType& type) {
    int before_HP = this->getCurrentHP();
    int dmg;
    float randChance = rand()/RAND_MAX;
    if (randChance < this->getAtkChance(enemy)) {
        int lvl_diff = (this->getLvl()) - (enemy->getLvl());
        if (lvl_diff >= 10)
            lvl_diff = 9;
        float reduction = reduct(enemy);
        float resistancemult = enemy->getResistance(type);
        dmg = dmgcalc::damageCalculator(this->getAd(), this->getLvl(), this->getMultDmg(), reduction, resistancemult, lvl_diff);
    }
    this->incCurrentHP(-dmg);
    if (this->getCurrentHP() < 0)
        this->setCurrentHP(0);
    return before_HP - this->getCurrentHP();
}

float Hero::getAtkChance (Enemy*& enemy) const {
    int lvldif = (this->getLvl()) - (enemy->getLvl());
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

float Hero::reduct (Enemy*& enemy) const {
    int lvlDiff = (this->getLvl()) - (enemy->getLvl());
    if (lvlDiff >= 10)
        lvlDiff = 9;
    float reduction = atan(this->getDef()) / this->getLvl() * (1 + 0.1 * lvlDiff);
    std::string classhero = enemy->getClass();
    if (((classhero == "Warrior")) && reduction > 0.75f)
        reduction = 0.75f;
    else if (((classhero == "Archer")) && reduction > 0.55f)
        reduction = 0.55f;
    else if (((classhero == "Mage")) && reduction > 0.40f)
        reduction = 0.40f;
    return reduction;
}

void Hero::pray () {
    setCurrentHP(getStats().base_hp);
}

void Hero::goldInc (int gold) {
    current_gold += gold;
}

void Hero::setCurrentGold (int gold) {
    current_gold = gold;
}

int Hero::getCurrentGold () const {
    return current_gold;
}

void Hero::expInc (int experience) {
    exp += experience;
}

void Hero::setExp (int experience) {
    exp = experience;
}

int Hero::getCurrentExp () const {
    return exp;
}

void Hero::prologueSet (bool isPrologue) {
    prologue = isPrologue;
}

bool Hero::prologueState () const {
    return prologue;
}

void Hero::citySet (bool isCity) {
    firstcity = isCity;
}

bool Hero::cityState () const {
    return firstcity;
}

void Hero::blacksmithSet (bool isBlacksmith) {
    firstblacksmith = isBlacksmith;
}

bool Hero::blacksmithState () const {
    return firstblacksmith;
}

void Hero::churchSet (bool isChurch) {
    firstchurch = isChurch;
}

bool Hero::churchState () const {
    return firstchurch;
}

void Hero::tavernSet (bool isTavern) {
    firsttavern = isTavern;
}

bool Hero::tavernState () const {
    return firsttavern;
}

void Hero::mapSet (bool isMap) {
    firstmap = isMap;
}

bool Hero::mapState () const {
    return firstmap;
}

void Hero::regen () {
    setCurrentHP(getLvl() * getLvl() / 2);
    if (getCurrentHP() > getMaxHP())
        setCurrentHP(getMaxHP());
}

void Hero::instaHP () {
    setCurrentHP(getMaxHP() / 4);
    if (getCurrentHP() > getMaxHP())
        setCurrentHP(getMaxHP());
}

void Hero::manaregen () {
    currentmana += getLvl();
    if (currentmana > getMaxMana())
        currentmana = getMaxMana();
}

void Hero::potionmanaregen () {
    currentmana += getLvl() / 2;
    if (currentmana > getMaxMana())
        currentmana = getMaxMana();
}

void Hero::setHPpot (int x) {
    healthpotion += x;
}

int Hero::getHPpot () const {
    return healthpotion;
}

void Hero::setManapot (int x) {
    manapotion += x;
}

int Hero::getManapot () const {
    return manapotion;
}

void Hero::setHPRegpot (int x) {
    regenpotion += x;
}

int Hero::getHPRegpot () const {
    return regenpotion;
}

void Hero::setManapotT (int x) {
    manapotionT += x;
}

int Hero::getManapotT () const {
    return manapotionT;
}

void Hero::setHPRegpotT (int x) {
    regenpotionT += x;
}

int Hero::getHPRegpotT () const {
    return regenpotionT;
}

void Hero::setActionpot (int x) {
    actionPot += x;
}

int Hero::getActionpot () const {
    return actionPot;
}

void Hero::setFastAction (bool isFastAction) {
    fastaction = isFastAction;
}

bool Hero::getFastAction () const {
    return fastaction;
}

void Hero::setPotionCD () {
    potionCD = 3;
}

int Hero::getPotionCD () const {
    return potionCD;
}

int Hero::getExtraSlot () const {
    return extraSlot;
}

void Hero::setExtraSlot (int extra) {
    extraSlot = extra;
}

void Hero::save_to_file () {
    std::string filename = this->getSave();
    std::ofstream file(filename);
    int play = this->getPlaytime().asSeconds();
    if (file.is_open()) {
        file << this->getClass() << "\n" << this->getName() << "\n" << play << "\n" << this->getLvl() << "\n" << this->getMaxHP() << "\n" << this->getAd() << "\n" << this->getDef() << "\n" << this->getMaxMana() << "\n" << this->getSpeed() << "\n" << this->getMaxHPInc() << "\n" << this->getAdInc() << "\n" << this->getDefInc() << "\n" << this->getMaxManaInc() << "\n" << this->getSpeedInc() << "\n" << this->current_gold << "\n" << this->getCurrentHP() << "\n" << this->currentmana << "\n" << this->
                exp << "\n" << this->prologueState() << "\n" << this->getHPpot() << "\n" << this->getHPRegpot() << "\n" << this->getManapot() << "\n" << this->getActionpot() << "\n" << this->getResistance(DamageType::MagicEnergy) << "\n" << this->getResistance(DamageType::MagicFire) << "\n" << this->getResistance(DamageType::MagicIce) << "\n" << this->getResistance(DamageType::MagicEarth) << "\n" << this->getResistance(DamageType::MagicWater) << "\n" << this->
                getResistance(DamageType::MagicPoison) << "\n" << this->getResistance(DamageType::MagicAir) << "\n" << this->getResistance(DamageType::Physical) << "\n" << this->getResistance(DamageType::Enviroment) << "\n" << this->getExtraSlot() << "\n";

        int invSize = this->heroInv.getInvSize() - this->heroInv.getAvaiableAmount();
        file << invSize << "\n";

        const auto& inv = this->heroInv.m_inventory;

        for (size_t i = 0; i < inv.size(); ++i) {
            const Item& item = inv[i];
            itemStats item_stats = item.getStats();
            if (item.getId() > 0) {
                file << i << "\n" << item.getId() << "\n" << item_stats.hp << "\n" << item_stats.ad << "\n" << item_stats.def << "\n" << item_stats.mana << "\n" << item_stats.speed << "\n";
            }
        }

        if (helmetslot) {
            itemStats item_stats = helmetslot->getStats();
            file << "x\n" << helmetslot->getId() << "\n" << item_stats.hp << "\n" << item_stats.ad << "\n" << item_stats.def << "\n" << item_stats.mana << "\n" << item_stats.speed << "\n";
        }
        else
            file << "NOHELMET\n";

        if (necklaceslot) {
            itemStats item_stats = necklaceslot->getStats();
            file << "x\n" << necklaceslot->getId() << "\n" << item_stats.hp << "\n" << item_stats.ad << "\n" << item_stats.def << "\n" << item_stats.mana << "\n" << item_stats.speed << "\n";
        }
        else
            file << "NONECKLACE\n";

        if (chestplateslot) {
            itemStats item_stats = chestplateslot->getStats();
            file << "x\n" << chestplateslot->getId() << "\n" << item_stats.hp << "\n" << item_stats.ad << "\n" << item_stats.def << "\n" << item_stats.mana << "\n" << item_stats.speed << "\n";
        }
        else
            file << "NOCHEST\n";

        if (glovesslot) {
            itemStats item_stats = glovesslot->getStats();
            file << "x\n" << glovesslot->getId() << "\n" << item_stats.hp << "\n" << item_stats.ad << "\n" << item_stats.def << "\n" << item_stats.mana << "\n" << item_stats.speed << "\n";
        }
        else
            file << "NOGLOVES\n";

        if (ringslot) {
            itemStats item_stats = ringslot->getStats();
            file << "x\n" << ringslot->getId() << "\n" << item_stats.hp << "\n" << item_stats.ad << "\n" << item_stats.def << "\n" << item_stats.mana << "\n" << item_stats.speed << "\n";
        }
        else
            file << "NORING\n";

        if (leggingsslot) {
            itemStats item_stats = leggingsslot->getStats();
            file << "x\n" << leggingsslot->getId() << "\n" << item_stats.hp << "\n" << item_stats.ad << "\n" << item_stats.def << "\n" << item_stats.mana << "\n" << item_stats.speed << "\n";
        }
        else
            file << "NOLEGS\n";

        if (bootsslot) {
            itemStats item_stats = bootsslot->getStats();
            file << "x\n" << bootsslot->getId() << "\n" << item_stats.hp << "\n" << item_stats.ad << "\n" << item_stats.def << "\n" << item_stats.mana << "\n" << item_stats.speed << "\n";
        }
        else
            file << "NOBOOTS\n";

        if (weaponslot) {
            itemStats item_stats = weaponslot->getStats();
            file << "x\n" << weaponslot->getId() << "\n" << item_stats.hp << "\n" << item_stats.ad << "\n" << item_stats.def << "\n" << item_stats.mana << "\n" << item_stats.speed << "\n";
        }
        else
            file << "NOWEAPON\n";

        file.close();
    }
    else {
        std::cout << "Saving gamestate ERROR" << std::endl;
    }
}

bool Hero::load_from_file (const std::string filename, Hero*& hero) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string className;
        std::string name;
        Stats charStats;
        StatsIncrese incStats;
        int playtime;

        file >> className >> name >> playtime >> charStats.lvl >> charStats.base_hp >> charStats.ad >> charStats.def >> charStats.mana >> charStats.speed >> incStats.base_HP_inc >> incStats.ad_inc >> incStats.def_inc >> incStats.mana_inc >> incStats.speed_inc;

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
        int x, y, z, a, gold, hp, mana, experience;
        file >> gold >> hp >> mana >> experience >> isPrologue >> x >> y >> z >> a;
        hero->setCurrentGold(gold);
        hero->setCurrentHP(hp);
        hero->setCurrentMana(mana);
        hero->setExp(experience);
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
            itemStats stats = itemData.at(id);
            file >> stats.hp;
            file >> stats.ad;
            file >> stats.def;
            file >> stats.mana;
            file >> stats.speed;
            item.setStats(stats);
            hero->heroInv.addItem(item, slot);
        }
        std::string isSlot;
        file >> isSlot;
        if (isSlot == "NOHELMET");
        else {
            int id;
            file >> id;
            itemStats stats = itemData.at(id);
            Item helmet(id);
            file >> stats.hp >> stats.ad >> stats.def >> stats.mana >> stats.speed;
            helmet.setStats(stats);
            hero->helmetslot = std::make_optional<Item>(helmet);
        }
        file >> isSlot;
        if (isSlot == "NONECKLACE");
        else {
            int id;
            file >> id;
            itemStats stats = itemData.at(id);
            Item necklace(id);
            file >> stats.hp >> stats.ad >> stats.def >> stats.mana >> stats.speed;
            necklace.setStats(stats);
            hero->necklaceslot = std::make_optional<Item>(necklace);
        }
        file >> isSlot;
        if (isSlot == "NOCHEST");
        else {
            int id;
            file >> id;
            itemStats stats = itemData.at(id);
            Item chest(id);
            file >> stats.hp >> stats.ad >> stats.def >> stats.mana >> stats.speed;
            chest.setStats(stats);
            hero->chestplateslot = std::make_optional<Item>(chest);
        }
        file >> isSlot;
        if (isSlot == "NOGLOVES");
        else {
            int id;
            file >> id;
            itemStats stats = itemData.at(id);
            Item gloves(id);
            file >> stats.hp >> stats.ad >> stats.def >> stats.mana >> stats.speed;
            gloves.setStats(stats);
            hero->glovesslot = std::make_optional<Item>(gloves);
        }
        file >> isSlot;
        if (isSlot == "NORING");
        else {
            int id;
            file >> id;
            itemStats stats = itemData.at(id);
            Item ring(id);
            file >> stats.hp >> stats.ad >> stats.def >> stats.mana >> stats.speed;
            ring.setStats(stats);
            hero->ringslot = std::make_optional<Item>(ring);
        }
        file >> isSlot;
        if (isSlot == "NOLEGS");
        else {
            int id;
            file >> id;
            itemStats stats = itemData.at(id);
            Item leg(id);
            file >> stats.hp >> stats.ad >> stats.def >> stats.mana >> stats.speed;
            leg.setStats(stats);
            hero->leggingsslot = std::make_optional<Item>(leg);
        }
        file >> isSlot;
        if (isSlot == "NOBOOTS");
        else {
            int id;
            file >> id;
            itemStats stats = itemData.at(id);
            Item boots(id);
            file >> stats.hp >> stats.ad >> stats.def >> stats.mana >> stats.speed;
            boots.setStats(stats);
            hero->bootsslot = std::make_optional<Item>(boots);
        }
        file >> isSlot;
        if (isSlot == "NOWEAPON");
        else {
            int id;
            file >> id;
            itemStats stats = itemData.at(id);
            Item weapon(id);
            file >> stats.hp >> stats.ad >> stats.def >> stats.mana >> stats.speed;
            weapon.setStats(stats);
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
