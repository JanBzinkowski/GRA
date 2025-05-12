enum class enemyClasses {
    enemyArcher,
    enemyMage,
    enemyWarrior,
};

struct enemyStats {
    Stats stats;
    std::string name;
    enemyClasses Class;
    //std::string path;
};

extern std::unordered_map<int, enemyStats> enemies;
