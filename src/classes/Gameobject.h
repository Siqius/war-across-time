#include <raylib.h>

#include "Vec2.h"
#include "Transf.h"
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H



class Gameobject {
    Vec2 _vector2;
    Transf _transform;
    Texture2D _texture;
    public:
        Gameobject(int x, int y, int width, int height, Texture2D image);
};



#endif
