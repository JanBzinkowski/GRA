#include "include/itemType.h"
#include <iostream>
#include <string>
#include <random>
#include "character.h"
// @formatter:off
std::unordered_map<int, itemStats> itemData = {
    {0,{"Error Item",itemType::ERROR,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,false,"src\\textures\\items\\Buty.png"}},
    //warrior/crossbow/berserker lvl 1-7
    {1, {"Worn Leather Boots", itemType::Boots, 1, 3, 0, 0, 0, 0, 1, 3, 0, 0, 0, 0, 1, 4, 0, 1, 15, false, "src\\textures\\items\\Buty.png"}},
    {2, {"Torn Traveller's Boots", itemType::Boots, 1, 3, 0, 0, 0, 0, 1, 3, 0, 0, 0, 0, 1, 4, 0, 1, 15, false, "src\\textures\\items\\Buty.png"}},
    {3, {"Scuffed Hiking Boots", itemType::Boots, 1, 3, 0, 0, 0, 0, 1, 3, 0, 0, 0, 0, 1, 4, 0, 1, 15, false, "src\\textures\\items\\Buty.png"}},
    {4, {"Forester's Tattered Boots", itemType::Boots, 1, 3, 0, 0, 0, 0, 1, 3, 0, 0, 0, 0, 1, 4, 0, 1, 15, false, "src\\textures\\items\\Buty.png"}},
    {5, {"Tattered Leather Trousers", itemType::Leggings, 1, 4, 0, 0, 0, 0, 1, 4, 0, 1, 1, 0, 0, 0, 0, 1, 20, false, "src\\textures\\items\\Buty.png"}},
    {6, {"Adventurer's Worn Pants", itemType::Leggings, 1, 4, 0, 0, 0, 0, 1, 4, 0, 1, 1, 0, 0, 0, 0, 1, 20, false, "src\\textures\\items\\Buty.png"}},
    {7, {"Faded Hunting Pants", itemType::Leggings, 1, 4, 0, 0, 0, 0, 1, 4, 0, 1, 1, 0, 0, 0, 0, 1, 20, false, "src\\textures\\items\\Buty.png"}},
    {8, {"Ragged Travel Leggings", itemType::Leggings, 1, 4, 0, 0, 0, 0, 1, 4, 0, 1, 1, 0, 0, 0, 0, 1, 20, false, "src\\textures\\items\\Buty.png"}},
    {9, {"Threadbare Leather Tunic", itemType::Chestplate, 2, 5, 0, 0, 0, 0, 2, 5, 0, 1, 2, 0, 0, 0, 0, 1, 25, false, "src\\textures\\items\\Buty.png"}},
    {10, {"Old Leather Vest", itemType::Chestplate, 2, 5, 0, 0, 0, 0, 2, 5, 0, 1, 2, 0, 0, 0, 0, 1, 25, false, "src\\textures\\items\\Buty.png"}},
    {11, {"Rugged Hide Tunic", itemType::Chestplate, 2, 5, 0, 0, 0, 0, 2, 5, 0, 1, 2, 0, 0, 0, 0, 1, 25, false, "src\\textures\\items\\Buty.png"}},
    {12, {"Tattered Travel Vest", itemType::Chestplate, 2, 5, 0, 0, 0, 0, 2, 5, 0, 1, 2, 0, 0, 0, 0, 1, 25, false, "src\\textures\\items\\Buty.png"}},
    {13, {"Explorer's Old Gloves", itemType::Gloves, 0, 0, 0, 1, 3, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 1, 15, false, "src\\textures\\items\\Buty.png"}},
    {14, {"Ripped Leather Gloves", itemType::Gloves, 0, 0, 0, 1, 3, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 1, 15, false, "src\\textures\\items\\Buty.png"}},
    {15, {"Torn Cloth Gloves", itemType::Gloves, 0, 0, 0, 1, 3, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 1, 15, false, "src\\textures\\items\\Buty.png"}},
    {16, {"Hunter's Worn Gloves", itemType::Gloves, 0, 0, 0, 1, 3, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 1, 15, false, "src\\textures\\items\\Buty.png"}},
    {17, {"Torn Leather Hood", itemType::Helmet, 1, 4, 0, 0, 0, 0, 1, 4, 0, 0, 0, 0, 0, 0, 0, 1, 20, false, "src\\textures\\items\\Buty.png"}},
    {18, {"Ripped Hood", itemType::Helmet, 1, 4, 0, 0, 0, 0, 1, 4, 0, 0, 0, 0, 0, 0, 0, 1, 20, false, "src\\textures\\items\\Buty.png"}},
    {19, {"Old Cloth Hood", itemType::Helmet, 1, 4, 0, 0, 0, 0, 1, 4, 0, 0, 0, 0, 0, 0, 0, 1, 20, false, "src\\textures\\items\\Buty.png"}},
    {20, {"Beggar's Worn Hood", itemType::Helmet, 1, 4, 0, 0, 0, 0, 1, 4, 0, 0, 0, 0, 0, 0, 0, 1, 20, false, "src\\textures\\items\\Buty.png"}},

    //mage/palladin/alchemist lvl 1-7
    {21,{"Worn Spellboots",itemType::Boots,1,3,0,0,0,0,1,2,0,0,0,0,1,3,0,1,15,false,"src\\textures\\items\\Buty.png"}},
    {22,{"Sorcerer's Worn Boots",itemType::Boots,1,3,0,0,0,0,1,2,0,0,0,0,1,3,0,1,15,false,"src\\textures\\items\\Buty.png"}},
    {23,{"Wizard's Threadbare Boots",itemType::Boots,1,3,0,0,0,0,1,2,0,0,0,0,1,3,0,1,15,false,"src\\textures\\items\\Buty.png"}},
    {24,{"Tattered Magic Boots",itemType::Boots,1,3,0,0,0,0,1,2,0,0,0,0,1,3,0,1,15,false,"src\\textures\\items\\Buty.png"}},
    {25,{"Tattered Arcane Pants",itemType::Leggings,1,3,0,0,0,0,1,3,0,1,2,0,0,0,0,1,20,false,"src\\textures\\items\\Buty.png"}},
    {26,{"Mage's Scrached Pants",itemType::Leggings,1,3,0,0,0,0,1,3,0,1,2,0,0,0,0,1,20,false,"src\\textures\\items\\Buty.png"}},
    {27,{"Ripped Arcane Trousers",itemType::Leggings,1,3,0,0,0,0,1,3,0,1,2,0,0,0,0,1,20,false,"src\\textures\\items\\Buty.png"}},
    {28,{"Sorcerer's Torn Leggings",itemType::Leggings,1,3,0,0,0,0,1,3,0,1,2,0,0,0,0,1,20,false,"src\\textures\\items\\Buty.png"}},
    {29,{"Wizard's Thredbare Robe",itemType::Chestplate,1,4,0,0,0,0,1,4,0,1,3,0,0,0,0,1,25,false,"src\\textures\\items\\Buty.png"}},
    {30,{"Tattered Robe",itemType::Chestplate,1,4,0,0,0,0,1,4,0,1,3,0,0,0,0,1,25,false,"src\\textures\\items\\Buty.png"}},
    {31,{"Sorcerer's Faded Tunic",itemType::Chestplate,1,4,0,0,0,0,1,4,0,1,3,0,0,0,0,1,25,false,"src\\textures\\items\\Buty.png"}},
    {32,{"Scrached Tunic",itemType::Chestplate,1,4,0,0,0,0,1,4,0,1,3,0,0,0,0,1,25,false,"src\\textures\\items\\Buty.png"}},
    {33,{"Battlemage's Old Gloves",itemType::Gloves,0,0,0,1,4,0,1,2,0,0,0,0,0,0,0,1,15,false,"src\\textures\\items\\Buty.png"}},
    {34,{"Tattered Magic Gloves",itemType::Gloves,0,0,0,1,4,0,1,2,0,0,0,0,0,0,0,1,15,false,"src\\textures\\items\\Buty.png"}},
    {35,{"Worn Mystic Gloves",itemType::Gloves,0,0,0,1,4,0,1,2,0,0,0,0,0,0,0,1,15,false,"src\\textures\\items\\Buty.png"}},
    {36,{"Wizard's Worn Gloves",itemType::Gloves,0,0,0,1,4,0,1,2,0,0,0,0,0,0,0,1,15,false,"src\\textures\\items\\Buty.png"}},
    {37,{"Torn Arcane Hood",itemType::Helmet,1,3,0,0,0,0,1,3,0,0,0,0,0,0,0,1,20,false,"src\\textures\\items\\Buty.png"}},
    {38,{"Sorcerer's Worn Hood",itemType::Helmet,1,3,0,0,0,0,1,3,0,0,0,0,0,0,0,1,20,false,"src\\textures\\items\\Buty.png"}},
    {39,{"Mage's Old Hood",itemType::Helmet,1,3,0,0,0,0,1,3,0,0,0,0,0,0,0,1,20,false,"src\\textures\\items\\Buty.png"}},
    {40,{"Tattered Mystic Hood",itemType::Helmet,1,3,0,0,0,0,1,3,0,0,0,0,0,0,0,1,20,false,"src\\textures\\items\\Buty.png"}},

    //archer/hunter/druid lvl 1-7
    {41,{"Worn Lether Boots",itemType::Boots,1,3,0,0,0,0,1,3,0,0,0,0,1,4,0,1,15,false,"src\\textures\\items\\Buty.png"}},
    {42,{"Torn Traveller's Boots",itemType::Boots,1,3,0,0,0,0,1,3,0,0,0,0,1,4,0,1,15,false,"src\\textures\\items\\Buty.png"}},
    {43,{"Scuffed Hiking Boots",itemType::Boots,1,3,0,0,0,0,1,3,0,0,0,0,1,4,0,1,15,false,"src\\textures\\items\\Buty.png"}},
    {44,{"Forester's Tattered Boots",itemType::Boots,1,3,0,0,0,0,1,3,0,0,0,0,1,4,0,1,15,false,"src\\textures\\items\\Buty.png"}},
    {45,{"Tattered Leather Trousers",itemType::Leggings,1,4,0,0,0,0,1,4,0,1,1,0,0,0,0,1,20,false,"src\\textures\\items\\Buty.png"}},
    {46,{"Adventurer's Worn Pants",itemType::Leggings,1,4,0,0,0,0,1,4,0,1,1,0,0,0,0,1,20,false,"src\\textures\\items\\Buty.png"}},
    {47,{"Faded Hunting Pants",itemType::Leggings,1,4,0,0,0,0,1,4,0,1,1,0,0,0,0,1,20,false,"src\\textures\\items\\Buty.png"}},
    {48,{"Ragged Travel Leggings",itemType::Leggings,1,4,0,0,0,0,1,4,0,1,1,0,0,0,0,1,20,false,"src\\textures\\items\\Buty.png"}},
    {49,{"Thredbare Leather Tunic",itemType::Chestplate,2,5,0,0,0,0,2,5,0,1,2,0,0,0,0,1,25,false,"src\\textures\\items\\Buty.png"}},
    {50,{"Old Leather Vest",itemType::Chestplate,2,5,0,0,0,0,2,5,0,1,2,0,0,0,0,1,25,false,"src\\textures\\items\\Buty.png"}},
    {51,{"Rugged Hide Tunic",itemType::Chestplate,2,5,0,0,0,0,2,5,0,1,2,0,0,0,0,1,25,false,"src\\textures\\items\\Buty.png"}},
    {52,{"Tattered Travel Vest",itemType::Chestplate,2,5,0,0,0,0,2,5,0,1,2,0,0,0,0,1,25,false,"src\\textures\\items\\Buty.png"}},
    {53,{"Explorer's Old Gloves",itemType::Gloves,0,0,0,1,3,0,1,2,0,0,0,0,0,0,0,1,15,false,"src\\textures\\items\\Buty.png"}},
    {54,{"Ripped Leather Gloves",itemType::Gloves,0,0,0,1,3,0,1,2,0,0,0,0,0,0,0,1,15,false,"src\\textures\\items\\Buty.png"}},
    {55,{"Torn Cloth Gloves",itemType::Gloves,0,0,0,1,3,0,1,2,0,0,0,0,0,0,0,1,15,false,"src\\textures\\items\\Buty.png"}},
    {56,{"Hunter's Worn Gloves",itemType::Gloves,0,0,0,1,3,0,1,2,0,0,0,0,0,0,0,1,15,false,"src\\textures\\items\\Buty.png"}},
    {57,{"Torn Leather Hood",itemType::Helmet,1,4,0,0,0,0,1,4,0,0,0,0,0,0,0,1,20,false,"src\\textures\\items\\Buty.png"}},
    {58,{"Ripped Hood",itemType::Helmet,1,4,0,0,0,0,1,4,0,0,0,0,0,0,0,1,20,false,"src\\textures\\items\\Buty.png"}},
    {59,{"Old Cloth Hood",itemType::Helmet,1,4,0,0,0,0,1,4,0,0,0,0,0,0,0,1,20,false,"src\\textures\\items\\Buty.png"}},
    {60,{"Beggar's Worn Hood",itemType::Helmet,1,4,0,0,0,0,1,4,0,0,0,0,0,0,0,1,20,false,"src\\textures\\items\\Buty.png"}},
};
// @formatter:on

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


