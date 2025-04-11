#include "include/itemType.h"
#include <iostream>
#include <string>
#include <random>
#include "character.h"

std::unordered_map<int, itemStats> itemData = {
    {0, {"Error Item", itemType::ERROR, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, false}},
    //warrior/crossbow/berserker lvl 1-7
    {1, {"Rotten Guardian's Boots", itemType::Boots, 2, 5, 0, 0, 0, 0, 2, 5, 0, 0, 0, 0, 1, 2, 0, 1, 15, false}},
    {2, {"Warrior's Worn Boots", itemType::Boots, 2, 4, 0, 0, 0, 0, 2, 4, 0, 0, 0, 0, 1, 2, 0, 1, 15, false}},
    {3, {"Defender's Torn Boots", itemType::Boots, 2, 4, 0, 0, 0, 0, 2, 4, 0, 0, 0, 0, 1, 2, 0, 1, 15, false}},
    {4, {"Bent Steel Boots", itemType::Boots, 2, 4, 0, 0, 0, 0, 2, 4, 0, 0, 0, 0, 1, 2, 0, 1, 15, false}},
    {5, {"Ripped Armored Pants", itemType::Leggings, 3, 6, 0, 0, 0, 0, 3, 6, 0, 1, 1, 0, 0, 0, 0, 1, 20, false}},
    {6,{"Pants with Scrached Knee Pads", itemType::Leggings, 3, 6, 0, 0, 0, 0, 3, 6, 0, 1, 1, 0, 0, 0, 0, 1, 20, false}},
    {7, {"Worn Combat Pants", itemType::Leggings, 3, 6, 0, 0, 0, 0, 3, 6, 0, 1, 1, 0, 0, 0, 0, 1, 20, false}},
    {8, {"Knight's Torn Leggings", itemType::Leggings, 3, 6, 0, 0, 0, 0, 3, 6, 0, 1, 1, 0, 0, 0, 0, 1, 20, false}},
    {9, {"Ripped Armor", itemType::Chestplate, 3, 8, 0, 0, 0, 0, 3, 8, 0, 1, 1, 0, 0, 0, 0, 1, 25, false}},
    {10, {"Tattered Plate Armor", itemType::Chestplate, 3, 8, 0, 0, 0, 0, 3, 8, 0, 1, 1, 0, 0, 0, 0, 1, 25, false}},
    {11, {"Broken Plate Armor", itemType::Chestplate, 3, 8, 0, 0, 0, 0, 3, 8, 0, 1, 1, 0, 0, 0, 0, 1, 25, false}},
    {12, {"Dent Plate Armor", itemType::Chestplate, 3, 8, 0, 0, 0, 0, 3, 8, 0, 1, 1, 0, 0, 0, 0, 1, 25, false}},
    {13, {"Worn Battle Gloves", itemType::Gloves, 0, 0, 0, 1, 2, 0, 1, 4, 0, 0, 0, 0, 0, 0, 0, 1, 15, false}},
    {14, {"Tattered Gloves", itemType::Gloves, 0, 0, 0, 1, 2, 0, 1, 4, 0, 0, 0, 0, 0, 0, 0, 1, 15, false}},
    {15, {"Guard's Old Gloves", itemType::Gloves, 0, 0, 0, 1, 2, 0, 1, 4, 0, 0, 0, 0, 0, 0, 0, 1, 15, false}},
    {16, {"Field-Tested Gloves", itemType::Gloves, 0, 0, 0, 1, 2, 0, 1, 4, 0, 0, 0, 0, 0, 0, 0, 1, 15, false}},
    {17, {"Old Rusted Helmet", itemType::Helmet, 2, 6, 0, 0, 0, 0, 2, 5, 0, 0, 0, 0, 0, 0, 0, 1, 20, false}},
    {18, {"Dent Helmet", itemType::Helmet, 2, 6, 0, 0, 0, 0, 2, 5, 0, 0, 0, 0, 0, 0, 0, 1, 20, false}},
    {19, {"Helmet with Missing Visor", itemType::Helmet, 2, 6, 0, 0, 0, 0, 2, 5, 0, 0, 0, 0, 0, 0, 0, 1, 20, false}},
    {20, {"Cracked Helmet", itemType::Helmet, 2, 6, 0, 0, 0, 0, 2, 5, 0, 0, 0, 0, 0, 0, 0, 1, 20, false}},
    //mage/palladin/alchemist lvl 1-7
    {21, {"Worn Spellboots", itemType::Boots, 1, 3, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 1, 3, 0, 1, 15, false}},
    {22, {"Sorcerer's Worn Boots", itemType::Boots, 1, 3, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 1, 3, 0, 1, 15, false}},
    {23, {"Wizard's Threadbare Boots", itemType::Boots, 1, 3, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 1, 3, 0, 1, 15, false}},
    {24, {"Tattered Magic Boots", itemType::Boots, 1, 3, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 1, 3, 0, 1, 15, false}},
    {25, {"Tattered Arcane Pants", itemType::Leggings, 1, 3, 0, 0, 0, 0, 1, 3, 0, 1, 2, 0, 0, 0, 0, 1, 20, false}},
    {26, {"Mage's Scrached Pants", itemType::Leggings, 1, 3, 0, 0, 0, 0, 1, 3, 0, 1, 2, 0, 0, 0, 0, 1, 20, false}},
    {27, {"Ripped Arcane Trousers", itemType::Leggings, 1, 3, 0, 0, 0, 0, 1, 3, 0, 1, 2, 0, 0, 0, 0, 1, 20, false}},
    {28, {"Sorcerer's Torn Leggings", itemType::Leggings, 1, 3, 0, 0, 0, 0, 1, 3, 0, 1, 2, 0, 0, 0, 0, 1, 20, false}},
    {29, {"Wizard's Thredbare Robe", itemType::Chestplate, 1, 4, 0, 0, 0, 0, 1, 4, 0, 1, 3, 0, 0, 0, 0, 1, 25, false}},
    {30, {"Tattered Robe", itemType::Chestplate, 1, 4, 0, 0, 0, 0, 1, 4, 0, 1, 3, 0, 0, 0, 0, 1, 25, false}},
    {31, {"Sorcerer's Faded Tunic", itemType::Chestplate, 1, 4, 0, 0, 0, 0, 1, 4, 0, 1, 3, 0, 0, 0, 0, 1, 25, false}},
    {32, {"Scrached Tunic", itemType::Chestplate, 1, 4, 0, 0, 0, 0, 1, 4, 0, 1, 3, 0, 0, 0, 0, 1, 25, false}},
    {33, {"Battlemage's Old Gloves", itemType::Gloves, 0, 0, 0, 1, 4, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 1, 15, false}},
    {34, {"Tattered Magic Gloves", itemType::Gloves, 0, 0, 0, 1, 4, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 1, 15, false}},
    {35, {"Worn Mystic Gloves", itemType::Gloves, 0, 0, 0, 1, 4, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 1, 15, false}},
    {36, {"Wizard's Worn Gloves", itemType::Gloves, 0, 0, 0, 1, 4, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 1, 15, false}},
    {37, {"Torn Arcane Hood", itemType::Helmet, 1, 3, 0, 0, 0, 0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 1, 20, false}},
    {38, {"Sorcerer's Worn Hood", itemType::Helmet, 1, 3, 0, 0, 0, 0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 1, 20, false}},
    {39, {"Mage's Old Hood", itemType::Helmet, 1, 3, 0, 0, 0, 0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 1, 20, false}},
    {40, {"Tattered Mystic Hood", itemType::Helmet, 1, 3, 0, 0, 0, 0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 1, 20, false}},
    //archer/hunter/druid lvl 1-7
    {41, {"Worn Lether Boots", itemType::Boots, 1, 3, 0, 0, 0, 0, 1, 3, 0, 0, 0, 0, 1, 4, 0, 1, 15, false}},
    {42, {"Torn Traveller's Boots", itemType::Boots, 1, 3, 0, 0, 0, 0, 1, 3, 0, 0, 0, 0, 1, 4, 0, 1, 15, false}},
    {43, {"Scuffed Hiking Boots", itemType::Boots, 1, 3, 0, 0, 0, 0, 1, 3, 0, 0, 0, 0, 1, 4, 0, 1, 15, false}},
    {44, {"Forester's Tattered Boots", itemType::Boots, 1, 3, 0, 0, 0, 0, 1, 3, 0, 0, 0, 0, 1, 4, 0, 1, 15, false}},
    {45, {"Tattered Leather Trousers", itemType::Leggings, 1, 4, 0, 0, 0, 0, 1, 4, 0, 1, 1, 0, 0, 0, 0, 1, 20, false}},
    {46, {"Adventurer's Worn Pants", itemType::Leggings, 1, 4, 0, 0, 0, 0, 1, 4, 0, 1, 1, 0, 0, 0, 0, 1, 20, false}},
    {47, {"Faded Hunting Pants", itemType::Leggings, 1, 4, 0, 0, 0, 0, 1, 4, 0, 1, 1, 0, 0, 0, 0, 1, 20, false}},
    {48, {"Ragged Travel Leggings", itemType::Leggings, 1, 4, 0, 0, 0, 0, 1, 4, 0, 1, 1, 0, 0, 0, 0, 1, 20, false}},
    {49, {"Thredbare Leather Tunic", itemType::Chestplate, 2, 5, 0, 0, 0, 0, 2, 5, 0, 1, 2, 0, 0, 0, 0, 1, 25, false}},
    {50, {"Old Leather Vest", itemType::Chestplate, 2, 5, 0, 0, 0, 0, 2, 5, 0, 1, 2, 0, 0, 0, 0, 1, 25, false}},
    {51, {"Rugged Hide Tunic", itemType::Chestplate, 2, 5, 0, 0, 0, 0, 2, 5, 0, 1, 2, 0, 0, 0, 0, 1, 25, false}},
    {52, {"Tattered Travel Vest", itemType::Chestplate, 2, 5, 0, 0, 0, 0, 2, 5, 0, 1, 2, 0, 0, 0, 0, 1, 25, false}},
    {53, {"Explorer's Old Gloves", itemType::Gloves, 0, 0, 0, 1, 3, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 1, 15, false}},
    {54, {"Ripped Leather Gloves", itemType::Gloves, 0, 0, 0, 1, 3, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 1, 15, false}},
    {55, {"Torn Cloth Gloves", itemType::Gloves, 0, 0, 0, 1, 3, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 1, 15, false}},
    {56, {"Hunter's Worn Gloves", itemType::Gloves, 0, 0, 0, 1, 3, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 1, 15, false}},
    {57, {"Torn Leather Hood", itemType::Helmet, 1, 4, 0, 0, 0, 0, 1, 4, 0, 0, 0, 0, 0, 0, 0, 1, 20, false}},
    {58, {"Ripped Hood", itemType::Helmet, 1, 4, 0, 0, 0, 0, 1, 4, 0, 0, 0, 0, 0, 0, 0, 1, 20, false}},
    {59, {"Old Cloth Hood", itemType::Helmet, 1, 4, 0, 0, 0, 0, 1, 4, 0, 0, 0, 0, 0, 0, 0, 1, 20, false}},
    {60, {"Beggar's Worn Hood", itemType::Helmet, 1, 4, 0, 0, 0, 0, 1, 4, 0, 0, 0, 0, 0, 0, 0, 1, 20, false}},
};


