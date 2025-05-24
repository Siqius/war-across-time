#ifndef MEDIEVAL1_H
#define MEDIEVAL1_H
#include "../Troop.h"

class Medieval1 : public Troop {
public:
    explicit Medieval1(int playern);

    inline static int PRICE = 40;
    inline static int MAX_HEALTH = 120;
    inline static int DAMAGE = 20;
    inline static int ATTACK_RANGE = 10;
    inline static const Texture2D* TEXTURE;
};

#endif
