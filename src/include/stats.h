#pragma once

#include <iostream>

struct Stats {
    int lvl;
    int base_hp;
    int ad;
    int def;
    int mana;
    int speed;
    std::string path = "src\\textures\\GUI\\32x32border.png";
};

struct StatsIncrese {
    int base_HP_inc;
    int ad_inc;
    int def_inc;
    int mana_inc = 3;
    int speed_inc;
};
