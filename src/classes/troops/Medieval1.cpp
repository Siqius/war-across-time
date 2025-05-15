#include "Medieval1.h"

Medieval1::Medieval1(bool friendly)
: Troop(
    (friendly) ? FRIENDLY_SPAWN_POS_X : ENEMY_SPAWN_POS_X,
    (friendly) ? FRIENDLY_SPAWN_POS_Y : ENEMY_SPAWN_POS_Y,
    TROOP_SIZE,
    TROOP_SIZE,
    PRICE,
    MAX_HEALTH,
    DAMAGE,
    ATTACK_RANGE,
    TEXTURE,
    friendly
    ) { }
