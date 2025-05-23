#include <raylib.h>
#include <string>

#include "Vec2.h"
#include "Transf.h"
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H



class Gameobject {
    Vec2 _vector2;
    Transf _transform;
    const Texture2D* _texture;
    int _id;
    bool _dead = false;

public:
    Gameobject(int x, int y, int width, int height, const Texture2D* texture);

    virtual ~Gameobject() {}

    void mark_dead() { _dead = true; }
    bool is_dead() const { return _dead; }

    // Getters
    Transf& transform();
    Vec2& vector2();
    int id() const;

    void render() const;
};



#endif
