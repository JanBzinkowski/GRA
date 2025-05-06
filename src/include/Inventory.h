#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "Item.h"

class Inventory {
    friend class Hero;

    std::vector<Item> m_inventory;
    std::vector<int> m_avaiable_slot;
    int extraSlot = 0;

    public:
        Inventory ();
        void addSlot ();
        void removeSlot ();
        void removeAvaiableSlot (int index);
        void addItem (const Item& item, const int slot);
        void removeItem (int index);
        int getInvSize () const;
        int get1stAvailableSlot () const;
        int getAvaiableAmount () const;
        Item getItemByIndex (size_t index) const;
        void swapItems (size_t index1, size_t index2);
        bool isAvaiable (const int index) const;
};


#endif //INVENTORY_H
