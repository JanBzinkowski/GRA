#pragma once

#include <iostream>

struct stats {
    int lvl;
    int basehp;
    int ad;
    int def;
    int mana;
    int speed;
    std::string path = "src\\textures\\GUI\\32x32border.png";
};

struct statsincrese {
    int basehpinc;
    int adinc;
    int definc;
    int manainc = 3;
    int speedinc;
};
