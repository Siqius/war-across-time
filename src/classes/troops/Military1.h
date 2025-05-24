#ifndef MILITARY1_H
#define MILITARY1_H
#include "../Troop.h"


class Military1 : public Troop {
public:
    explicit Military1(int playern);

    inline static int PRICE = 200;
    inline static int MAX_HEALTH = 800;
    inline static int DAMAGE = 100;
    inline static int ATTACK_RANGE = 0;
    inline static const Texture2D* TEXTURE;
};



#endif //MILITARY1_H
