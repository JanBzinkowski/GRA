#ifndef ITEM_H
#define ITEM_H

#include "itemType.h"

class Item {
    friend class character;

    private:
        int id;
        itemStats stats;
        std::mt19937 gen;

    public:
        Item (int ItemId): id(ItemId) {
            stats = itemData.at(ItemId);
        }

        Item (int ItemId, itemStats stat): id(ItemId), stats(stat) {}

        itemStats getStats () const;
        void setStats (itemStats stat);
        void generateStats (std::mt19937& gen, Hero*& hero);
        int getId () const;
        itemType getType () const;
        std::string getTypeString () const;
        std::string getPath () const;
        std::string getData () const;
};


#endif //ITEM_H
