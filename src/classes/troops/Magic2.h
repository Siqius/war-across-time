#ifndef MAGIC2_H
#define MAGIC2_H
#include "../Troop.h"


class Magic2 : public Troop{
public:
    explicit Magic2(int playern);

    inline static int PRICE = 400;
    inline static int MAX_HEALTH = 5;
    inline static int DAMAGE = 100;
    inline static int ATTACK_RANGE = 230;
    inline static const Texture2D* TEXTURE;
};



#endif //MAGIC2_H
