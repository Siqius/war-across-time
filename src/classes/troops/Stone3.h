#ifndef STONE3_H
#define STONE3_H
#include "../Troop.h"
#include "../Game.h"

class Stone3 : public Troop {
public:
    Stone3(bool friendly);

    inline static int PRICE = 100;
    inline static int MAX_HEALTH = 100;
    inline static int DAMAGE = 10;
    inline static int ATTACK_RANGE = 10;
    inline static Texture2D TEXTURE;
};

#endif
