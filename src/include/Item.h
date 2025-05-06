#ifndef ITEM_H
#define ITEM_H

#include "itemType.h"

class Item {
    friend class character;

    private:
        int id;
        itemStats stats = itemData.at(id);
        std::mt19937 gen;

    public:
        Item (int ItemId): id(ItemId) {
            stats = itemData.at(ItemId);
        }

        Item (int ItemId, itemStats stat): id(ItemId) {
            stats = itemData.at(ItemId);
            stats.hp = stat.hp;
            stats.ad = stat.ad;
            stats.def = stat.def;
            stats.mana = stat.mana;
            stats.speed = stat.speed;
        }

        itemStats getStats () const;
        void generateStats (std::mt19937& gen, Hero*& hero);
        int getId () const;
        itemType getType () const;
        std::string getTypeString () const;
        std::string getPath () const;
        std::string getData () const;
};


#endif //ITEM_H
