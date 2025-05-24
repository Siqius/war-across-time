#ifndef MEDIEVAL3_H
#define MEDIEVAL3_H
#include "../Troop.h"

class Medieval3 : public Troop {
public:
    explicit Medieval3(int playern);

    inline static int PRICE = 400;
    inline static int MAX_HEALTH = 400;
    inline static int DAMAGE = 40;
    inline static int ATTACK_RANGE = 10;
    inline static const Texture2D* TEXTURE;
};

#endif
