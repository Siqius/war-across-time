#ifndef MEDIEVAL3_H
#define MEDIEVAL3_H
#include "../Troop.h"
#include "../Game.h"

class Medieval3 : public Troop {
public:
    Medieval3(bool friendly);

    inline static int PRICE = 400;
    inline static int MAX_HEALTH = 400;
    inline static int DAMAGE = 40;
    inline static int ATTACK_RANGE = 10;
    inline static Texture2D TEXTURE = Game::textures["medieval_3"];
};

#endif
