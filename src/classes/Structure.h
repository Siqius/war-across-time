#ifndef STRUCTURE_H
#define STRUCTURE_H
#include <string>
#include <vector>
#include <map>

std::vector<std::map<std::string, int>> structures = {
    {
        {"health", 500},
        {"price", 400}
    },
    {
        {"health", 2000},
        {"price", 3000}
    },
    {
        {"health", 8000},
        {"price", 10000}
    },
    {
        {"health", 25000},
        {"price", 99999999}
    }
};

class Structure {
    int _stage = 1;
    int _upgrade_cost = structures[_stage - 1]["price"];
    int _health = structures[_stage - 1]["health"];
public:
    Structure();

    int stage() const;
    void next_stage();

    int upgrade_cost() const;

    int health() const;
    void remove_health(int value);
};



#endif //STRUCTURE_H
