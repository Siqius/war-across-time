#ifndef STONE3_H
#define STONE3_H
#include "../Troop.h"

class Stone3 : public Troop {
public:
    explicit Stone3(int playern);

    inline static int PRICE = 100;
    inline static int MAX_HEALTH = 100;
    inline static int DAMAGE = 10;
    inline static int ATTACK_RANGE = 0;
    inline static const Texture2D* TEXTURE;
};

#endif
