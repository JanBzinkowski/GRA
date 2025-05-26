#include "character.h"
#include <algorithm>

int Character::getCurrentHP () const {
    return m_current_HP;
}

void Character::setCurrentHP (const int current_HP) {
    m_current_HP = current_HP;
}

void Character::incCurrentHP (const int current_HP_inc) {
    m_current_HP += current_HP_inc;
}

float Character::getMultDmg () const {
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

Stats Character::getStats () const {
    return m_stats;
}

void Character::setStats (const Stats& stats) {
    m_stats = stats;
}

StatsIncrese Character::getStatsInc () const {
    return m_stats_inc;
}

int Character::getMaxHP () const {
    return m_stats.base_hp;
}

int Character::getLvl () const {
    return m_stats.lvl;
}

int Character::getAd () const {
    return m_stats.ad;
}

int Character::getDef () const {
    return m_stats.def;
}

int Character::getMaxMana () const {
    return m_stats.mana;
}

std::string Character::getName () const {
    return m_name;
}

std::string Character::getPath () const {
    return m_stats.path;
}

int Character::getSpeed () const {
    return m_stats.speed;
}

int Character::getMaxHPInc () const {
    return m_stats_inc.base_HP_inc;
}

int Character::getAdInc () const {
    return m_stats_inc.ad_inc;
}

int Character::getDefInc () const {
    return m_stats_inc.def_inc;
}

int Character::getMaxManaInc () const {
    return m_stats_inc.mana_inc;
}

int Character::getSpeedInc () const {
    return m_stats_inc.speed_inc;
}


float Character::getWeaknessMult (const DamageType& type) const {
    auto it = m_weakness_multiplayer.find(type);
    return it != m_weakness_multiplayer.end()? it->second : 1.0f;
}

void Character::setWeaknessMult (const DamageType& type, float weakness_mult) {
    m_weakness_multiplayer[type] = weakness_mult;
}

int Character::getAtkTypeNB () const {
    return m_atk_type_nb;
}

void Character::setAtkTypeNB (int attack_number) {
    m_atk_type_nb = attack_number;
}