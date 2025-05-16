#include <string>
#include "troops/Stone1.h"
#include "troops/Stone2.h"
#include "troops/Stone3.h"
#include "troops/Medieval1.h"
#include "troops/Medieval2.h"
#include "troops/Medieval3.h"

#include "Vec2.h"
#include "Gameobject.h"
#ifndef TROOP_H
#define TROOP_H



class Troop : public Gameobject {
    int _speed = 1;
    Troop* _target;
    int _price;
    int _health;
    int _damage;
    int _attack_range;
    int _target_range = 200;
    bool _friendly;
public:
    Troop(int x, int y, int width, int height, int price, int health, int damage, int attack_range, Texture2D texture, bool friendly);

    // Getters
    int speed() const;
    Troop target() const;
    bool friendly() const;

    // Setters
    void target(Troop newTarget);

    void scan();

    bool take_damage(int damage);

    static const int FRIENDLY_SPAWN_POS_X = 100;
    static const int FRIENDLY_SPAWN_POS_Y = 400;
    static const int ENEMY_SPAWN_POS_X = 700;
    static const int ENEMY_SPAWN_POS_Y = 400;

    static const int TROOP_SIZE = 64;
};

#endif
