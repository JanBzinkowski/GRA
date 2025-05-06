#include "include/Item.h"
#include "Hero.h"

itemStats Item::getStats () const {
    return stats;
}

int Item::getId () const {
    return id;
}

itemType Item::getType () const {
    return itemData.at(id).type;
}

std::string Item::getTypeString () const {
    switch (getType()) {
        case itemType::Boots:
            return "Boots";
        case itemType::Leggings:
            return "Leggings";
        case itemType::Chestplate:
            return "Chestplate";
        case itemType::Helmet:
            return "Helmet";
        case itemType::Gloves:
            return "Gloves";
        case itemType::Ring:
            return "Ring";
        case itemType::Necklace:
            return "Necklace";
        case itemType::Weapon:
            return "Weapon";
        default:
            return "Unknown";
    }
}

std::string Item::getPath () const {
    return stats.item_path;
}

void Item::generateStats (std::mt19937& gen, Hero*& hero) {
    auto randomize = [&gen] (int min, int max) ->int {
        std::uniform_int_distribution<> dist(min, max);
        return dist(gen);
    };

    stats.hp = randomize(stats.hpmin, stats.hpmax);
    stats.ad = randomize(stats.admin, stats.admax);
    stats.def = randomize(stats.defmin, stats.defmax);
    stats.mana = randomize(stats.manamin, stats.manamax);
    stats.speed = randomize(stats.speedmin, stats.speedmax);
    if (stats.hpmax > 0)
        stats.hp += hero->getLvl();
    if (stats.admax > 0)
        stats.ad += hero->getLvl();
    if (stats.defmax > 0)
        stats.def += hero->getLvl();
    if (stats.manamax > 0)
        stats.mana += hero->getLvl();
    if (stats.speedmax > 0)
        stats.speed += hero->getLvl();
}

std::string Item::getData () const {
    std::string text;
    text = stats.name + " \nType: " + getTypeString() + ",\nItem LVL: " + std::to_string(stats.itemLvl);
    if (stats.hp > 0)
        text += ",\nHP: " + std::to_string(stats.hp);
    if (stats.def > 0)
        text += ",\nDEF: " + std::to_string(stats.def);
    if (stats.ad > 0)
        text += ",\nAD: " + std::to_string(stats.ad);
    if (stats.mana > 0)
        text += ",\nMana: " + std::to_string(stats.mana);
    if (stats.speed > 0)
        text += ",\nSpeed: " + std::to_string(stats.speed);
    text += "\nPrice: " + std::to_string(stats.price) + " gold coins";
    return text;
}
