#ifndef STRUCTURE_H
#define STRUCTURE_H
#include <string>
#include <vector>
#include <map>

#include "Gameobject.h"

inline std::vector<std::map<std::string, int>> structures = {
    {
        {"health", 500},
        {"price", 400},
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
    int _playern;
    Texture2D* _texture;
public:
    Structure(int playern);

    int stage() const;
    void next_stage();

    int upgrade_cost() const;

    int health() const;
    bool remove_health(int value);

    void texture(Texture2D* texture);

    void render() const;
};



#endif
