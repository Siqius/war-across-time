#ifndef STONE2_H
#define STONE2_H
#include "../Troop.h"
#include "../Game.h"

class Stone2 : public Troop {
public:
    Stone2(bool friendly);

    inline static int PRICE = 25;
    inline static int MAX_HEALTH = 20;
    inline static int DAMAGE = 10;
    inline static int ATTACK_RANGE = 150;
    inline static Texture2D TEXTURE = Game::textures["stone_2"];
};

#endif