void Inventory::addItem (const Item& item) {
    items.push_back(item);
}

void Inventory::removeItem (int index) {
    if (index >= 0 && index < static_cast<int>(items.size())) {
        items.erase(items.begin() + index);
    }
}

std::optional<Item> Inventory::getItemByIndex (size_t index) const {
    return items[index - 1];
}

void Inventory::printInv () const {
    if (items.empty()) {
        std::cout << "Inventory is empty.\n";
        return;
    }

    std::cout << "Items in inventory:\n" << std::endl;
    for (size_t i = 0; i < items.size(); ++i) {
        const auto& stats = items[i].getStats();
        std::cout << i + 1 << ". " << stats.name << " Type: " << items[i].getTypeString() << ",\nItem LVL: " << stats.
                itemLvl;
        if (stats.hp > 0)
            std::cout << ", HP: " << stats.hp;
        if (stats.def > 0)
            std::cout << ", DEF: " << stats.def;
        if (stats.ad > 0)
            std::cout << ", AD: " << stats.ad;
        if (stats.mana > 0)
            std::cout << ", Mana: " << stats.mana;
        if (stats.speed > 0)
            std::cout << ", Speed: " << stats.speed << std::endl;
        std::cout << std::endl;
    }
}

void Item::generateStats (std::mt19937& gen, character*& hero) {
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

int Inventory::getInvSize () const {
    return items.size();
}
