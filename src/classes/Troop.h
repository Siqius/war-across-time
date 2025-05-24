#pragma once
#include "Time.h"
#include "Gameobject.h"
#ifndef TROOP_H
#define TROOP_H



class Troop : public Gameobject {
    int _speed = 1;
    Troop* _target;
    int _price;
    int _health;
    int _max_health;
    int _damage;
    int _attack_range;
    int _target_range = 200;
    int _playern;
    bool can_move = true;
    long time_since_attack = Time::get_time();
    long time_since_scan = Time::get_time();

public:
    Troop(int x, int y, int width, int height, int price, int health, int damage, int attack_range, const Texture2D* texture, int playern);

    // Getters
    int speed() const;
    Troop* target() const;
    int player() const;
    int health() const;
    int max_health() const;

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
