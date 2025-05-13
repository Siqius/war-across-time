#include <raylib.h>
#include "Vec2.h"
#include "Transf.h"
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H



class Gameobject {
    Vec2 _vector2;
    Transf _transform;
    Texture2D _texture;
    int _id;

public:
    Gameobject(int x, int y, int width, int height, Texture2D image);

    // Getters
    Transf transform() const;
    Vec2 vector2() const;
    int id() const;

    void render() const;
};



#endif
