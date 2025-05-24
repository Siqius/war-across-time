#ifndef STONE2_H
#define STONE2_H
#include "../Troop.h"

class Stone2 : public Troop {
public:
    explicit Stone2(int playern);

    inline static int PRICE = 25;
    inline static int MAX_HEALTH = 10;
    inline static int DAMAGE = 5;
    inline static int ATTACK_RANGE = 200;
    inline static const Texture2D* TEXTURE;
};

#endif
