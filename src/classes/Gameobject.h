#include "Vec2.h"
#include "Transf.h"
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H



class Gameobject {
    private:
        Vec2 _vector2;
        Transf _transform;
    public:
        Gameobject(int x, int y, int width, int height);
};



#endif
