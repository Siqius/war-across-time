#ifndef MAGIC1_H
#define MAGIC1_H
#include "../Troop.h"


class Magic1 : public Troop {
public:
    explicit Magic1(int playern);

    inline static int PRICE = 60;
    inline static int MAX_HEALTH = 500;
    inline static int DAMAGE = 80;
    inline static int ATTACK_RANGE = 0;
    inline static const Texture2D* TEXTURE;
};



#endif //MAGIC1_H
