#include "Vec2.h"
#include "Gameobject.h"
#ifndef TROOP_H
#define TROOP_H



class Troop : public Gameobject {
    int _speed;
    Vec2 _target;
public:
    Troop(int x, int y, int width, int height, Texture2D texture);

    // Getters
    int speed() const;
    Vec2 target() const;

    // Setters
    void target(Vec2 newTarget);
};



#endif
