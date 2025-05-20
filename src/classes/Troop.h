#pragma once
#include <string>
#include <ctime>

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
    bool can_move = true;
    clock_t time_since_attack = clock();
public:
    Troop(int x, int y, int width, int height, int price, int health, int damage, int attack_range, const Texture2D* texture, bool friendly);

    // Getters
    int speed() const;
    Troop* target() const;
    bool friendly() const;

    // Setters
    void target(Troop* newTarget);

    void attempt_attack();

    void update();

    void scan();

    bool take_damage(int damage);

    static const int FRIENDLY_SPAWN_POS_X = 100;
    static const int FRIENDLY_SPAWN_POS_Y = 400;
    static const int ENEMY_SPAWN_POS_X = 700;
    static const int ENEMY_SPAWN_POS_Y = 400;

    static const int TROOP_SIZE = 64;
};

#endif
