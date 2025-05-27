#pragma once

enum class enemyClasses {
    EnemyArcher,
    EnemyMage,
    EnemyWarrior,
};

struct enemyStats {
    Stats stats;
    std::string name;
    enemyClasses Class;
    //std::string path;
};

extern std::unordered_map<int, enemyStats> enemies;
