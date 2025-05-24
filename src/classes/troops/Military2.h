#ifndef MILITARY2_H
#define MILITARY2_H
#include "../Troop.h"


class Military2 : public Troop {
public:
    explicit Military2(int playern);

    inline static int PRICE = 3000;
    inline static int MAX_HEALTH = 50;
    inline static int DAMAGE = 500;
    inline static int ATTACK_RANGE = 300;
    inline static const Texture2D* TEXTURE;
};



#endif //MILITARY2_H
