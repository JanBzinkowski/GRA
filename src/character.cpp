#include "character.h"
#include <bits/algorithmfwd.h>
#include "damage.h"
#include "itemType.h"
#include "button.h"


extern std::unordered_map<int, itemStats> itemData;

int character::getCurrentHP () const {
    return m_current_HP;
}

void character::setCurrentHP (const int current_HP) {
    m_current_HP = current_HP;
}

void character::incCurrentHP (const int current_HP_inc) {
    m_current_HP += current_HP_inc;
}

float character::getAtkChance (Enemy*& enemy, Hero*& hero, bool toHero) const {
    int lvldif;
    if (toHero) {
        lvldif = (this->getLvl()) - (hero->getLvl());
    }
    else
        lvldif = (this->getLvl()) - (enemy->getLvl());

    float base = 0;
    switch (m_atk_type_nb) {
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
    float chance = std::clamp(base + 0.1f * lvldif, 0.0f, 1.0f);
    return chance;
}

float character::getMultDmg () const {
    if (m_atk_type_nb == 1) {
        return 1;
    }
    if (m_atk_type_nb == 2) {
        return 1.3f;
    }
    if (m_atk_type_nb == 3) {
        return 1.8f;
    }
    return 0;
}

Stats character::getStats () const {
    return m_stats;
}

StatsIncrese character::getStatsInc () const {
    return m_stats_inc;
}

int character::getMaxHP () const {
    return m_stats.base_hp;
}

int character::getLvl () const {
    return m_stats.lvl;
}

int character::getAd () const {
    return m_stats.ad;
}

int character::getDef () const {
    return m_stats.def;
}

int character::getMaxMana () const {
    return m_stats.mana;
}

std::string character::getName () const {
    return m_name;
}

std::string character::getPath () const {
    return m_stats.path;
}

int character::getSpeed () const {
    return m_stats.speed;
}

int character::getMaxHPInc () const {
    return m_stats_inc.base_HP_inc;
}

int character::getAdInc () const {
    return m_stats_inc.ad_inc;
}

int character::getDefInc () const {
    return m_stats_inc.def_inc;
}

int character::getMaxManaInc () const {
    return m_stats_inc.mana_inc;
}

int character::getSpeedInc () const {
    return m_stats_inc.speed_inc;
}


float character::getResistance (const DamageType& type) const {
    auto it = m_resistance.find(type);
    return it != m_resistance.end()? it->second : 1.0f;
}

void character::setResist (const DamageType& type, float resist) {
    m_resistance[type] = resist;
}

int character::getAtkTypeNB () const {
    return m_atk_type_nb;
}

void character::setAtkTypeNB (int nb) {
    m_atk_type_nb = nb;
}

