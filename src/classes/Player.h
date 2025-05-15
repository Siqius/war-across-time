#ifndef PLAYER_H
#define PLAYER_H
#include "Structure.h"


class Player {
    int _coins;
    Structure _structure;
public:
    Player(bool friendly);

    Structure structure() const;

    int coins() const;

    void add_coins(int value);
    void remove_coins(int value);
};



#endif //PLAYER_H
