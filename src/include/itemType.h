#ifndef ITEMTYPE_H
#define ITEMTYPE_H

#include <unordered_map>
#include <string>
#include <random>

class character;

enum class itemType {
    Boots,
    Leggings,
    Chestplate,
    Helmet,
    Gloves,
    Ring,
    Necklace,
    Weapon,
    ERROR
};

struct itemStats {
    std::string name;
    itemType type;
    int hpmin = 0;
    int hpmax = 0;
    int hp = 0;
    int admin = 0;
    int admax = 0;
    int ad = 0;
    int defmin = 0;
    int defmax = 0;
    int def = 0;
    int manamin = 0;
    int manamax = 0;
    int mana = 0;
    int speedmin = 0;
    int speedmax = 0;
    int speed = 0;
    int itemLvl = 1;
    int price = 20;
    bool isArtifact = false;
    std::string item_path;
};

extern std::unordered_map<int, itemStats> itemData;

#endif //ITEMTYPE_H
