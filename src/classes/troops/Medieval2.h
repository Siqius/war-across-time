#ifndef MEDIEVAL2_H
#define MEDIEVAL2_H
#include "../Troop.h"
#include "../Game.h"

class Medieval2 : public Troop {
public:
    Medieval2(bool friendly);

    inline static int PRICE = 100;
    inline static int MAX_HEALTH = 80;
    inline static int DAMAGE = 40;
    inline static int ATTACK_RANGE = 10;
    inline static Texture2D TEXTURE = Game::textures["medieval_2"];
};

#endif
