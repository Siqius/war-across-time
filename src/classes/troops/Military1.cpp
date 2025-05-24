#include "Military1.h"

Military1::Military1(int playern)
: Troop(
    (playern == 1) ? FRIENDLY_SPAWN_POS_X : ENEMY_SPAWN_POS_X,
    (playern == 1) ? FRIENDLY_SPAWN_POS_Y : ENEMY_SPAWN_POS_Y,
    TROOP_SIZE,
    TROOP_SIZE,
    PRICE,
    MAX_HEALTH,
    DAMAGE,
    ATTACK_RANGE,
    TEXTURE,
    playern
    ) { }
