#ifndef MAGIC3_H
#define MAGIC3_H
#include "../Troop.h"


class Magic3 : public Troop{
public:
    explicit Magic3(int playern);

    inline static int PRICE = 600;
    inline static int MAX_HEALTH = 2000;
    inline static int DAMAGE = 5;
    inline static int ATTACK_RANGE = 0;
    inline static const Texture2D* TEXTURE;
};



#endif //MAGIC3_H
