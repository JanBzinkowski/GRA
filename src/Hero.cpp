#include "Hero.h"
#include "Warrior.h"
#include "Archer.h"
#include "Mage.h"
#include "DamageCalculation.h"
#include <fstream>
#include <math.h>

std::string Hero::getClass () const {
    return "Hero";
}

void Hero::setCurrentMana (int mana) {
    m_current_mana = mana;
}

void Hero::incCurrentMana (int inc) {
    m_current_mana += inc;
}

int Hero::getCurrentMana () const {
    return m_current_mana;
}

void Hero::startClock () {
    m_gameplay_time.start();
}

void Hero::restartClock () {
    m_gameplay_time.reset();
}

sf::Time Hero::getPlaytime () {
    m_playtime += m_gameplay_time.getElapsedTime();
    restartClock();
    return m_playtime;
}

void Hero::setPlaytime (sf::Time time) {
    m_playtime = time;
}

void Hero::setSave (const std::string fileName) {
    m_save_path = fileName;
}

const std::string Hero::getSave () {
    return m_save_path;
}

int Hero::get1stAvaiableIndex () const {
    return m_inventory.get1stAvailableSlot();
}

int Hero::getAvaiableAmount () const {
    return m_inventory.getAvaiableAmount();
}

bool Hero::isAvailable (const int slot) const {
    return m_inventory.isAvaiable(slot);
}

void Hero::swapItems (size_t i, size_t x) {
    m_inventory.swapItems(i, x);
}

int Hero::getInvSize () const {
    return m_inventory.getInvSize();
}

Item Hero::getItemFromEqp (itemType type) const {
    switch (type) {
        case itemType::Helmet: {
            if (m_helmet_slot)
                return *m_helmet_slot;
            break;
        }
        case itemType::Chestplate: {
            if (m_chestplate_slot)
                return *m_chestplate_slot;
            break;
        }
        case itemType::Necklace: {
            if (m_necklace_slot)
                return *m_necklace_slot;
            break;
        }
        case itemType::Gloves: {
            if (m_gloves_slot)
                return *m_gloves_slot;
            break;
        }
        case itemType::Ring: {
            if (m_ring_slot)
                return *m_ring_slot;
            break;
        }
        case itemType::Leggings: {
            if (m_leggings_slot)
                return *m_leggings_slot;
            break;
        }
        case itemType::Boots: {
            if (m_boots_slot)
                return *m_boots_slot;
            break;
        }
        case itemType::Weapon: {
            if (m_weapon_slot)
                return *m_weapon_slot;
            break;
        }
        default:
            return Item(0);
    }
    return Item(0);
}

Item Hero::getItemFromInventory (int slot) const {
    return m_inventory.m_inventory[slot];
}

void Hero::removeFromEqp (const itemType type) {
    Item item(0);
    switch (type) {
        case itemType::Helmet: {
            item = *m_helmet_slot;
            m_helmet_slot = std::nullopt;
            break;
        }
        case itemType::Chestplate: {
            item = *m_chestplate_slot;
            m_chestplate_slot = std::nullopt;
            break;
        }
        case itemType::Necklace: {
            item = *m_necklace_slot;
            m_necklace_slot = std::nullopt;
            break;
        }
        case itemType::Gloves: {
            item = *m_gloves_slot;
            m_gloves_slot = std::nullopt;
            break;
        }
        case itemType::Ring: {
            item = *m_ring_slot;
            m_ring_slot = std::nullopt;
            break;
        }
        case itemType::Leggings: {
            item = *m_leggings_slot;
            m_leggings_slot = std::nullopt;
            break;
        }
        case itemType::Boots: {
            item = *m_boots_slot;
            m_boots_slot = std::nullopt;
            break;
        }
        case itemType::Weapon: {
            item = *m_weapon_slot;
            m_weapon_slot = std::nullopt;
            break;
        }
    }
    updateStats(item.getStats(), false);
}

