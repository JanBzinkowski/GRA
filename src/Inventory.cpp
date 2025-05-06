#include "Inventory.h"
#include <algorithm>

Inventory::Inventory () {
    for (int i = 0; i < 6; i++) {
        m_inventory.emplace_back(Item(0));
        m_avaiable_slot.emplace_back(i);
    }
}


void Inventory::addItem (const Item& item, const int slot) {
    if (slot >= 0 && m_inventory.size()) {
        m_inventory[slot] = item;
        removeAvaiableSlot(slot);
    }
}

void Inventory::removeAvaiableSlot (int index) {
    for (int i = 0; i < m_avaiable_slot.size(); i++) {
        if (m_avaiable_slot[i] == index) {
            m_avaiable_slot.erase(m_avaiable_slot.begin() + i);
            break;
        }
    }
}

int Inventory::getInvSize () const {
    return m_inventory.size();
}

int Inventory::get1stAvailableSlot () const {
    return *std::min_element(m_avaiable_slot.begin(), m_avaiable_slot.end());
}

int Inventory::getAvaiableAmount () const {
    return m_avaiable_slot.size();
}

void Inventory::removeItem (int index) {
    m_inventory[index] = Item(0);
    m_avaiable_slot.push_back(index);
}

Item Inventory::getItemByIndex (size_t index) const {
    return m_inventory[index];
}

void Inventory::addSlot () {
    extraSlot++;
    m_inventory.emplace_back(Item(0));
    m_avaiable_slot.emplace_back(extraSlot + 5);
}

void Inventory::removeSlot () {
    extraSlot--;
}

void Inventory::swapItems (size_t index1, size_t index2) {
    Item temp = m_inventory[index1];
    m_inventory[index1] = m_inventory[index2];
    m_inventory[index2] = temp;
}

bool Inventory::isAvaiable (const int index) const {
    if (m_inventory[index].getId() != 0)
        return false;
    return true;
}
