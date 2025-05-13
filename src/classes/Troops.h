#include <ratio>

#include "Troop.h"

#ifndef TROOPS_H
#define TROOPS_H



class StoneAge1 : public Troop {
    static int _price;
    static int _health;
    static int _damage;
    static int _attack_range;
public:
    StoneAge1(int x, int y, int width, int height, Texture2D texture);

    static int price();
    static int health();
    static int damage();
    static int attack_range();
};

class StoneAge2 : public Troop {
    static int _price;
    static int _health;
    static int _damage;
    static int _attack_range;
public:
    StoneAge2(int x, int y, int width, int height, Texture2D texture);

    static int price();
    static int health();
    static int damage();
    static int attack_range();
};

class StoneAge3 : public Troop {
    static int _price;
    static int _health;
    static int _damage;
    static int _attack_range;
public:
    StoneAge3(int x, int y, int width, int height, Texture2D texture);

    static int price();
    static int health();
    static int damage();
    static int attack_range();
};



#endif