void Hero::addToInv (const Item& item, const int slot) {
    m_inventory.addItem(item, slot);
}

void Hero::removeFromInv (const int slot) {
    m_inventory.removeItem(slot);
}

void Hero::equipItem (const Item& item) {
    itemType type = item.getType();
    unequip(type);
    switch (type) {
        case itemType::Helmet: {
            m_helmet_slot = item;
            break;
        }
        case itemType::Chestplate: {
            m_chestplate_slot = item;
            break;
        }
        case itemType::Necklace: {
            m_necklace_slot = item;
            break;
        }
        case itemType::Gloves: {
            m_gloves_slot = item;
            break;
        }
        case itemType::Ring: {
            m_ring_slot = item;
            break;
        }
        case itemType::Leggings: {
            m_leggings_slot = item;
            break;
        }
        case itemType::Boots: {
            m_boots_slot = item;
            break;
        }
        case itemType::Weapon: {
            m_weapon_slot = item;
            break;
        }
    }
    itemStats stats = item.getStats();
    updateStats(stats, true);
}

void Hero::equipFromInv (const int& slot) {
    bool remove = false;
    Item item = m_inventory.getItemByIndex(slot);
    itemType type = item.getType();
    if (checkIfEqp(type))
        unequip(type, slot);
    else
        remove = true;
    switch (type) {
        case itemType::Helmet: {
            m_helmet_slot = item;
            break;
        }
        case itemType::Chestplate: {
            m_chestplate_slot = item;
            break;
        }
        case itemType::Necklace: {
            m_necklace_slot = item;
            break;
        }
        case itemType::Gloves: {
            m_gloves_slot = item;
            break;
        }
        case itemType::Ring: {
            m_ring_slot = item;
            break;
        }
        case itemType::Leggings: {
            m_leggings_slot = item;
            break;
        }
        case itemType::Boots: {
            m_boots_slot = item;
            break;
        }
        case itemType::Weapon: {
            m_weapon_slot = item;
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
            if (m_helmet_slot)
                return true;
            break;
        }
        case itemType::Chestplate: {
            if (m_chestplate_slot)
                return true;
            break;
        }
        case itemType::Necklace: {
            if (m_necklace_slot)
                return true;
            break;
        }
        case itemType::Gloves: {
            if (m_gloves_slot)
                return true;
            break;
        }
        case itemType::Ring: {
            if (m_ring_slot)
                return true;
            break;
        }
        case itemType::Leggings: {
            if (m_leggings_slot)
                return true;
            break;
        }
        case itemType::Boots: {
            if (m_boots_slot)
                return true;
            break;
        }
        case itemType::Weapon: {
            if (m_weapon_slot)
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
        slot = m_inventory.get1stAvailableSlot();
    itemStats stats = Item(0).getStats();
    switch (type) {
        case itemType::Helmet: {
            if (m_helmet_slot) {
                stats = m_helmet_slot->getStats();
                m_inventory.m_inventory[slot] = *m_helmet_slot;
                m_helmet_slot.reset();
                m_inventory.removeAvaiableSlot(slot);
            }
            break;
        }
        case itemType::Chestplate: {
            if (m_chestplate_slot) {
                stats = m_chestplate_slot->getStats();
                m_inventory.m_inventory[slot] = *m_chestplate_slot;
                m_chestplate_slot.reset();
                m_inventory.removeAvaiableSlot(slot);
            }
            break;
        }
        case itemType::Necklace: {
            if (m_necklace_slot) {
                stats = m_necklace_slot->getStats();
                m_inventory.m_inventory[slot] = *m_necklace_slot;
                m_necklace_slot.reset();
                m_inventory.removeAvaiableSlot(slot);
            }
            break;
        }
        case itemType::Gloves: {
            if (m_gloves_slot) {
                stats = m_gloves_slot->getStats();
                m_inventory.m_inventory[slot] = *m_gloves_slot;
                m_gloves_slot.reset();
                m_inventory.removeAvaiableSlot(slot);
            }
            break;
        }
        case itemType::Ring: {
            if (m_ring_slot) {
                stats = m_ring_slot->getStats();
                m_inventory.m_inventory[slot] = *m_ring_slot;
                m_ring_slot.reset();
                m_inventory.removeAvaiableSlot(slot);
            }
            break;
        }
        case itemType::Leggings: {
            if (m_leggings_slot) {
                stats = m_leggings_slot->getStats();
                m_inventory.m_inventory[slot] = *m_leggings_slot;
                m_leggings_slot.reset();
                m_inventory.removeAvaiableSlot(slot);
            }
            break;
        }
        case itemType::Boots: {
            if (m_boots_slot) {
                stats = m_boots_slot->getStats();
                m_inventory.m_inventory[slot] = *m_boots_slot;
                m_boots_slot.reset();
                m_inventory.removeAvaiableSlot(slot);
            }
            break;
        }
        case itemType::Weapon: {
            if (m_weapon_slot) {
                stats = m_weapon_slot->getStats();
                m_inventory.m_inventory[slot] = *m_weapon_slot;
                m_weapon_slot.reset();
                m_inventory.removeAvaiableSlot(slot);
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

bool Hero::lvlup () {
    Stats stat = getStats();
    StatsIncrese incstats = getStatsInc();
    int exp_treshold = 5 * pow(stat.lvl, 2.2) + 25;
    if (exp >= exp_treshold) {
        exp -= exp_treshold;
        stat.lvl++;

        stat.ad += incstats.ad_inc;
        stat.base_hp += incstats.base_HP_inc * stat.lvl;
        stat.def += incstats.def_inc;
        stat.mana += incstats.mana_inc;

        m_current_gold += 5 * stat.lvl;

        setCurrentHP(stat.base_hp);
        m_current_mana = stat.mana;

        setStats(stat);
        return true;
    }
    return false;
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
        float resistancemult = enemy->getWeaknessMult(type);
        dmg = DMGCalculation::damageCalculator(this->getAd(), this->getLvl(), this->getMultDmg(), reduction, resistancemult, lvl_diff);
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
    m_current_gold += gold;
}

void Hero::setCurrentGold (int gold) {
    m_current_gold = gold;
}

int Hero::getCurrentGold () const {
    return m_current_gold;
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
    m_prologue_state = isPrologue;
}

bool Hero::prologueState () const {
    return m_prologue_state;
}

void Hero::citySet (bool isCity) {
    m_first_time_city = isCity;
}

bool Hero::cityState () const {
    return m_first_time_city;
}

void Hero::blacksmithSet (bool isBlacksmith) {
    m_first_time_blacksmith = isBlacksmith;
}

bool Hero::blacksmithState () const {
    return m_first_time_blacksmith;
}

void Hero::churchSet (bool isChurch) {
    m_first_time_church = isChurch;
}

bool Hero::churchState () const {
    return m_first_time_church;
}

void Hero::tavernSet (bool isTavern) {
    m_first_time_tavern = isTavern;
}

bool Hero::tavernState () const {
    return m_first_time_tavern;
}

void Hero::mapSet (bool isMap) {
    m_first_time_map = isMap;
}

bool Hero::mapState () const {
    return m_first_time_map;
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

void Hero::manaRegen () {
    m_current_mana += getLvl();
    if (m_current_mana > getMaxMana())
        m_current_mana = getMaxMana();
}

void Hero::manaRegenPotion () {
    m_current_mana += getLvl() / 2;
    if (m_current_mana > getMaxMana())
        m_current_mana = getMaxMana();
}

void Hero::setHPpot (int x) {
    m_health_potion_amount += x;
}

int Hero::getHPpot () const {
    return m_health_potion_amount;
}

void Hero::setManapot (int x) {
    m_mana_potion_amount += x;
}

int Hero::getManapot () const {
    return m_mana_potion_amount;
}

void Hero::setHPRegpot (int x) {
    m_regen_potion_amount += x;
}

int Hero::getHPRegpot () const {
    return m_regen_potion_amount;
}

void Hero::setManapotT (int x) {
    m_mana_potion_time += x;
}

int Hero::getManapotT () const {
    return m_mana_potion_time;
}

void Hero::setHPRegpotT (int x) {
    m_regen_potion_time += x;
}

int Hero::getHPRegpotT () const {
    return m_regen_potion_time;
}

void Hero::setActionpot (int x) {
    m_action_potion_amount += x;
}

int Hero::getActionpot () const {
    return m_action_potion_amount;
}

void Hero::setFastAction (bool isFastAction) {
    m_fast_action = isFastAction;
}

bool Hero::getFastAction () const {
    return m_fast_action;
}

void Hero::setPotionCD () {
    m_potion_cooldown = 3;
}

int Hero::getPotionCD () const {
    return m_potion_cooldown;
}

int Hero::getExtraSlot () const {
    return m_extraSlot;
}

void Hero::setExtraSlot (int extra) {
    m_extraSlot = extra;
}

void Hero::save_to_file () {
    std::string filename = this->getSave();
    std::ofstream file(filename);
    int play = this->getPlaytime().asSeconds();
    if (file.is_open()) {
        file << this->getClass() << "\n" << this->getName() << "\n" << play << "\n" << this->getLvl() << "\n" << this->getMaxHP() << "\n" << this->getAd() << "\n" << this->getDef() << "\n" << this->getMaxMana() << "\n" << this->getSpeed() << "\n" << this->getMaxHPInc() << "\n" << this->getAdInc() << "\n" << this->getDefInc() << "\n" << this->getMaxManaInc() << "\n" << this->getSpeedInc() << "\n" << this->m_current_gold << "\n" << this->getCurrentHP() << "\n" << this->m_current_mana << "\n" << this->
                exp << "\n" << this->prologueState() << "\n" << this->getHPpot() << "\n" << this->getHPRegpot() << "\n" << this->getManapot() << "\n" << this->getActionpot() << "\n" << this->getWeaknessMult(DamageType::MagicEnergy) << "\n" << this->getWeaknessMult(DamageType::MagicFire) << "\n" << this->getWeaknessMult(DamageType::MagicIce) << "\n" << this->getWeaknessMult(DamageType::MagicEarth) << "\n" << this->getWeaknessMult(DamageType::MagicWater) << "\n" << this->
                getWeaknessMult(DamageType::MagicPoison) << "\n" << this->getWeaknessMult(DamageType::MagicAir) << "\n" << this->getWeaknessMult(DamageType::Physical) << "\n" << this->getWeaknessMult(DamageType::Environment) << "\n" << this->getExtraSlot() << "\n";

        int invSize = this->m_inventory.getInvSize() - this->m_inventory.getAvaiableAmount();
        file << invSize << "\n";

        const auto& inv = this->m_inventory.m_inventory;

        for (size_t i = 0; i < inv.size(); ++i) {
            const Item& item = inv[i];
            itemStats item_stats = item.getStats();
            if (item.getId() > 0) {
                file << i << "\n" << item.getId() << "\n" << item_stats.hp << "\n" << item_stats.ad << "\n" << item_stats.def << "\n" << item_stats.mana << "\n" << item_stats.speed << "\n";
            }
        }

        if (m_helmet_slot) {
            itemStats item_stats = m_helmet_slot->getStats();
            file << "x\n" << m_helmet_slot->getId() << "\n" << item_stats.hp << "\n" << item_stats.ad << "\n" << item_stats.def << "\n" << item_stats.mana << "\n" << item_stats.speed << "\n";
        }
        else
            file << "NOHELMET\n";

        if (m_necklace_slot) {
            itemStats item_stats = m_necklace_slot->getStats();
            file << "x\n" << m_necklace_slot->getId() << "\n" << item_stats.hp << "\n" << item_stats.ad << "\n" << item_stats.def << "\n" << item_stats.mana << "\n" << item_stats.speed << "\n";
        }
        else
            file << "NONECKLACE\n";

        if (m_chestplate_slot) {
            itemStats item_stats = m_chestplate_slot->getStats();
            file << "x\n" << m_chestplate_slot->getId() << "\n" << item_stats.hp << "\n" << item_stats.ad << "\n" << item_stats.def << "\n" << item_stats.mana << "\n" << item_stats.speed << "\n";
        }
        else
            file << "NOCHEST\n";

        if (m_gloves_slot) {
            itemStats item_stats = m_gloves_slot->getStats();
            file << "x\n" << m_gloves_slot->getId() << "\n" << item_stats.hp << "\n" << item_stats.ad << "\n" << item_stats.def << "\n" << item_stats.mana << "\n" << item_stats.speed << "\n";
        }
        else
            file << "NOGLOVES\n";

        if (m_ring_slot) {
            itemStats item_stats = m_ring_slot->getStats();
            file << "x\n" << m_ring_slot->getId() << "\n" << item_stats.hp << "\n" << item_stats.ad << "\n" << item_stats.def << "\n" << item_stats.mana << "\n" << item_stats.speed << "\n";
        }
        else
            file << "NORING\n";

        if (m_leggings_slot) {
            itemStats item_stats = m_leggings_slot->getStats();
            file << "x\n" << m_leggings_slot->getId() << "\n" << item_stats.hp << "\n" << item_stats.ad << "\n" << item_stats.def << "\n" << item_stats.mana << "\n" << item_stats.speed << "\n";
        }
        else
            file << "NOLEGS\n";

        if (m_boots_slot) {
            itemStats item_stats = m_boots_slot->getStats();
            file << "x\n" << m_boots_slot->getId() << "\n" << item_stats.hp << "\n" << item_stats.ad << "\n" << item_stats.def << "\n" << item_stats.mana << "\n" << item_stats.speed << "\n";
        }
        else
            file << "NOBOOTS\n";

        if (m_weapon_slot) {
            itemStats item_stats = m_weapon_slot->getStats();
            file << "x\n" << m_weapon_slot->getId() << "\n" << item_stats.hp << "\n" << item_stats.ad << "\n" << item_stats.def << "\n" << item_stats.mana << "\n" << item_stats.speed << "\n";
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
        hero->setWeaknessMult(DamageType::MagicEnergy, energy);
        hero->setWeaknessMult(DamageType::MagicFire, fire);
        hero->setWeaknessMult(DamageType::MagicIce, ice);
        hero->setWeaknessMult(DamageType::MagicEarth, earth);
        hero->setWeaknessMult(DamageType::MagicWater, water);
        hero->setWeaknessMult(DamageType::MagicPoison, poison);
        hero->setWeaknessMult(DamageType::MagicAir, air);
        hero->setWeaknessMult(DamageType::Physical, phys);
        hero->setWeaknessMult(DamageType::Environment, env);

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
            hero->m_inventory.addItem(item, slot);
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
            hero->m_helmet_slot = std::make_optional<Item>(helmet);
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
            hero->m_necklace_slot = std::make_optional<Item>(necklace);
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
            hero->m_chestplate_slot = std::make_optional<Item>(chest);
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
            hero->m_gloves_slot = std::make_optional<Item>(gloves);
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
            hero->m_ring_slot = std::make_optional<Item>(ring);
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
            hero->m_leggings_slot = std::make_optional<Item>(leg);
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
            hero->m_boots_slot = std::make_optional<Item>(boots);
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
            hero->m_weapon_slot = std::make_optional<Item>(weapon);
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
