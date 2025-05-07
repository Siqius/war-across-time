#include "Vector2.h"
#ifndef TROOP_H
#define TROOP_H



class Troop {
    private:
        int _speed;
        Vector2 _pos;
        Vector2 _target;
        Transform _transform;
    public:
        int speed() const;
        void speed(int value);
};



#endif //TROOP_H
