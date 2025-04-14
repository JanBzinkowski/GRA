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

        itemStats getStats () const;
        void generateStats (std::mt19937& gen, character*& hero);
        int getId () const;
        itemType getType () const;
        std::string getTypeString () const;
        std::string getPath () const;
        std::string getData () const;
};


#endif //ITEM_H
