#include "enemyWarrior.h"
#include "enemyArcher.h"
#include "enemyMage.h"
#include <unordered_map>
#include <string>
#include "enemyMap.h"

std::unordered_map<int, enemyStats> enemies{
    //prologue
    {0, {{1, 20, 2, 7, 0, 1}, "Killer Bunny", enemyClasses::EnemyWarrior}},
    {1, {{2, 37, 5, 10, 0, 1}, "Butt-kicking Rabbit", enemyClasses::EnemyWarrior}},
    {2, {{2, 25, 7, 7, 0, 1}, "Magical Crow", enemyClasses::EnemyMage}},
    {3, {{2, 28, 6, 7, 0, 2}, "Stinger-shooting Bee", enemyClasses::EnemyArcher}},
    //forest
    {4, {{2, 25, 7, 8, 0, 1}, "Poison-spitting Viper", enemyClasses::EnemyMage}},
    {5, {{2, 37, 6, 10, 0, 1}, "Giant Spider", enemyClasses::EnemyWarrior}},
    {6, {{2, 40, 6, 10, 0, 1}, "Black Boar", enemyClasses::EnemyWarrior}},
    {7, {{3, 58, 9, 14, 0, 2}, "Brown Boar", enemyClasses::EnemyWarrior}},
    {8, {{3, 40, 11, 10, 0, 2}, "Forest Spirit", enemyClasses::EnemyMage}},
    {9, {{4, 56, 13, 15, 0, 4}, "Scared Hedgehog", enemyClasses::EnemyArcher}},
    {10, {{4, 57, 14, 12, 0, 4}, "Bombardier Squirrel", enemyClasses::EnemyArcher}},
    {11, {{5, 77, 14, 12, 0, 4}, "Bloody Hawk", enemyClasses::EnemyWarrior}},
    {12, {{5, 65, 14, 12, 0, 4}, "Magic Owl", enemyClasses::EnemyMage}},
    {13, {{6, 100, 16, 20, 0, 5}, "Forest Guardian", enemyClasses::EnemyWarrior}}
    //bagna
};
