#ifndef STONE1_H
#define STONE1_H
#include "../Troop.h"
#include "../Game.h"

class Stone1 : public Troop {
public:
    Stone1(bool friendly);

    inline static int PRICE = 10;
    inline static int MAX_HEALTH = 30;
    inline static int DAMAGE = 5;
    inline static int ATTACK_RANGE = 10;
    inline static Texture2D TEXTURE;
};

#endif