itemStats Item::getStats () const {
    return stats;
}

int Item::getId () const {
    return id;
}

itemType Item::getType () const {
    return itemData . at(id) . type;
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

void Inventory::addItem (const Item& item) {
    items . push_back(item);
}

void Inventory::removeItem (int index) {
    if (index >= 0 && index < static_cast<int>(items . size())) {
        items . erase(items . begin() + index);
    }
}

std::optional<Item> Inventory::getItemByIndex (size_t index) const {
    return items[index - 1];
}

void Inventory::printInv () const {
    if (items . empty()) {
        std::cout << "Inventory is empty.\n";
        return;
    }

    std::cout << "Items in inventory:\n" << std::endl;
    for (size_t i = 0; i < items . size(); ++i) {
        const auto& stats = items[i] . getStats();
        std::cout << i + 1 << ". " << stats . name << " Type: " << items[i] . getTypeString() << ",\nItem LVL: " <<
                stats . itemLvl;
        if (stats . hp > 0)
            std::cout << ", HP: " << stats . hp;
        if (stats . def > 0)
            std::cout << ", DEF: " << stats . def;
        if (stats . ad > 0)
            std::cout << ", AD: " << stats . ad;
        if (stats . mana > 0)
            std::cout << ", Mana: " << stats . mana;
        if (stats . speed > 0)
            std::cout << ", Speed: " << stats . speed << std::endl;
        std::cout << std::endl;
    }
}

void Item::generateStats (std::mt19937& gen, character*& hero) {
    auto randomize = [&gen] (int min, int max) -> int {
        std::uniform_int_distribution<> dist(min, max);
        return dist(gen);
    };

    stats . hp = randomize(stats . hpmin, stats . hpmax);
    stats . ad = randomize(stats . admin, stats . admax);
    stats . def = randomize(stats . defmin, stats . defmax);
    stats . mana = randomize(stats . manamin, stats . manamax);
    stats . speed = randomize(stats . speedmin, stats . speedmax);
    if (stats . hpmax > 0)
        stats . hp += hero -> getLvl();
    if (stats . admax > 0)
        stats . ad += hero -> getLvl();
    if (stats . defmax > 0)
        stats . def += hero -> getLvl();
    if (stats . manamax > 0)
        stats . mana += hero -> getLvl();
    if (stats . speedmax > 0)
        stats . speed += hero -> getLvl();
}

int Inventory::getInvSize () const {
    return items . size();
}
