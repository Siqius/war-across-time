#include "Vec2.h"
#include "Gameobject.h"
#ifndef TROOP_H
#define TROOP_H



class Troop : public Gameobject {
    private:
        int _speed;
        Vec2 _target;
    public:
        Troop(int x, int y, int width, int height, int speed);

        int speed() const;
        void speed(int value);

        Vec2 target() const;
        void target(Vec2 newTarget);
};



#endif //TROOP_H
