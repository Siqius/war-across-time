#ifndef MEDIEVAL2_H
#define MEDIEVAL2_H
#include "../Troop.h"

class Medieval2 : public Troop {
public:
    explicit Medieval2(int playern);

    inline static int PRICE = 100;
    inline static int MAX_HEALTH = 80;
    inline static int DAMAGE = 40;
    inline static int ATTACK_RANGE = 10;
    inline static const Texture2D* TEXTURE;
};

#endif
