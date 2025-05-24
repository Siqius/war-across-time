#ifndef MILITARY3_H
#define MILITARY3_H
#include "../Troop.h"


class Military3 : public Troop {
public:
    explicit Military3(int playern);

    inline static int PRICE = 7000;
    inline static int MAX_HEALTH = 10000;
    inline static int DAMAGE = 200;
    inline static int ATTACK_RANGE = 0;
    inline static const Texture2D* TEXTURE;
};



#endif
