#include "Vec2.h"
#include "Gameobject.h"
#ifndef TROOP_H
#define TROOP_H



class Troop : public Gameobject {
    int _speed = 1;
    Vec2 _target;
    int _price;
    int _health;
    int _damage;
    int _attack_range;
    int _target_range = 200;
public:
    Troop(int x, int y, int width, int height, int price, int health, int damage, int attack_range, Texture2D texture);

    // Getters
    int speed() const;
    Vec2 target() const;

    // Setters
    void target(Vec2 newTarget);
};



#endif
