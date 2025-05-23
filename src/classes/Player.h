#ifndef PLAYER_H
#define PLAYER_H
#include "Structure.h"
#include <ctime>

class Player {
    int _coins;
    Structure _structure;
    clock_t last_spawned = clock();

public:
    Player(bool friendly);

    Structure& structure();

    int coins() const;

    void add_coins(int value);
    void remove_coins(int value);

    void spawn_random_troops();
};



#endif //PLAYER_H
