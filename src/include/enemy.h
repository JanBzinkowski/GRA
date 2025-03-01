enum class enemyClasses
{
    enemyArcher,
    enemyMage,
    enemyWarrior,
};

struct enemyStats
{
    stats stats;
    std::string name;
    enemyClasses Class;
};
