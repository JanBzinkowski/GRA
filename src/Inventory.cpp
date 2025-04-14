#include "Inventory.h"

Inventory::Inventory () {
    for (int i = 0; i < 6; i++) {
        inventory.emplace_back(Item(0));
        avaiableSlot.emplace_back(i);
    }
}


void Inventory::addItem (const Item& item, const int slot) {
    inventory[slot] = item;
    for (int i = 0; i < avaiableSlot.size(); i++) {
        if (avaiableSlot[i] == slot) {
            avaiableSlot.erase(avaiableSlot.begin() + i);
            break;
        }
    }
}

int Inventory::getInvSize () const {
    return inventory.size();
}

int Inventory::get1stAvailableSlot () const {
    return avaiableSlot.front();
}

int Inventory::getAvaiableAmount () const {
    return avaiableSlot.size();
}

void Inventory::removeItem (int index) {
    inventory[index] = Item(0);
    avaiableSlot.push_back(index);
}

Item Inventory::getItemByIndex (size_t index) const {
    return inventory[index];
}

void Inventory::addSlot () {
    extraSlot++;
    inventory.emplace_back(Item(0));
    avaiableSlot.emplace_back(extraSlot + 5);
}

void Inventory::removeSlot () {
    extraSlot--;
}

void Inventory::swapItems (size_t index1, size_t index2) {
    Item temp = inventory[index1];
    inventory[index1] = inventory[index2];
    inventory[index2] = temp;
}

bool Inventory::isAvaiable (const int index) const {
    if (inventory[index].getId() != 0)
        return false;
    return true;
}
