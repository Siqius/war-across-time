#ifndef PLAYER_H
#define PLAYER_H
#include "Structure.h"
#include "Time.h"

class Player {
    int _coins;
    Structure _structure;
    int _playern;

    long last_spawned = Time::get_time();

public:
    Player(int playern);

    Structure& structure();

    int coins() const;

    void add_coins(int value);
    void remove_coins(int value);
};



#endif //PLAYER_H
