#ifndef STONE1_H
#define STONE1_H
#include <string>
#include "../Troop.h"
#include "../Game.h"
using namespace std;


class Stone1 : public Troop {
public:
    Stone1(bool friendly);

    inline static int PRICE = 10;
    inline static int MAX_HEALTH = 30;
    inline static int DAMAGE = 5;
    inline static int ATTACK_RANGE = 10;
    inline static Texture2D TEXTURE = Game::textures["stone_1"];
};

#endif
